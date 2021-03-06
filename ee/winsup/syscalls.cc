/* syscalls.cc: syscalls

   Copyright 1996, 1997, 1998, 1999 Cygnus Solutions.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include <sys/stat.h>
#include <sys/vfs.h> /* needed for statfs */
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <utmp.h>
#include <sys/uio.h>
#include <errno.h>
#include <limits.h>
#include "winsup.h"
#include <lmcons.h> /* for UNLEN */

/* Close all files and process any queued deletions.
   Lots of unix style applications will open a tmp file, unlink it,
   but never call close.  This function is called by _exit to
   ensure we don't leave any such files lying around.  */

void
close_all_files (void)
{
  for (int i = 0; i < (int)dtable.size; i++)
    if (!dtable.not_open (i))
      _close (i);

  cygwin_shared->delqueue.process_queue ();
}

extern "C"
int
_unlink (const char *ourname)
{
  int res;

  path_conv win32_name (ourname, SYMLINK_NOFOLLOW);

  if (win32_name.error)
    {
      set_errno (win32_name.error);
      res = -1;
      goto done;
    }

  syscall_printf ("_unlink (%s)", win32_name.get_win32 ());

  /* Windows won't check the directory mode, so we do that ourselves.  */
  if (! writable_directory (win32_name.get_win32 ()))
    {
      syscall_printf ("-1 = unlink (%s)", ourname);
      return -1;
    }

  if (!DeleteFileA (win32_name.get_win32 ()))
    {
      res = GetLastError ();

      /* if access denied, chmod to be writable in case it is not
	 and try again */
      /* FIXME!!! Should check whether ourname is directory or file
	 and only try again if permissions are not sufficient */
      if (res == ERROR_ACCESS_DENIED)
	{
	  /* chmod ourname to be writable here */
	  res = chmod (ourname, 0777);

	  if (DeleteFileA (win32_name.get_win32 ()))
	    {
	      res = GetLastError ();
	      syscall_printf ("%d = unlink (%s)", res, ourname);
	      return 0;
	    }

	  res = GetLastError ();
	}

      /* If we get ERROR_SHARING_VIOLATION, the file may still be open -
	 Windows NT doesn't support deleting a file while it's open.  */
      if (res == ERROR_SHARING_VIOLATION
	  || res == ERROR_ACCESS_DENIED)
	{
	  cygwin_shared->delqueue.queue_file (win32_name.get_win32 ());
	  res = 0;
	}
      else
	{
	  __seterrno ();
	  res = -1;
	}
    }
  else
    res = 0;

done:
  syscall_printf ("%d = unlink (%s)", res, ourname);
  return res;
}

extern "C"
pid_t
_getpid ()
{
  return myself->pid;
}

/* getppid: POSIX 4.1.1.1 */
extern "C"
pid_t
getppid ()
{
  return myself->ppid;
}

/* setsid: POSIX 4.3.2.1 */
extern "C"
pid_t
setsid (void)
{
  /* FIXME: for now */
  myself->ctty = -1;
  myself->sid = _getpid ();
  myself->pgid = _getpid ();
  return _getpid ();
}

static int
read_handler (int fd, void *ptr, size_t len)
{
  int res;
  fhandler_base *fh = dtable[fd];

  if ((fh->get_flags() & (O_NONBLOCK | O_NDELAY)) && !fh->ready_for_read (0, 0))
    {
      syscall_printf ("nothing to read");
      set_errno (EAGAIN);
      return -1;
    }
  myself->process_state |= PID_TTYIN;
  res = fh->read (ptr, len);
  myself->process_state &= ~PID_TTYIN;
  syscall_printf ("%d = read (%d<%s>, %p, %d)", res, fd, fh->get_name (), ptr, len);
  return res;
}

extern "C" int
_read (int fd, void *ptr, size_t len)
{
  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
      return -1;
    }

  fhandler_base *fh = dtable[fd];

  /* Could block, so let user know we at least got here.  */
  syscall_printf ("read (%d, %p, %d)", fd, ptr, len);

  if (!fh->is_slow () || (fh->get_flags () & (O_NONBLOCK | O_NDELAY)) ||
      fh->get_r_no_interrupt ())
    {
      debug_printf ("non-interruptible read\n");
      return read_handler (fd, ptr, len);
    }

  if (!ResetEvent (signal_arrived))
    debug_printf ("couldn't reset signal_arrived (%p)", signal_arrived);

  sig_protect (here, 1);

  if (fh->ready_for_read (INFINITE, 0))
    return read_handler (fd, ptr, len);

  set_errno (EINTR);
  syscall_printf ("%d = read (%d<%s>, %p, %d), errno %d", -1, fd, fh->get_name (),
		  ptr, len, get_errno ());
  return -1;
}

extern "C"
int
_write (int fd, const void *ptr, size_t len)
{
  int res = -1;

  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
      goto done;
    }

  /* Could block, so let user know we at least got here.  */
  if (fd == 1 || fd == 2)
    {
      paranoid_printf ("write (%d, %p, %d)", fd, ptr, len);
    }
  else
    {
      syscall_printf  ("write (%d, %p, %d)", fd, ptr, len);
    }

  myself->process_state |= PID_TTYOU;
  res = dtable[fd]->write (ptr, len);
  myself->process_state &= ~PID_TTYOU;

done:
  if (fd == 1 || fd == 2)
    {
      paranoid_printf ("%d = write (%d, %p, %d)", res, fd, ptr, len);
    }
  else
    {
      syscall_printf ("%d = write (%d, %p, %d)", res, fd, ptr, len);
    }

  return (ssize_t)res;
}

/*
 * FIXME - should really move this interface into fhandler, and implement
 * write in terms of it. There are devices in Win32 that could do this with
 * overlapped I/O much more efficiently - we should eventually use
 * these.
 */

extern "C"
ssize_t
writev (int fd, const struct iovec *iov, int iovcnt)
{
  int i;
  ssize_t len, total;
  char *base;

  if (iovcnt < 1 || iovcnt > IOV_MAX)
    {
      set_errno (EINVAL);
      return -1;
    }

  /* Ensure that the sum of the iov_len values is less than
     SSIZE_MAX (per spec), if so, we must fail with no output (per spec).
  */
  total = 0;
  for (i = 0; i < iovcnt; ++i)
    {
    total += iov[i].iov_len;
    if (total > SSIZE_MAX)
      {
      set_errno (EINVAL);
      return -1;
      }
    }
  /* Now write the data */
  for (i = 0, total = 0; i < iovcnt; i++, iov++)
    {
      len = iov->iov_len;
      base = iov->iov_base;
      while (len > 0)
	{
	  register int nbytes;
	  nbytes = write (fd, base, len);
	  if (nbytes < 0 && total == 0)
	    return -1;
	  if (nbytes <= 0)
	    return total;
	  len -= nbytes;
	  total += nbytes;
	  base += nbytes;
	}
    }
  return total;
}

