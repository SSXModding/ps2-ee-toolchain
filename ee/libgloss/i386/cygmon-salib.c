/*
 * Standard x86 syscalls for user programs running under Cygmon
 *
 * Copyright (c) 1998 Cygnus Support
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include <stdlib.h>
#include "cygmon-syscall.h"
#include <sys/time.h>

extern int errno;

_syscall3(int,write,int,i,char *,c,int,len);

_syscall3(int,read,int,i,char *,c,int,len);

_syscall2(int,kill,int,pid,int,signal);

_syscall2(void,__install_signal_handler,int,arg,void *,handler);
_syscall1(char **,__get_program_arguments,int *,argc);

_syscall1(void,__sys_exit,int,exitcode);
_syscall1(void,putTtyChar,int,character);
_syscall1(time_t,time,time_t *,ptr);
_syscall2(int, gettimeofday, struct timeval *,time, struct timezone *,z);

/* Always fails. */
int
open (char *filename, int mode, int perms)
{
  return -1;
}

/* Ultra-super cheezy. */
int
isatty (int i)
{
  return i<3;
}

char *
sbrk (int amt)
{
  extern char _end;
  static char *ptr = 0;
  char *res;
  if (ptr == 0)
    ptr = &_end;
  if (amt == 0)
    return (char *)ptr;

  if (((long)ptr) % 8)
    ptr = ptr + (8 - (((long)(ptr)) % 8));
  res = ptr;
  ptr += amt;
  return (char *)res;
}

void
_exit(int i)
{
  while(1) {
    __sys_exit (i);
    asm("	int $3");
  }
}

int
close (int fd)
{
  return 0;
}

int
fstat(int des,void *buf)
{
  return -1;
}

int
lseek(int des,unsigned long offset, int whence)
{
  return -1;
}


int
getpid ()
{
  return -1;
}

/* Simple replacement for the clock() syscall. */
clock_t
clock ()
{
  struct timeval t;

  gettimeofday (&t, 0);
  return t.tv_sec * 1000 + (t.tv_usec / 1000);
}

#ifndef COFF
typedef void (*ctp)();
void
__do_global_ctors ()
{
  extern int __CTOR_LIST__;
  int *c = &__CTOR_LIST__;
  c++;
  while (*c)
    {
      ctp d = (ctp)*c;
      (d)();
      c++;
    }
}

void
__do_global_dtors ()
{
  extern int __DTOR_LIST__;
  int *c = &__DTOR_LIST__;
  int *cp = c;
  c++;
  while (*c)
    {
      c++;
    }
  c--;
  while (c > cp)
    {
      ctp d = (ctp)*c;
      (*d)();
      c--;
    }
}
#endif
