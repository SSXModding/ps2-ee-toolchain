#if 0
#ifndef lint
static char *rcsid = "$Id: regerror.c,v 1.2 1998/09/15 23:31:37 cgf Exp $";
#endif /* not lint */
#endif

#include "regexp.h"
#include <stdio.h>

void
regerror(s)
const char *s;
{
#ifdef ERRAVAIL
	error("regexp: %s", s);
#else
/*
	fprintf(stderr, "regexp(3): %s\n", s);
	exit(1);
*/
	return;	  /* let std. egrep handle errors */
#endif
	/* NOTREACHED */
}