/*
 * FIXME - should really move this interface into fhandler, and implement
 * read in terms of it. There are devices in Win32 that could do this with
 * overlapped I/O much more efficiently - we should eventually use
 * these.
 */

extern "C"
ssize_t
readv (int fd, const struct iovec *iov, int iovcnt)
{
  int i;
  ssize_t len, total;
  char *base;

  for (i = 0, total = 0; i < iovcnt; i++, iov++)
    {
      len = iov->iov_len;
      base = iov->iov_base;
      while (len > 0)
	{
	  register int nbytes;
	  nbytes = read (fd, base, len);
	  if (nbytes < 0 && total == 0)
	    return -1;
	  if (nbytes <= 0)
	    return total;
	  len -= nbytes;
	  total += nbytes;
	  base += nbytes;
	}
    }
  return total;
}

/* _open */
/* newlib's fcntl.h defines _open as taking variable args so we must
   correspond.  The third arg if it exists is: mode_t mode. */
extern "C"
int
_open (const char *unix_path, int flags, ...)
{
  int fd;
  int res = -1;
  va_list ap;
  mode_t mode = 0;
  fhandler_base *fh;

  syscall_printf ("open (%s, %p)", unix_path, flags);
  if (check_null_empty_path_errno(unix_path))
    goto done;

  SetResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," open ");

  /* check for optional mode argument */
  va_start (ap, flags);
  mode = va_arg (ap, mode_t);
  va_end (ap);

  fd = dtable.find_unused_handle ();

  if (fd < 0)
    {
      set_errno (ENMFILE);
      goto done;
    }

  fh = dtable.build_fhandler (fd, unix_path, NULL);
  if (fh == NULL)
    {
      res = -1;		// errno already set
      goto done;
    }

  if (! dtable[fd]->open (unix_path, flags, (mode & 0777) & ~myself->umask))
    {
      dtable.release (fd);
      res = -1;
    }
  else if ((res = fd) <= 2)
    set_std_handle (res);

done:
  syscall_printf ("%d = open (%s, %p)", res, unix_path, flags);
  ReleaseResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," open");
  return res;
}

extern "C"
off_t
_lseek (int fd, off_t pos, int dir)
{
  off_t res;

  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
      res = -1;
    }
  else
    {
      res = dtable[fd]->lseek (pos, dir);
    }
  syscall_printf ("%d = lseek (%d, %d, %d)", res, fd, pos, dir);

  return res;
}

extern "C"
int
_close (int fd)
{
  int res;

  syscall_printf ("close (%d)", fd);

  if (dtable.not_open (fd))
    {
      debug_printf ("handle %d not open", fd);
      set_errno (EBADF);
      res = -1;
    }
  else
    {
      SetResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," close");
      sig_protect (here, 0);
      res = dtable[fd]->close ();
      dtable.release (fd);
      ReleaseResourceLock(LOCK_FD_LIST,WRITE_LOCK|READ_LOCK," close");
    }

  syscall_printf ("%d = close (%d)", res, fd);
  return res;
}

extern "C"
int
isatty (int fd)
{
  int res;

  if (dtable.not_open (fd))
    {
      syscall_printf ("0 = isatty (%d)", fd);
      return 0;
    }

  res = dtable[fd]->is_tty ();
  syscall_printf ("%d = isatty (%d)", res, fd);
  return res;
}

/* Under NT, try to make a hard link using backup API.  If that
   fails or we are Win 95, just copy the file.
   FIXME: We should actually be checking partition type, not OS.
   Under NTFS, we should support hard links.  On FAT partitions,
   we should just copy the file.
*/

extern "C"
int
_link (const char *a, const char *b)
{
  int res = -1;
  path_conv real_a (a, SYMLINK_NOFOLLOW);

  if (real_a.error)
    {
      set_errno (real_a.error);
      syscall_printf ("-1 = link (%s, %s)", a, b);
      return -1;
    }

  path_conv real_b (b, SYMLINK_NOFOLLOW);

  if (real_b.error)
    {
      set_errno (real_b.error);
      syscall_printf ("-1 = link (%s, %s)", a, b);
      return -1;
    }

  /* Try to make hard link first on Windows NT */
  if (os_being_run == winNT)
    {
      HANDLE hFileSource;

      WIN32_STREAM_ID StreamId;
      DWORD dwBytesWritten;
      LPVOID lpContext;
      DWORD cbPathLen;
      DWORD StreamSize;
      WCHAR wbuf[MAX_PATH];
      char buf[MAX_PATH];

      BOOL bSuccess;

      hFileSource = CreateFile (
	real_a.get_win32 (),
	FILE_WRITE_ATTRIBUTES,
	FILE_SHARE_READ | FILE_SHARE_WRITE /*| FILE_SHARE_DELETE*/,
	&sec_none_nih, // sa
	OPEN_EXISTING,
	0,
	NULL
	);

      if (hFileSource == INVALID_HANDLE_VALUE)
	{
	  syscall_printf ("cannot open source, %E");
	  goto docopy;
	}

      lpContext = NULL;
      cygwin_conv_to_full_win32_path (real_b.get_win32 (), buf);
      OemToCharW (buf, wbuf);
      cbPathLen = (strlen (buf) + 1) * sizeof (WCHAR);

      StreamId.dwStreamId = BACKUP_LINK;
      StreamId.dwStreamAttributes = 0;
      StreamId.dwStreamNameSize = 0;
      StreamId.Size.u.HighPart = 0;
      StreamId.Size.u.LowPart = cbPathLen;

      StreamSize = sizeof (WIN32_STREAM_ID) - sizeof (WCHAR**) +
					    StreamId.dwStreamNameSize;

      /* Write the WIN32_STREAM_ID */
      bSuccess = BackupWrite (
	hFileSource,
	(LPBYTE) &StreamId,	// buffer to write
	StreamSize,		// number of bytes to write
	&dwBytesWritten,
	FALSE,			// don't abort yet
	FALSE,			// don't process security
	&lpContext);

      if (bSuccess)
	{
	  /* write the buffer containing the path */
	  /* FIXME: BackupWrite sometimes traps if linkname is invalid.
	     Need to handle. */
	  bSuccess = BackupWrite (
		hFileSource,
		(LPBYTE) wbuf,	// buffer to write
		cbPathLen,	// number of bytes to write
		&dwBytesWritten,
		FALSE,		// don't abort yet
		FALSE,		// don't process security
		&lpContext
		);

	  if (!bSuccess)
	    syscall_printf ("cannot write linkname, %E");

	  /* Free context */
	  BackupWrite (
	    hFileSource,
	    NULL,		// buffer to write
	    0,			// number of bytes to write
	    &dwBytesWritten,
	    TRUE,		// abort
	    FALSE,		// don't process security
	    &lpContext
	    );
	}
      else
	syscall_printf ("cannot write streamId, %E");

      CloseHandle (hFileSource);

      if (!bSuccess)
	goto docopy;

      res = 0;
      goto done;
    }
docopy:
  /* do this with a copy */
  if (CopyFileA (real_a.get_win32 (), real_b.get_win32 (), 1))
    res = 0;
  else
    __seterrno ();

done:
  syscall_printf ("%d = link (%s, %s)", res, a, b);
  return res;
}

