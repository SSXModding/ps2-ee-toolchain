/* pipe.cc: pipe for WIN32.

   Copyright 1996, 1998, 1999 Cygnus Solutions.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include "winsup.h"

static int
make_pipe (int fildes[2], unsigned int psize, int mode)
{
  SetResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," make_pipe");

  HANDLE r, w;
  int  fdr, fdw;
  SECURITY_ATTRIBUTES *sa = (mode & O_NOINHERIT) ?  &sec_none_nih : &sec_none;

  if ((fdr = dtable.find_unused_handle ()) < 0)
    set_errno (ENMFILE);
  else if ((fdw = dtable.find_unused_handle (fdr + 1)) < 0)
    set_errno ( ENMFILE);
  else if (!CreatePipe (&r, &w, sa, psize))
    __seterrno ();
  else
    {
      fhandler_base *fhr = dtable.build_fhandler (fdr, FH_PIPE, "/dev/piper");
      fhandler_base *fhw = dtable.build_fhandler (fdw, FH_PIPE, "/dev/pipew");

      int binmode = mode & O_TEXT ? 0 : 1;
      fhr->init (r, GENERIC_READ, binmode);
      fhw->init (w, GENERIC_WRITE, binmode);
      if (mode & O_NOINHERIT)
       {
	 fhr->set_close_on_exec_flag (1);
	 fhw->set_close_on_exec_flag (1);
       }

      fildes[0] = fdr;
      fildes[1] = fdw;

      debug_printf ("0 = pipe (%p) (%d:%p, %d:%p)", fildes,
		    fdr, fhr->get_handle (), fdw, fhw->get_handle ());

      ReleaseResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," make_pipe");
      return 0;
    }

  syscall_printf ("-1 = pipe (%p)", fildes);
  ReleaseResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," make_pipe");
  return -1;
}

extern "C" int
pipe (int filedes[2])
{
  return make_pipe (filedes, 16384, __fmode);
}

extern "C" int
_pipe (int filedes[2], unsigned int psize, int mode)
{
  int res = make_pipe (filedes, psize, mode);
  /* This type of pipe is not interruptible so set the appropriate flag. */
  if (!res)
    dtable[filedes[0]]->set_r_no_interrupt (1);
  return res;
}

int
dup (int fd)
{
  int res;
  SetResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," dup");

  res = dup2 (fd, dtable.find_unused_handle ());

  ReleaseResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," dup");

  return res;
}

int
dup2 (int oldfd, int newfd)
{
  return dtable.dup2 (oldfd, newfd);
}
