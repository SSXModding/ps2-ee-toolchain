/* Support files for GNU libc.  Files in the system namespace go here.
   Files in the C namespace (ie those that do not start with an
   underscore) go in .c.  */

#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include "swi.h"

/* Adjust our internal handles to stay away from std* handles */
#define FILE_HANDLE_OFFSET (0x20)

static int monitor_stdin;
static int monitor_stdout;
static int monitor_stderr;

/* Struct used to keep track of the file position, just so we
   can implement fseek(fh,x,SEEK_CUR).  */
typedef struct
{
  int handle;
  int pos;
}
poslog;

#define MAX_OPEN_FILES 20
static poslog openfiles [MAX_OPEN_FILES];

static int
findslot (int fh)
{
  int i;
  for (i = 0; i < MAX_OPEN_FILES; i ++)
    if (openfiles[i].handle == fh)
      break;
  return i;
}

#ifdef ARM_RDI_MONITOR

static inline int
do_AngelSWI (int reason, void * arg)
{
  int value;
  asm volatile ("mov r0, %1; mov r1, %2; swi %a3; mov %0, r0"
       : "=r" (value) /* Outputs */
       : "r" (reason), "r" (arg), "i" (AngelSWI) /* Inputs */
       : "r0", "r1", "lr"
		/* Clobbers r0 and r1, and lr if in supervisor mode */);
  return value;
}
#endif /* ARM_RDI_MONITOR */

/* Function to convert std(in|out|err) handles to internal versions */
static int
remap_handle (int fh)
{
  if (fh == __sfileno (stdin))
    return monitor_stdin;
  if (fh == __sfileno (stdout))
    return monitor_stdout;
  if (fh == __sfileno (stderr))
    return monitor_stderr;

  return fh - FILE_HANDLE_OFFSET;
}

void
initialise_monitor_handles (void)
{
  int i;
  
#ifdef ARM_RDI_MONITOR
  int volatile block[3];
  
  block[0] = (int) ":tt";
  block[2] = 3;     /* length of filename */
  block[1] = 0;     /* mode "r" */
  monitor_stdin = do_AngelSWI (AngelSWI_Reason_Open, block);

  block[0] = (int) ":tt";
  block[2] = 3;     /* length of filename */
  block[1] = 4;     /* mode "w" */
  monitor_stdout = monitor_stderr = do_AngelSWI (AngelSWI_Reason_Open, block);
#else
  int fh;
  const char * name;

  name = ":tt";
  asm ("mov r0,%2; mov r1, #0; swi %a1; mov %0, r0"
       : "=r"(fh)
       : "i" (SWI_Open),"r"(name)
       : "r0","r1");
  monitor_stdin = fh;

  name = ":tt";
  asm ("mov r0,%2; mov r1, #4; swi %a1; mov %0, r0"
       : "=r"(fh)
       : "i" (SWI_Open),"r"(name)
       : "r0","r1");
  monitor_stdout = monitor_stderr = fh;
#endif

  for (i = 0; i < MAX_OPEN_FILES; i ++)
    openfiles[i].handle = -1;

  openfiles[0].handle = monitor_stdin;
  openfiles[0].pos = 0;
  openfiles[1].handle = monitor_stdout;
  openfiles[1].pos = 0;
}

static int
get_errno ()
{
#ifdef ARM_RDI_MONITOR
  return do_AngelSWI (AngelSWI_Reason_Errno, NULL);
#else
  asm ("swi %a0" :: "i" (SWI_GetErrno));
#endif
}

static int
error (int result)
{
  errno = get_errno ();
  return result;
}

static int
wrap (int result)
{
  if (result == -1)
    return error (-1);
  return result;
}

/* Returns # chars not! written */

int
_swiread (int file,
	  char * ptr,
	  int len)
{
  int fh = remap_handle (file);
#ifdef ARM_RDI_MONITOR
  int block[3];
  
  block[0] = fh;
  block[1] = (int) ptr;
  block[2] = len;
  
  return do_AngelSWI (AngelSWI_Reason_Read, block);
#else
  asm ("mov r0, %1; mov r1, %2;mov r2, %3; swi %a0"
       : /* No outputs */
       : "i"(SWI_Read), "r"(fh), "r"(ptr), "r"(len)
       : "r0","r1","r2");
#endif
}