static BOOL
rel2abssd (PSECURITY_DESCRIPTOR psd_rel, PSECURITY_DESCRIPTOR psd_abs,
		DWORD abslen)
{
#ifdef _MT_SAFE
  struct _winsup_t *r=_reent_winsup();
  char *dacl_buf=r->_dacl_buf;
  char *sacl_buf=r->_sacl_buf;
  char *ownr_buf=r->_ownr_buf;
  char *grp_buf=r->_grp_buf;
#else
  static char dacl_buf[1024];
  static char sacl_buf[1024];
  static char ownr_buf[1024];
  static char grp_buf[1024];
#endif
  DWORD dacl_len = 1024;
  DWORD sacl_len = 1024;
  DWORD ownr_len = 1024;
  DWORD grp_len = 1024;

  BOOL res = MakeAbsoluteSD (psd_rel, psd_abs, &abslen, (PACL) dacl_buf,
			     &dacl_len, (PACL) sacl_buf, &sacl_len,
			     (PSID) ownr_buf, &ownr_len, (PSID) grp_buf,
			     &grp_len);

  syscall_printf ("%d = rel2abssd (...)", res);
  return res;
}

static BOOL
set_process_privileges ()
{
  HANDLE hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE,
					GetCurrentProcessId ());
  HANDLE hToken;
  LUID privilege;
  TOKEN_PRIVILEGES *new_priv;

  if (!OpenProcessToken (hProcess, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,
			 &hToken))
    {
      CloseHandle (hProcess);
      return FALSE;
    }

  if (!LookupPrivilegeValue (NULL, SE_RESTORE_NAME, &privilege))
    {
      CloseHandle (hProcess);
      CloseHandle (hToken);
      return FALSE;
    }

  new_priv = (TOKEN_PRIVILEGES *) malloc (sizeof (TOKEN_PRIVILEGES) +
					2 * sizeof (LUID_AND_ATTRIBUTES));
  new_priv->PrivilegeCount = 2;
  new_priv->Privileges[0].Luid = privilege;
  new_priv->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if (!LookupPrivilegeValue (NULL, SE_BACKUP_NAME, &privilege))
    {
      CloseHandle (hProcess);
      CloseHandle (hToken);
      return FALSE;
    }

  new_priv->Privileges[1].Luid = privilege;
  new_priv->Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;

  if (!AdjustTokenPrivileges (hToken, FALSE, new_priv, 0, NULL, NULL))
    {
      CloseHandle (hProcess);
      CloseHandle (hToken);
      free (new_priv);
      return FALSE;
    }

  free (new_priv);
  CloseHandle (hProcess);
  CloseHandle (hToken);

  syscall_printf ("TRUE = set_process_privileges ()");
  return TRUE;
}

/* chown: POSIX 5.6.5.1 */
/*
 * chown() is only implemented for Windows NT.  Under other operating
 * systems, it is only a stub that always returns zero.
 *
 * Note: the SetFileSecurity API in NT can only set the current
 * user as file owner so we have to use the Backup API instead.
 */
