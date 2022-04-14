# /* This is file ISATTY.S */
# /*
# ** Copyright (C) 1991 DJ Delorie, 24 Kirsten Ave, Rochester NH 03867-2954
# **
# ** This file is distributed under the terms listed in the document
# ** "copying.dj", available from DJ Delorie at the address above.
# ** A copy of "copying.dj" should accompany this file; if not, a copy
# ** should be available from where this file was obtained.  This file
# ** may not be distributed without a verbatim copy of "copying.dj".
# **
# ** This file is distributed WITHOUT ANY WARRANTY; without even the implied
# ** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# */

	.text
	.globl _isatty
_isatty:
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	movl	16(%esp),%ebx
	movw	$0x4400,%ax
	int	$0x21
	popl	%edi
	popl	%esi
	popl	%ebx
	movl	$0,%eax
	jb	tf
	testl	$0x80,%edx
	jz	tf
	movl	$1,%eax
tf:
	ret