int
_read (int file,
       char * ptr,
       int len)
{
  int slot = findslot (remap_handle (file));
  int x = _swiread (file, ptr, len);

  if (x < 0)
    return error (-1);

  if (slot != MAX_OPEN_FILES)
    openfiles [slot].pos += len - x;

  /* x == len is not an error, at least if we want feof() to work */
  return len - x;
}

int
_swilseek (int file,
	int ptr,
	int dir)
{
  int res;
  int fh = remap_handle (file);
  int slot = findslot (fh);
#ifdef ARM_RDI_MONITOR
  int block[2];
#endif

  if (dir == SEEK_CUR)
    {
      if (slot == MAX_OPEN_FILES)
	return -1;
      ptr = openfiles[slot].pos + ptr;
      dir = SEEK_SET;
    }
  
#ifdef ARM_RDI_MONITOR
  if (dir == SEEK_END)
    {
      block[0] = fh;
      ptr += do_AngelSWI (AngelSWI_Reason_FLen, block);
    }
  
  /* This code only does absolute seeks */
  block[0] = remap_handle (file);
  block[1] = ptr;
  res = do_AngelSWI (AngelSWI_Reason_Seek, block);
#else
  if (dir == SEEK_END)
    {
      asm ("mov r0, %2; swi %a1; mov %0, r0"
	   : "=r" (res)
	   : "i" (SWI_Flen), "r" (fh)
	   : "r0");
      ptr += res;
    }

  /* This code only does absolute seeks */
  asm ("mov r0, %2; mov r1, %3; swi %a1; mov %0, r0"
       : "=r" (res)
       : "i" (SWI_Seek), "r" (fh), "r" (ptr)
       : "r0", "r1");
#endif

  if (slot != MAX_OPEN_FILES && res == 0)
    openfiles[slot].pos = ptr;

  /* This is expected to return the position in the file */
  return res == 0 ? ptr : -1;
}

int
_lseek (int file,
	int ptr,
	int dir)
{
  return wrap (_swilseek (file, ptr, dir));
}

/* Returns #chars not! written */
int
_swiwrite (
	   int    file,
	   char * ptr,
	   int    len)
{
  int fh = remap_handle (file);
#ifdef ARM_RDI_MONITOR
  int block[3];
  
  block[0] = fh;
  block[1] = (int) ptr;
  block[2] = len;
  
  return do_AngelSWI (AngelSWI_Reason_Write, block);
#else
  asm ("mov r0, %1; mov r1, %2;mov r2, %3; swi %a0"
       : /* No outputs */
       : "i"(SWI_Write), "r"(fh), "r"(ptr), "r"(len)
       : "r0","r1","r2");
#endif
}

int
_write (int    file,
	char * ptr,
	int    len)
{
  int slot = findslot (remap_handle (file));
  int x = _swiwrite (file, ptr,len);

  if (x == -1 || x == len)
    return error (-1);
  
  if (slot != MAX_OPEN_FILES)
    openfiles[slot].pos += len - x;
  
  return len - x;
}

int
_swiopen (const char * path,
	  int          flags)
{
  int aflags = 0, fh;
#ifdef ARM_RDI_MONITOR
  int block[3];
#endif
  
  int i = findslot (-1);
  
  if (i == MAX_OPEN_FILES)
    return -1;

  /* The flags are Unix-style, so we need to convert them */
#ifdef O_BINARY
  if (flags & O_BINARY)
    aflags |= 1;
#endif

  if (flags & O_RDWR)
    aflags |= 2;

  if (flags & O_CREAT)
    aflags |= 4;

  if (flags & O_TRUNC)
    aflags |= 4;

  if (flags & O_APPEND)
    {
      aflags &= ~4;     /* Can't ask for w AND a; means just 'a' */
      aflags |= 8;
    }
  
#ifdef ARM_RDI_MONITOR
  block[0] = (int) path;
  block[2] = strlen (path);
  block[1] = aflags;
  
  fh = do_AngelSWI (AngelSWI_Reason_Open, block);
  
#else
  asm ("mov r0,%2; mov r1, %3; swi %a1; mov %0, r0"
       : "=r"(fh)
       : "i" (SWI_Open),"r"(path),"r"(aflags)
       : "r0","r1");
#endif
  
  if (fh >= 0)
    {
      openfiles[i].handle = fh;
      openfiles[i].pos = 0;
    }

  return fh >= 0 ? fh + FILE_HANDLE_OFFSET : error (fh);
}