extern "C"
int
chown (const char * name, uid_t uid, gid_t gid)
{
  if (os_being_run == winNT)	// real chown only works on NT
    {
      char sid_name_buffer[1024];  // FIXME: do the bufs have to be this big?
      char sid_group_buffer[1024];
      DWORD sid_len;
      WIN32_STREAM_ID header;
      HANDLE hFile;
      DWORD bytes_read = 0;
      LPVOID context = NULL;
      PSID psid_name = (PSID) sid_name_buffer;
      PSID psid_group = (PSID) sid_group_buffer;
      char domain_name[100];
      DWORD domname_len;
      char username[UNLEN + 1];
      char groupname[UNLEN + 1];
      SID_NAME_USE acc_type;
      struct passwd *pw_ptr;
      struct group *gr_ptr;

      /* converting user and group id to names */
      if ((pw_ptr = getpwuid (uid)) == NULL)
	{
	  /* We didn't find the user id in /etc/passwd.  See if it
	     refers to us, for convenience when there is no
	     /etc/passwd file.  */
	  char userbuf[UNLEN + 1];
	  DWORD ulen;

	  sid_len = 1024;
	  domname_len = 100;
	  ulen = UNLEN + 1;
	  if (GetUserName (userbuf, &ulen))
	    {
	      if (! LookupAccountName (NULL, username, psid_name, &sid_len,
				       domain_name, &domname_len, &acc_type))
		{
		  if (GetLastError () == ERROR_NONE_MAPPED)
		    {
		      /* There is no mapping from user names to
			 security identifiers, so there isn't much we
			 can do.  */
		      syscall_printf ("0 = chown (%s,...) (no mapping)",
				      name);
		      return 0;
		    }
		  __seterrno ();
		  return -1;
		}
	      if (uid == get_id_from_sid (psid_name))
		strcpy (username, userbuf);
	      else
		{
		  set_errno (EINVAL);
		  return -1;
		}
	    }
	  else
	    {
	      set_errno (EINVAL);
	      return -1;
	    }
	}

      strcpy (username, pw_ptr->pw_name);

      if ((gr_ptr = getgrgid (gid)) == NULL)
	{
	  set_errno (EINVAL);
	  return -1;
	}

      strcpy (groupname, gr_ptr->gr_name);

      /* we need Win32 path names because of usage of Win32 API functions */
      path_conv win32_path (name);

      if (win32_path.error)
	{
	  set_errno (win32_path.error);
	  return -1;
	}

      /* open the file for read */
      hFile = CreateFile (win32_path.get_win32 (), GENERIC_READ,
			   FILE_SHARE_READ | FILE_SHARE_WRITE,
			   &sec_none_nih, OPEN_EXISTING,
			   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
			   NULL);

      if (hFile == INVALID_HANDLE_VALUE)
	{
	  __seterrno ();
	  return -1;
	}

      /* step through the backup streams and search for the security data */
      while (BackupRead (hFile, (LPBYTE) &header, sizeof (header) -
	      sizeof (header.cStreamName), &bytes_read, FALSE, TRUE, &context))
	{
	  if (header.dwStreamId == BACKUP_SECURITY_DATA)
	    {
	      DWORD datasize = header.Size.u.LowPart + header.dwStreamNameSize;
	      char b[datasize + 100];  // add space for new information
	      PSECURITY_DESCRIPTOR psd =
			 (PSECURITY_DESCRIPTOR) &b[header.dwStreamNameSize];

	      if (!BackupRead (hFile, (LPBYTE) b, datasize, &bytes_read,
		       FALSE, TRUE, &context))
		{
		  __seterrno ();
		  BackupRead (hFile, NULL, 0, &bytes_read, TRUE, TRUE, &context);
		  CloseHandle (hFile);
		  return -1;
		}

	      if (IsValidSecurityDescriptor (psd))
		{
		  /* data is valid security descriptor */

		  char abs_buf[1024];
		  PSECURITY_DESCRIPTOR abs_psd = (PSECURITY_DESCRIPTOR) abs_buf;
		  DWORD bytes_written;

		  /* terminate read process */
		  BackupRead (hFile, NULL, 0, &bytes_read, TRUE, TRUE, &context);
		  CloseHandle (hFile);

		 strcpy(abs_buf, username);
		 int retried = 0;
retry:

		  /* get sid for the new user */
		  sid_len = 1024;
		  domname_len = 100;
		 if (!LookupAccountName (NULL, abs_buf, psid_name,
			    &sid_len, domain_name, &domname_len, &acc_type))
		    {
		      __seterrno ();
		      syscall_printf ("0 = chown (%s,...)", name);
		      return 0;
		    }

		  if (!IsValidSid (psid_name))
		    {
		      __seterrno ();
		      return -1;
		    }

		 if (acc_type != SidTypeUser
		     && ! retried
		     && domain_name && *domain_name)
		   {
		      __small_sprintf (abs_buf, "%s\\%s",
				       domain_name, username);
		      retried = 1;
		      goto retry;
		   }

		  /* convert security descriptor to absolute format */
		  if (!rel2abssd (psd, abs_psd, 1024))
		    {
		      __seterrno ();
		      return -1;
		    }

		  /* set new owner information */
		  if (!SetSecurityDescriptorOwner (abs_psd, psid_name, TRUE))
		    {
			__seterrno ();
			return -1;
		    }

		  /* restore buffer size information */
		  sid_len = 1024;
		  domname_len = 100;

		  /* get sid for new group */
		  if (!LookupAccountName (NULL, groupname, psid_group,
			  &sid_len, domain_name, &domname_len, &acc_type))
		    {
		      __seterrno ();
		      return -1;
		    }

		  /* set new group info */
		  if (!SetSecurityDescriptorGroup (abs_psd, psid_group, TRUE))
		    {
		      __seterrno ();
		      return -1;
		    }

		  datasize = sizeof (b);

		  /* convert security descriptor to self-relative format */
		  if (!MakeSelfRelativeSD (abs_psd, psd, &datasize))
		    {
		      __seterrno ();
		      return -1;
		    }

		  /* set new size of security descriptor */
		  header.Size.u.LowPart = GetSecurityDescriptorLength (psd);
		  header.dwStreamAttributes = STREAM_CONTAINS_SECURITY;
		  context = NULL;

		  if (!set_process_privileges ())
		    {
		      set_errno (EACCES);
		      return -1;
		    }

		  /* open the file again for write owner and dac */
		  hFile = CreateFile (win32_path.get_win32 (),
			     GENERIC_READ | GENERIC_WRITE |
			     WRITE_OWNER | WRITE_DAC,
			     FILE_SHARE_READ | FILE_SHARE_WRITE,
			     &sec_none_nih,
			     OPEN_EXISTING,
			     FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
			     NULL);

		  if (hFile == INVALID_HANDLE_VALUE)
		    {
		      __seterrno ();
		      return -1;
		    }

		  context = NULL;
		  bytes_written = 0;

		  /* write new security info header */
		  if (!BackupWrite (hFile, (LPBYTE) &header,
			   sizeof (WIN32_STREAM_ID) - sizeof (header.cStreamName),
			   &bytes_written, FALSE, TRUE, &context))
		    {
		      __seterrno ();
		      CloseHandle (hFile);
		      return -1;
		    }

		  /* write new security descriptor */
		  if (!BackupWrite (hFile, (LPBYTE) b,
			    header.Size.u.LowPart + header.dwStreamNameSize,
			    &bytes_written, FALSE, TRUE, &context))
		    {
		      __seterrno ();
		      BackupWrite (hFile, NULL, 0, &bytes_written, TRUE,
							  TRUE, &context);
		      CloseHandle (hFile);
		      return -1;
		    }

		  /* terminate the restore process */
		  BackupWrite (hFile, NULL, 0, &bytes_written, TRUE,
							   TRUE, &context);
		  CloseHandle (hFile);
		  syscall_printf ("0 = chown (%s,...)", name);
		  return 0;
		}
	      else
		{
		  /* security descriptor data is invalid,
		   * this should not happen
		   */

		  CloseHandle (hFile);
		  set_errno (EINVAL);
		  return -1;
		}
	    }
	  else
	    {
	      DWORD low_seek = 0;
	      DWORD high_seek = 0;

	      if (!BackupSeek (hFile, header.Size.u.LowPart,
			       header.Size.u.HighPart,
			       &low_seek, &high_seek, &context))
		break;
	    }
	}

	/* no security data found - all remains unchanged */
	CloseHandle (hFile);
	syscall_printf ("0 = chown (%s,...)", name);
	return 0;
    }

  /* chown() returns zero (and does nothing) under other operating systems
     such as Windows 95 */

  syscall_printf ("0 = chown (%s,...)", name);
  return 0;
}

/* umask: POSIX 5.3.3.1 */
extern "C"
mode_t
umask (mode_t mask)
{
  mode_t oldmask;

  oldmask = myself->umask;
  myself->umask = mask & 0777;
  return oldmask;
}

/* chmod: POSIX 5.6.4.1 */
extern "C"
int
chmod (const char *path, mode_t mode)
{
  int res = -1;

  path_conv win32_path (path);

  if (win32_path.error)
    {
      set_errno (win32_path.error);
      goto done;
    }

  int now;

  set_file_attribute (win32_path.get_win32 (), mode);

  if ((now = GetFileAttributesA (win32_path.get_win32 ())) == -1)
    {
      __seterrno ();
    }
  else
    {
      /* if the mode we want has any write bits set, we can't
	 be read only. */
      if (mode & (S_IWUSR | S_IWGRP | S_IWOTH))
	{
	  now &= ~FILE_ATTRIBUTE_READONLY;
	}
      else
	{
	  now |= FILE_ATTRIBUTE_READONLY;
	}
      if (S_ISLNK (mode))
	{
	  now |= FILE_ATTRIBUTE_SYSTEM;
	}

      if (SetFileAttributesA (win32_path.get_win32 (), now))
	res = 0;
      else
	__seterrno ();
    }

done:
  syscall_printf ("%d = chmod (%s, %p)", res, path, mode);
  return res;
}

/* fchmod: P96 5.6.4.1 */

