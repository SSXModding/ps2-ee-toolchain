/* read.c -- read bytes from a input device.
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
#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "bsp-trap.h"


/*
 * _read  -- read bytes from an input device.
 */
int
_read(int fd, char *buf, int nbytes)
{
    int err;
    err = _bsp_trap(SYS_read, fd, buf, nbytes);
    if (err)
	errno = err;
    return err;
}

