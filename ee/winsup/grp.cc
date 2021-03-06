/* grp.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

   Original stubs by Jason Molenda of Cygnus Support, crash@cygnus.com
   First implementation by Gunther Ebert, gunther.ebert@ixos-leipzig.de

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include "winsup.h"

/* Read /etc/group only once for better performance.  This is done
   on the first call that needs information from it. */

static NO_COPY const char *etc_group = "/etc/group";
static struct group *group_buf = NULL;		/* group contents in memory */
static int curr_lines = 0;
static int max_lines = 0;

/* Position in the group cache */
#ifdef _MT_SAFE
#define grp_pos _reent_winsup()->_grp_pos
#else
static int grp_pos = 0;
#endif

/* Default values used if accessing /etc/group isn't possible */
static char def_gr_name[] = "everyone";
static int def_gr_gid = 500;
static struct group defgroup;

/* Set to 1 when /etc/group has been read in by read_etc_group (). */
/* Functions in this file need to check the value of group_in_memory_p
   and read in the group file if it isn't set. */
/* FIXME: This should be static but this is called in uinfo_init outside
   this file */
int group_in_memory_p = 0;

static int
parse_grp (struct group &grp, const char *line)
{
  int len = strlen(line);
  char *newline = (char *) malloc (len + 1);
  (void) memcpy (newline, line, len + 1);

  if (newline[--len] == '\n')
    newline[len] = '\0';

  grp.gr_name = strtok (newline, ":");

  if (grp.gr_name)
    {
      char *id_ptr = strtok (NULL, ":");

      if (id_ptr)
	{
	  char **namearray = (char **) calloc (2, sizeof (char *));
	  grp.gr_gid = atoi (id_ptr);
	  namearray[0] = grp.gr_name;
	  namearray[1] = NULL;
	  grp.gr_mem = namearray;
	  return 1;
	}
    }

  return 0;
}

/* Read one line from /etc/group into the group cache */
static void
add_grp_line (const char *line)
{
    if (curr_lines == max_lines)
    {
	max_lines += 10;
	group_buf = (struct group *) realloc (group_buf, max_lines * sizeof (struct group));
    }
    if (parse_grp (group_buf[curr_lines], line))
      curr_lines++;
}

/* Cygwin internal */
/* Read in /etc/group and save contents in the group cache */
/* This sets group_in_memory_p to 1 so functions in this file can
   tell that /etc/group has been read in */
/* FIXME: should be static but this is called in uinfo_init outside this
   file */
void
read_etc_group ()
{
  FILE *f = fopen (etc_group, "r");

  if (f)
    {
      char linebuf[200];

      while (fgets (linebuf, sizeof (linebuf), f) != NULL)
	{
	  if (strlen (linebuf))
	    add_grp_line (linebuf);
	}

      fclose (f);
    }
  else /* /etc/group doesn't exist -- create default one in memory */
    add_grp_line ("everyone::500:\n");

  static char *defnames[2];
  defgroup.gr_gid = def_gr_gid;
  defgroup.gr_name = def_gr_name;
  defgroup.gr_mem = defnames;
  defnames[0] = def_gr_name;
  defnames[1] = NULL;

  group_in_memory_p = 1;
}

extern "C"
struct group *
getgrgid (gid_t gid)
{
  if (!group_in_memory_p)
    read_etc_group();

  for (int i = 0; i < curr_lines; i++)
    if (group_buf[i].gr_gid == gid)
      return group_buf + i;

  return &defgroup;
}

extern "C"
struct group *
getgrnam (const char *name)
{
  if (!group_in_memory_p)
    read_etc_group();

  for (int i = 0; i < curr_lines; i++)
    if (strcasematch (group_buf[i].gr_name, name))
      return group_buf + i;

  /* Didn't find requested group */
  return NULL;
}

extern "C"
void
endgrent()
{
  grp_pos = 0;
}

extern "C"
struct group *
getgrent()
{
  if (!group_in_memory_p)
    read_etc_group();

  if (grp_pos < curr_lines)
    return group_buf + grp_pos++;

  return NULL;
}

extern "C"
void
setgrent ()
{
  grp_pos = 0;
}

/* Cygwin doesn't support supplementary groups so we
   return only the current gid */
extern "C"
int
getgroups (int gidsetsize, gid_t *grouplist)
{
  if (gidsetsize <= 0)
      return 0;
  grouplist[0] = myself->gid;
  return 1;
}

extern "C"
int
initgroups (const char *user, gid_t grp)
{
  return 0;
}