extern "C"
int
fchmod (int fd, mode_t mode)
{
  if (dtable.not_open (fd))
    {
      syscall_printf ("-1 = fchmod (%d, 0%o)", fd, mode);
      set_errno (EBADF);
      return -1;
    }

  const char *path = dtable[fd]->get_name ();

  if (path == NULL)
    {
      syscall_printf ("-1 = fchmod (%d, 0%o) (no name)", fd, mode);
      set_errno (ENOSYS);
      return -1;
    }

  syscall_printf ("fchmod (%d, 0%o): calling chmod (%s, 0%o)",
		  fd, mode, path, mode);
  return chmod (path, mode);
}

/* Cygwin internal */
static int
num_entries (const char *win32_name)
{
  WIN32_FIND_DATA buf;
  HANDLE handle;
  char buf1[MAX_PATH];
  int count = 0;

  strcpy (buf1, win32_name);
  int len = strlen (buf1);
  if (len == 0 || isdirsep (buf1[len - 1]))
    strcat (buf1, "*");
  else
    strcat (buf1, "/*");	/* */

  handle = FindFirstFileA (buf1, &buf);

  if (handle == INVALID_HANDLE_VALUE)
    return 0;
  count ++;
  while (FindNextFileA (handle, &buf))
    {
      if ((buf.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	count ++;
    }
  FindClose (handle);
  return count;
}

extern "C"
int
_fstat (int fd, struct stat *buf)
{
  int r;

  if (dtable.not_open (fd))
    {
      syscall_printf ("-1 = fstat (%d, %p)", fd, buf);
      set_errno (EBADF);
      r = -1;
    }
  else
    {
      memset (buf, 0, sizeof (struct stat));
      r = dtable[fd]->fstat (buf);
      syscall_printf ("%d = fstat (%d, %x)", r,fd,buf);
    }

  return r;
}

/* fsync: P96 6.6.1.1 */
extern "C"
int
fsync (int fd)
{
  if (dtable.not_open (fd))
    {
      syscall_printf ("-1 = fsync (%d)", fd);
      set_errno (EBADF);
      return -1;
    }

  HANDLE h = dtable[fd]->get_handle ();

  if (FlushFileBuffers (h) == 0)
    {
      __seterrno ();
      return -1;
    }
  return 0;
}

/* sync: standards? */
extern "C"
int
sync ()
{
  return 0;
}

int
stat_dev (DWORD devn, int unit, unsigned long ino, struct stat *buf)
{
  switch (devn)
    {
    case FH_CONOUT:
    case FH_PIPEW:
      buf->st_mode = STD_WBITS;
      break;
    case FH_CONIN:
    case FH_PIPER:
      buf->st_mode = STD_RBITS;
      break;
    default:
      buf->st_mode = STD_RBITS | S_IWUSR | S_IWGRP | S_IWOTH;
      break;
    }

  buf->st_mode |= S_IFCHR;
  buf->st_blksize = S_BLKSIZE;
  buf->st_nlink = 1;
  buf->st_dev = buf->st_rdev = FHDEVN (devn) << 8 | (unit & 0xff);
  buf->st_ino = ino;
  buf->st_atime = buf->st_mtime = buf->st_ctime = time (NULL);
  return 0;
}

/* Cygwin internal */
static int
stat_worker (const char *caller, const char *name, struct stat *buf,
	      int nofollow)
{
  int res = -1;
  int atts;
  char *win32_name;
  static char drive[4] = "X:\\";

  debug_printf ("%s (%s, %p)", caller, name, buf);

  path_conv real_path (name, nofollow ? SYMLINK_NOFOLLOW : SYMLINK_FOLLOW, 1);
  if (real_path.error)
    {
      set_errno (real_path.error);
      goto done;
    }

  memset (buf, 0, sizeof (struct stat));

  win32_name = real_path.get_win32 ();
  if (real_path.is_device ())
    return stat_dev (real_path.get_devn (), real_path.get_unitn (),
		     hash_path_name (0, win32_name), buf);

  atts = real_path.file_attributes ();

/* FIXME: this is of dubious merit and is fundamentally flawed.
   E.g., what if the .exe file is a symlink?  This is not accounted
   for here.  Also, what about all of the other special extensions?

   This could be "fixed" by passing the appropriate extension list
   to path_conv but I'm not sure that this is really justified.  */

  int len;
  /* If we can't find the name, try again with a .exe suffix
     [but only if not already present].  */
  if (atts == -1
      && ((len = strlen (win32_name)) < 5
	  || !strcasematch (win32_name + len - 4, ".exe")))
    {
      debug_printf ("trying with .exe suffix");
      strcat (win32_name, ".exe");
      atts = GetFileAttributesA (win32_name);
    }

  debug_printf ("%d = GetFileAttributesA (%s)", atts, win32_name);

  drive[0] = win32_name[0];
  UINT dtype;

  if (os_being_run == winNT
      && (!(atts & FILE_ATTRIBUTE_DIRECTORY)
          || ((dtype = GetDriveType (drive)) != DRIVE_NO_ROOT_DIR
             && dtype != DRIVE_REMOTE
             && dtype != DRIVE_UNKNOWN)))
    {
      fhandler_disk_file fh (NULL);

      if (fh.open (real_path, O_RDONLY | O_BINARY | O_DIROPEN |
                              (nofollow ? O_NOSYMLINK : 0), 0))
        {
          res = fh.fstat (buf);
          fh.close ();
          if (atts != -1 && (atts & FILE_ATTRIBUTE_DIRECTORY))
            buf->st_nlink = num_entries (win32_name);
        }
    }
  else if (atts == -1 || !(atts & FILE_ATTRIBUTE_DIRECTORY))
    {
      fhandler_disk_file fh (NULL);

      if (fh.open (real_path, O_RDONLY | O_BINARY |
			      (nofollow ? O_NOSYMLINK : 0), 0))
	{
	  res = fh.fstat (buf);
	  fh.close ();
	}
    }
  else
    {
      WIN32_FIND_DATA wfd;
      HANDLE handle;
      /* hmm, the number of links to a directory includes the
	 number of entries in the directory, since all the things
	 in the directory point to it */
      buf->st_nlink += num_entries (win32_name);
      buf->st_dev = FHDEVN(FH_DISK) << 8;
      buf->st_ino = hash_path_name (0, real_path.get_win32 ());
      buf->st_mode = S_IFDIR | STD_RBITS | STD_XBITS;
      if ((atts & FILE_ATTRIBUTE_READONLY) == 0)
	buf->st_mode |= STD_WBITS;
      buf->st_uid = get_file_owner (real_path.get_win32 ());
      buf->st_gid = get_file_group (real_path.get_win32 ());
      if ((handle = FindFirstFile (real_path.get_win32(), &wfd)) != INVALID_HANDLE_VALUE)
	{
	  buf->st_atime   = to_time_t (&wfd.ftLastAccessTime);
	  buf->st_mtime   = to_time_t (&wfd.ftLastWriteTime);
	  buf->st_ctime   = to_time_t (&wfd.ftCreationTime);
	  buf->st_size    = wfd.nFileSizeLow;
	  buf->st_blksize = S_BLKSIZE;
	  buf->st_blocks  = (buf->st_size + S_BLKSIZE-1) / S_BLKSIZE;
	  FindClose (handle);
	}
      res = 0;
    }

 done:
  syscall_printf ("%d = %s (%s, %p)", res, caller, name, buf);
  return res;
}

extern "C"
int
_stat (const char *name, struct stat *buf)
{
  return stat_worker ("stat", name, buf, 0);
}

/* lstat: Provided by SVR4 and 4.3+BSD, POSIX? */
extern "C"
int
lstat (const char *name, struct stat *buf)
{
  return stat_worker ("lstat", name, buf, 1);
}

extern "C"
int
access (const char *fn, int flags)
{
  struct stat st;
  int r;

  r = stat (fn, &st);
  if (r)
    return -1;
  if (flags & W_OK)
    {
      if (st.st_mode & S_IWRITE)
	return 0;

      /* can't write to the file */
      set_errno (EACCES);
      return -1;
    }
  return 0;
}

extern "C"
int
_rename (const char *oldpath, const char *newpath)
{
  int res = 0;

  path_conv real_old (oldpath, SYMLINK_NOFOLLOW);

  if (real_old.error)
    {
      set_errno (real_old.error);
      syscall_printf ("-1 = rename (%s, %s)", oldpath, newpath);
      return -1;
    }

  path_conv real_new (newpath, SYMLINK_NOFOLLOW);

  if (real_new.error)
    {
      set_errno (real_new.error);
      syscall_printf ("-1 = rename (%s, %s)", oldpath, newpath);
      return -1;
    }

  if (! writable_directory (real_old.get_win32 ())
      || ! writable_directory (real_new.get_win32 ()))
    {
      syscall_printf ("-1 = rename (%s, %s)", oldpath, newpath);
      return -1;
    }

  int oldatts = GetFileAttributesA (real_old.get_win32 ());
  int newatts = GetFileAttributesA (real_new.get_win32 ());

  if (oldatts == -1) /* file to move doesn't exist */
    {
       syscall_printf ("file to move doesn't exist");
       return (-1);
    }

  if (newatts != -1 && newatts & FILE_ATTRIBUTE_READONLY)
    {
      /* Destination file exists and is read only, change that or else
	 the rename won't work. */
      SetFileAttributesA (real_new.get_win32 (), newatts & ~ FILE_ATTRIBUTE_READONLY);
    }

  /* First make sure we have the permissions */
  if (!MoveFileEx (real_old.get_win32 (), real_new.get_win32 (), MOVEFILE_REPLACE_EXISTING))
    {
      res = -1;

      /* !!! fixme, check for windows version before trying this.. */
      if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
	{
	  /* How sad, we must be on win95, try it the stupid way */
	  syscall_printf ("try win95 hack");
	  for (;;)
	    {
	      if (MoveFile (real_old.get_win32 (), real_new.get_win32 ()))
		{
		  res = 0;
		  break;
		}

	      if (GetLastError () != ERROR_ALREADY_EXISTS)
		{
		  syscall_printf ("%s already_exists", real_new.get_win32 ());
		  break;
		}

	      if (!DeleteFileA (real_new.get_win32 ()) &&
		  GetLastError () != ERROR_FILE_NOT_FOUND)
		{
		  syscall_printf ("deleting %s to be paranoid",
				  real_new.get_win32 ());
		  break;
		}
	    }
	}
      if (res)
	__seterrno ();
    }

  if (res == 0)
    {
      /* make the new file have the permissions of the old one */
      SetFileAttributesA (real_new.get_win32 (), oldatts);
    }

  syscall_printf ("%d = rename (%s, %s)", res, real_old.get_win32 (),
		  real_new.get_win32 ());

  return res;
}

extern "C"
int
system (const char *cmdstring)
{
  int res;
  const char* command[4];
  _sig_func_ptr oldint, oldquit;
  sigset_t child_block, old_mask;

  if (cmdstring == (const char *) NULL)
	return 1;

  oldint = signal (SIGINT, SIG_IGN);
  oldquit = signal (SIGQUIT, SIG_IGN);
  sigemptyset (&child_block);
  sigaddset (&child_block, SIGCHLD);
  (void) sigprocmask (SIG_BLOCK, &child_block, &old_mask);

  command[0] = "sh";
  command[1] = "-c";
  command[2] = cmdstring;
  command[3] = (const char *) NULL;

  if ((res = spawnvp (_P_WAIT, "sh", command)) == -1)
    {
      // when exec fails, return value should be as if shell
      // executed exit (127)
      res = 127;
    }

  signal (SIGINT, oldint);
  signal (SIGQUIT, oldquit);
  (void) sigprocmask (SIG_SETMASK, &old_mask, 0);
  return res;
}

extern "C"
void
setdtablesize (int size)
{
  if (size > (int)dtable.size)
    dtable.extend (size);
}

extern "C"
int
getdtablesize ()
{
  return dtable.size;
}

extern "C"
size_t
getpagesize ()
{
  return sysconf (_SC_PAGESIZE);
}

/* FIXME: not all values are correct... */
extern "C"
long int
fpathconf (int fd, int v)
{
  switch (v)
    {
    case _PC_LINK_MAX:
      return _POSIX_LINK_MAX;
    case _PC_MAX_CANON:
    case _PC_MAX_INPUT:
      if (isatty (fd))
	return _POSIX_MAX_CANON;
      else
	{
	  set_errno (EBADF);
	  return -1;
	}
    case _PC_NAME_MAX:
    case _PC_PATH_MAX:
      return PATH_MAX;
    case _PC_PIPE_BUF:
      return 4096;
    case _PC_CHOWN_RESTRICTED:
    case _PC_NO_TRUNC:
      return -1;
    case _PC_VDISABLE:
      if (isatty (fd))
	return -1;
      else
	{
	  set_errno (EBADF);
	  return -1;
	}
    default:
      set_errno (EINVAL);
      return -1;
    }
}

extern "C"
long int
pathconf (char *file, int v)
{
  switch (v)
    {
    case _PC_PATH_MAX:
      return PATH_MAX - strlen (file);
    case _PC_NAME_MAX:
      return PATH_MAX;
    case _PC_LINK_MAX:
      return _POSIX_LINK_MAX;
    case _PC_MAX_CANON:
    case _PC_MAX_INPUT:
	return _POSIX_MAX_CANON;
    case _PC_PIPE_BUF:
      return 4096;
    case _PC_CHOWN_RESTRICTED:
    case _PC_NO_TRUNC:
      return -1;
    case _PC_VDISABLE:
	return -1;
    default:
      set_errno (EINVAL);
      return -1;
    }
}

extern "C"
char *
ctermid (char *str)
{
  static NO_COPY char buf[16];
  if (str == NULL)
    str = buf;
  if (NOTSTATE (myself, PID_USETTY) || myself->ctty == -1)
    strcpy (str, "/dev/con");
  else
    __small_sprintf (str, "/dev/tty%d", myself->ctty);
  return str;
}

extern "C"
char *
ttyname (int fd)
{
  if (dtable.not_open (fd) || !dtable[fd]->is_tty ())
    {
      return 0;
    }
  return (char *)(dtable[fd]->ttyname ());
}

/* Set a file descriptor into text or binary mode, returning the
   previous mode.  */

extern "C"
int
setmode (int fd, int mode)
{
  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
      return -1;
    }
  if (mode != O_BINARY  && mode != O_TEXT)
    {
      set_errno (EINVAL);
      return -1;
    }

  fhandler_base *p = dtable[fd];

  /* Note that we have no way to indicate the case that writes are
     binary but not reads, or vice-versa.  These cases can arise when
     using the tty or console interface.  People using those
     interfaces should not use setmode.  */

  int res;
  if (p->get_w_binary () && p->get_r_binary ())
    res = O_BINARY;
  else
    res = O_TEXT;

  if (mode & O_BINARY)
    {
      p->set_w_binary (1);
      p->set_r_binary (1);
    }
  else
    {
      p->set_w_binary (0);
      p->set_r_binary (0);
    }

  return res;
}

/* ftruncate: P96 5.6.7.1 */
extern "C"
int
ftruncate (int fd, off_t length)
{
  int res = -1;

  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
    }
  else
    {
      HANDLE h = dtable[fd]->get_handle ();
      off_t prev_loc;

      if (h)
	{
	  /* remember curr file pointer location */
	  prev_loc = dtable[fd]->lseek (0, SEEK_CUR);

	  dtable[fd]->lseek (length, SEEK_SET);
	  if (!SetEndOfFile (h))
	    {
	      __seterrno ();
	    }
	  else
	    res = 0;

	  /* restore original file pointer location */
	  dtable[fd]->lseek (prev_loc, 0);
	}
    }
  syscall_printf ("%d = ftruncate (%d, %d)", res, fd, length);

  return res;
}

