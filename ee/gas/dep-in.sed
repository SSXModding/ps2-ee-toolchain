:loop
/\\$/N
/\\$/b loop

s! ../config.h!!g
s! ../../bfd/bfd.h!!g
s! ../itbl-parse.h!!g
s!@INCDIR@!$(INCDIR)!g
s!@BFDDIR@!$(BFDDIR)!g
s!@SRCDIR@/config!$(srcdir)/config!g
s!@SRCDIR@/../opcodes!$(srcdir)/../opcodes!g
s!@SRCDIR@/!!g
s! config.h!!g
s! as.h!!g
s! asintl.h!!g
s! targ-env.h!!g
s! obj-format.h!!g
s! targ-cpu.h!!g
s! flonum.h!!g
s! expr.h!!g
s! struc-symbol.h!!g
s! write.h!!g
s! frags.h!!g
s! hash.h!!g
s! read.h!!g
s! symbols.h!!g
s! tc.h!!g
s! obj.h!!g
s! listing.h!!g
s! bignum.h!!g
s! bit_fix.h!!g
s! itbl-cpu.h!!g
s! \$(srcdir)/config/te-generic.h!!g
s! \$(INCDIR)/libiberty.h!!g
s! \$(INCDIR)/ansidecl.h!!g
s! \$(INCDIR)/fopen-same.h!!g

s/\\\n */ /g

s/ *$//
s/  */ /g
/:$/d

s/\(.\{50\}[^ ]*\) /\1 \\\
  /g