int
_open (const char * path,
       int          flags,
       ...)
{
  return wrap (_swiopen (path, flags));
}

int
_swiclose (int file)
{
  int myhan = remap_handle (file);
  int slot = findslot (myhan);
  
  if (slot != MAX_OPEN_FILES)
    openfiles[slot].handle = -1;

#ifdef ARM_RDI_MONITOR
  return do_AngelSWI (AngelSWI_Reason_Close, & myhan);
#else
  asm ("mov r0, %1; swi %a0" :: "i" (SWI_Close),"r"(myhan):"r0");
#endif
}

int
_close (int file)
{
  return wrap (_swiclose (file));
}

void
_exit (int n)
{
  /* FIXME: return code is thrown away */
  
#ifdef ARM_RDI_MONITOR
  do_AngelSWI (AngelSWI_Reason_ReportException,
	      (void *) ADP_Stopped_ApplicationExit);
#else
  asm ("swi %a0" :: "i" (SWI_Exit));
#endif
}

int
_kill (int n, int m)
{
#ifdef ARM_RDI_MONITOR
  do_AngelSWI (AngelSWI_Reason_ReportException,
	      (void *) ADP_Stopped_ApplicationExit);
#else
  asm ("swi %a0" :: "i" (SWI_Exit));
#endif
}

int
_getpid (int n)
{
  return 1;
}

register char * stack_ptr asm ("sp");

caddr_t
_sbrk (int incr)
{
  extern char   end asm ("end");	/* Defined by the linker */
  static char * heap_end;
  char *        prev_heap_end;

  if (heap_end == NULL)
    heap_end = & end;
  
  prev_heap_end = heap_end;
  
  if (heap_end + incr > stack_ptr)
    {
      _write (1, "_sbrk: Heap and stack collision\n", 32);
      abort ();
    }
  
  heap_end += incr;

  return (caddr_t) prev_heap_end;
}

int
_fstat (int           file,
	struct stat * st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int
_unlink (void)
{
  return -1;
}

void
_raise (void)
{
}

int
_gettimeofday (struct timeval * tp, struct timezone * tzp)
{

  if (tp)
    {
    /* Ask the host for the seconds since the Unix epoch */
#ifdef ARM_RDI_MONITOR
      tp->tv_sec = do_AngelSWI (AngelSWI_Reason_Time,NULL);
#else
      {
        int value;
        asm ("swi %a1; mov %0, r0" : "=r" (value): "i" (SWI_Time) : "r0");
        tp->tv_sec = value;
      }
#endif
      tp->tv_usec = 0;
    }

  /* Return fixed data for the timezone */
  if (tzp)
    {
      tzp->tz_minuteswest = 0;
      tzp->tz_dsttime = 0;
    }

  return 0;
}

/* Return a clock that ticks at 100Hz. */
clock_t 
_times(struct tms * tp)
{
  clock_t timeval;

#ifdef ARM_RDI_MONITOR
  timeval = do_AngelSWI (AngelSWI_Reason_Clock,NULL);
#else
  asm ("swi %a1; mov %0, r0" : "=r" (timeval): "i" (SWI_Clock) : "r0");
#endif

  if (tp)
    {
      tp->tms_utime  = timeval;	/* user time */
      tp->tms_stime  = 0;	/* system time */
      tp->tms_cutime = 0;	/* user time, children */
      tp->tms_cstime = 0;	/* system time, children */
    }
  
  return timeval;
};