/* truncate: Provided by SVR4 and 4.3+BSD.  Not part of POSIX.1 or XPG3 */
/* FIXME: untested */
extern "C"
int
truncate (const char *pathname, off_t length)
{
  int fd;
  int res = -1;

  fd = open (pathname, O_RDWR);

  if (fd == -1)
    {
      set_errno (EBADF);
    }
  else
    {
      res = ftruncate (fd, length);
      close (fd);
    }
  syscall_printf ("%d = truncate (%s, %d)", res, pathname, length);

  return res;
}

extern "C"
long
get_osfhandle (int fd)
{
  long res = -1;

  if (dtable.not_open (fd))
    {
      set_errno ( EBADF);
    }
  else
    {
      res = (long) dtable[fd]->get_handle ();
    }
  syscall_printf ("%d = get_osfhandle(%d)", res, fd);

  return res;
}

extern "C"
int
statfs (const char *fname, struct statfs *sfs)
{
  char full_path[MAX_PATH];

  if (!sfs)
    {
      set_errno (EFAULT);
      return -1;
    }
  cygwin_conv_to_full_win32_path (fname, full_path);

  /* Possible choices:
   * d:... -> d:/
   * \\server\share... -> \\server\share\
   * else current drive.
   */
  char *root=full_path;

  if (full_path[1] == ':')
    strcpy (full_path + 2, "\\");
  else if (full_path[0] == '\\' && full_path[1] == '\\')
    {
      char *cp = full_path + 2;
      while (*cp && *cp != '\\')
	cp++;
      if (!*cp)
	{
	  set_errno (ENOTDIR);
	  return -1;
	}
      cp++;
      while (*cp && *cp != '\\')
	cp++;
      strcpy (cp, "\\");
    }
  else
    root = NULL;

  syscall_printf ("statfs %s", root);

  DWORD spc, bps, freec, totalc;

  if (!GetDiskFreeSpace (root, &spc, &bps, &freec, &totalc))
    {
      __seterrno ();
      return -1;
    }

  DWORD vsn, maxlen, flags;

  if (!GetVolumeInformation (root, NULL, 0, &vsn, &maxlen, &flags, NULL, 0))
    {
      __seterrno ();
      return -1;
    }
  sfs->f_type = flags;
  sfs->f_bsize = spc*bps;
  sfs->f_blocks = totalc;
  sfs->f_bfree = sfs->f_bavail = freec;
  sfs->f_files = -1;
  sfs->f_ffree = -1;
  sfs->f_fsid = vsn;
  sfs->f_namelen = maxlen;
  return 0;
}

extern "C"
int
fstatfs (int fd, struct statfs *sfs)
{
  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
      return -1;
    }
  fhandler_disk_file *f = (fhandler_disk_file *) dtable[fd];
  return statfs (f->get_name (), sfs);
}

/* setpgid: POSIX 4.3.3.1 */
extern "C"
int
setpgid (pid_t pid, pid_t pgid)
{
  if (pid == 0)
    pid = getpid ();
  if (pgid == 0)
    pgid = pid;

  if (pgid < 0)
    {
      set_errno (EINVAL);
      return -1;
    }
  pinfo *p = procinfo (pid);
  if (p == 0)
    {
      set_errno (ESRCH);
      return -1;
    }
  /* A process may only change the process group of itself and its children */
  if (p == myself || p->ppid == myself->pid)
    {
      p->pgid = pgid;
      return 0;
    }
  else
    {
      set_errno (EPERM);
      return -1;
    }
}

extern "C"
pid_t
getpgid (pid_t pid)
{
  if (pid == 0)
    pid = getpid ();

  pinfo *p = procinfo (pid);
  if (p == 0)
    {
      set_errno (ESRCH);
      return -1;
    }
  return p->pgid;
}

extern "C"
int
setpgrp (void)
{
  return setpgid (0, 0);
}

extern "C"
pid_t
getpgrp (void)
{
  return getpgid (0);
}

extern "C"
char *
ptsname (int fd)
{
  if (dtable.not_open (fd))
    {
      set_errno (EBADF);
      return 0;
    }
  return (char *)(dtable[fd]->ptsname ());
}

/* FIXME: what is this? */
extern "C"
int
regfree ()
{
  return 0;
}

/* mknod was the call to create directories before the introduction
   of mkdir in 4.2BSD and SVR3.  Use of mknod required superuser privs
   so the mkdir command had to be setuid root.
   Although mknod hasn't been implemented yet, some GNU tools (e.g. the
   fileutils) assume its existence so we must provide a stub that always
   fails. */
extern "C"
int
mknod ()
{
  set_errno (ENOSYS);
  return -1;
}

/* setgid: POSIX 4.2.2.1 */
/* FIXME: unimplemented! */
extern "C"
int
setgid (gid_t a)
{
  set_errno (ENOSYS);
  return 0;
}

/* setuid: POSIX 4.2.2.1 */
/* FIXME: unimplemented! */
extern "C"
int
setuid (uid_t b)
{
  set_errno (ENOSYS);
  return 0;
}

/* seteuid: standards? */
extern "C"
int
seteuid (uid_t c)
{
  set_errno (ENOSYS);
  return 0;
}

/* setegid: from System V.  */
extern "C"
int
setegid (gid_t a)
{
  set_errno (ENOSYS);
  return 0;
}

/* chroot: privileged Unix system call.  */
extern "C"
int
chroot (const char *path)
{
  set_errno (ENOSYS);
  return -1;
}

extern "C"
int
creat (const char *path, mode_t mode)
{
  return open (path, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

extern "C"
void
__assertfail ()
{
  exit (99);
}

extern "C"
int
getw (FILE *fp)
{
  int w, ret;
  ret = fread (&w, sizeof (int), 1, fp);
  return ret != 1 ? EOF : w;
}

extern "C"
int
putw (int w, FILE *fp)
{
  int ret;
  ret = fwrite (&w, sizeof (int), 1, fp);
  if (feof (fp) || ferror (fp))
    return -1;
  return 0;
}

extern "C"
int
wcscmp (wchar_t *s1, wchar_t *s2)
{
  while (*s1  && *s1 == *s2)
    {
      s1++;
      s2++;
    }

  return (*(unsigned short *) s1) - (*(unsigned short *) s2);
}

extern "C"
int
wcslen (wchar_t *s1)
{
  int l = 0;
  while (s1[l])
    l++;
  return l;
}

/* FIXME: to do this right, maybe work out the usoft va_list machine
   and use wsvprintfW instead?
*/
extern "C"
int
wprintf (const char *fmt, ...)
{
  va_list ap;
  int ret;

  va_start (ap, fmt);
  ret = vprintf (fmt, ap);
  va_end (ap);
  return ret;
}

extern "C"
int
vhangup ()
{
  set_errno (ENOSYS);
  return -1;
}

extern "C"
_PTR
memccpy (_PTR out, const _PTR in, int c, size_t len)
{
  const char *inc = (char *) in;
  char *outc = (char *) out;

  while (len)
    {
      char x = *inc++;
      *outc++ = x;
      if (x == c)
	return outc;
      len --;
    }
  return 0;
}

extern "C"
int
nice (int incr)
{
  DWORD priority[] =
    {
      IDLE_PRIORITY_CLASS,
      IDLE_PRIORITY_CLASS,
      NORMAL_PRIORITY_CLASS,
      HIGH_PRIORITY_CLASS,
      REALTIME_PRIORITY_CLASS,
      REALTIME_PRIORITY_CLASS
    };
  int curr = 2;

  switch (GetPriorityClass (GetCurrentProcess ()))
    {
      case IDLE_PRIORITY_CLASS:
	curr = 1;
	break;
      case NORMAL_PRIORITY_CLASS:
	curr = 2;
	break;
      case HIGH_PRIORITY_CLASS:
	curr = 3;
	break;
      case REALTIME_PRIORITY_CLASS:
	curr = 4;
	break;
    }
  if (incr > 0)
    incr = -1;
  else if (incr < 0)
    incr = 1;

  if (SetPriorityClass (GetCurrentProcess (), priority[curr + incr]) == FALSE)
    {
      __seterrno ();
      return -1;
    }

  return 0;
}

/*
 * Find the first bit set in I.
 */

extern "C"
int
ffs (int i)
{
  static const unsigned char table[] =
    {
      0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
      6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
    };
  unsigned long int a;
  unsigned long int x = i & -i;

  a = x <= 0xffff ? (x <= 0xff ? 0 : 8) : (x <= 0xffffff ?  16 : 24);

  return table[x >> a] + a;
}

extern "C"
void
swab (const void *src, void *dst, ssize_t n)
{
  const char *from = (const char *) src;
  char *to = (char *) dst;

  while (n > 1)
    {
      const char b0 = from[--n], b1 = from[--n];
      to[n] = b0;
      to[n + 1] = b1;
    }
}

extern "C"
void
login (struct utmp *ut)
{
  register int fd;
  int currtty = ttyslot ();

  if (currtty >= 0 && (fd = open (_PATH_UTMP, O_WRONLY | O_CREAT | O_BINARY,
					 0644)) >= 0)
    {
      (void) lseek (fd, (long) (currtty * sizeof (struct utmp)), SEEK_SET);
      (void) write (fd, (char *) ut, sizeof (struct utmp));
      (void) close (fd);
    }
  if ((fd = open (_PATH_WTMP, O_WRONLY | O_APPEND | O_BINARY, 0)) >= 0)
    {
      (void) write (fd, (char *) ut, sizeof (struct utmp));
      (void) close (fd);
    }
}

/* It isn't possible to use unix-style I/O function in logout code because
cygwin's I/O subsystem may be inaccessible at logout() call time.
*/
extern "C"
int
logout (char *line)
{
  int res = 0;
  HANDLE ut_fd;

  path_conv win32_path (_PATH_UTMP);
  if (win32_path.error)
    return 0;

  ut_fd = CreateFile (win32_path.get_win32 (),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			&sec_none_nih,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
  if (ut_fd != INVALID_HANDLE_VALUE)
    {
      struct utmp *ut;
      struct utmp ut_buf[100];
      off_t pos = 0;		/* Position in file */
      DWORD rd;

      while (!res && ReadFile (ut_fd, ut_buf, sizeof ut_buf, &rd, NULL)
	     && rd != 0)
	{
	  struct utmp *ut_end = (struct utmp *) ((char *) ut_buf + rd);

	  for (ut = ut_buf; ut < ut_end; ut++, pos += sizeof (*ut))
	    if (ut->ut_name[0]
		&& strncmp (ut->ut_line, line, sizeof (ut->ut_line)) == 0)
	      /* Found the entry for LINE; mark it as logged out.  */
	      {
		/* Zero out entries describing who's logged in.  */
		bzero (ut->ut_name, sizeof (ut->ut_name));
		bzero (ut->ut_host, sizeof (ut->ut_host));
		time (&ut->ut_time);

		/* Now seek back to the position in utmp at which UT occured,
		   and write the new version of UT there.  */
		if ((SetFilePointer (ut_fd, pos, 0, FILE_BEGIN) != 0xFFFFFFFF)
		    && (WriteFile (ut_fd, (char *) ut, sizeof (*ut),
				   &rd, NULL)))
		  {
		    res = 1;
		    break;
		  }
	      }
	}

      CloseHandle (ut_fd);
    }

  return res;
}
