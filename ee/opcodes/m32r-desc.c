/* CPU data for m32r.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996, 1997, 1998, 1999 Free Software Foundation, Inc.

This file is part of the GNU Binutils and/or GDB, the GNU debugger.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/

#include "sysdep.h"
#include <ctype.h>
#include <stdio.h>
#include "ansidecl.h"
#include "bfd.h"
#include "symcat.h"
#include "m32r-desc.h"
#include "m32r-opc.h"
#include "opintl.h"

/* Attributes.  */

static const CGEN_ATTR_ENTRY bool_attr[] =
{
  { "#f", 0 },
  { "#t", 1 },
  { 0, 0 }
};

static const CGEN_ATTR_ENTRY MACH_attr[] =
{
  { "base", MACH_BASE },
  { "m32r", MACH_M32R },
  { "m32rx", MACH_M32RX },
  { "max", MACH_MAX },
  { 0, 0 }
};

static const CGEN_ATTR_ENTRY PIPE_attr[] =
{
  { "NONE", PIPE_NONE },
  { "O", PIPE_O },
  { "S", PIPE_S },
  { "OS", PIPE_OS },
  { 0, 0 }
};

const CGEN_ATTR_TABLE m32r_cgen_ifield_attr_table[] =
{
  { "MACH", & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "PCREL-ADDR", &bool_attr[0], &bool_attr[0] },
  { "ABS-ADDR", &bool_attr[0], &bool_attr[0] },
  { "RESERVED", &bool_attr[0], &bool_attr[0] },
  { "SIGN-OPT", &bool_attr[0], &bool_attr[0] },
  { "SIGNED", &bool_attr[0], &bool_attr[0] },
  { "RELOC", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE m32r_cgen_hardware_attr_table[] =
{
  { "MACH", & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "CACHE-ADDR", &bool_attr[0], &bool_attr[0] },
  { "PC", &bool_attr[0], &bool_attr[0] },
  { "PROFILE", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE m32r_cgen_operand_attr_table[] =
{
  { "MACH", & MACH_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "PCREL-ADDR", &bool_attr[0], &bool_attr[0] },
  { "ABS-ADDR", &bool_attr[0], &bool_attr[0] },
  { "SIGN-OPT", &bool_attr[0], &bool_attr[0] },
  { "SIGNED", &bool_attr[0], &bool_attr[0] },
  { "NEGATIVE", &bool_attr[0], &bool_attr[0] },
  { "RELAX", &bool_attr[0], &bool_attr[0] },
  { "SEM-ONLY", &bool_attr[0], &bool_attr[0] },
  { "RELOC", &bool_attr[0], &bool_attr[0] },
  { "HASH-PREFIX", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

const CGEN_ATTR_TABLE m32r_cgen_insn_attr_table[] =
{
  { "MACH", & MACH_attr[0] },
  { "PIPE", & PIPE_attr[0] },
  { "ALIAS", &bool_attr[0], &bool_attr[0] },
  { "VIRTUAL", &bool_attr[0], &bool_attr[0] },
  { "UNCOND-CTI", &bool_attr[0], &bool_attr[0] },
  { "COND-CTI", &bool_attr[0], &bool_attr[0] },
  { "SKIP-CTI", &bool_attr[0], &bool_attr[0] },
  { "DELAY-SLOT", &bool_attr[0], &bool_attr[0] },
  { "RELAXABLE", &bool_attr[0], &bool_attr[0] },
  { "RELAX", &bool_attr[0], &bool_attr[0] },
  { "NO-DIS", &bool_attr[0], &bool_attr[0] },
  { "PBB", &bool_attr[0], &bool_attr[0] },
  { "FILL-SLOT", &bool_attr[0], &bool_attr[0] },
  { "SPECIAL", &bool_attr[0], &bool_attr[0] },
  { 0, 0, 0 }
};

static CGEN_KEYWORD_ENTRY m32r_cgen_opval_gr_names_entries[] =
{
  { "fp", 13 },
  { "lr", 14 },
  { "sp", 15 },
  { "r0", 0 },
  { "r1", 1 },
  { "r2", 2 },
  { "r3", 3 },
  { "r4", 4 },
  { "r5", 5 },
  { "r6", 6 },
  { "r7", 7 },
  { "r8", 8 },
  { "r9", 9 },
  { "r10", 10 },
  { "r11", 11 },
  { "r12", 12 },
  { "r13", 13 },
  { "r14", 14 },
  { "r15", 15 }
};

CGEN_KEYWORD m32r_cgen_opval_gr_names =
{
  & m32r_cgen_opval_gr_names_entries[0],
  19
};

static CGEN_KEYWORD_ENTRY m32r_cgen_opval_cr_names_entries[] =
{
  { "psw", 0 },
  { "cbr", 1 },
  { "spi", 2 },
  { "spu", 3 },
  { "bpc", 6 },
  { "bbpsw", 8 },
  { "bbpc", 14 },
  { "cr0", 0 },
  { "cr1", 1 },
  { "cr2", 2 },
  { "cr3", 3 },
  { "cr4", 4 },
  { "cr5", 5 },
  { "cr6", 6 },
  { "cr7", 7 },
  { "cr8", 8 },
  { "cr9", 9 },
  { "cr10", 10 },
  { "cr11", 11 },
  { "cr12", 12 },
  { "cr13", 13 },
  { "cr14", 14 },
  { "cr15", 15 }
};

CGEN_KEYWORD m32r_cgen_opval_cr_names =
{
  & m32r_cgen_opval_cr_names_entries[0],
  23
};

static CGEN_KEYWORD_ENTRY m32r_cgen_opval_h_accums_entries[] =
{
  { "a0", 0 },
  { "a1", 1 }
};

CGEN_KEYWORD m32r_cgen_opval_h_accums =
{
  & m32r_cgen_opval_h_accums_entries[0],
  2
};



/* The hardware table.  */

#define A(a) (1 << (CONCAT2 (CGEN_HW_,a) - CGEN_ATTR_BOOL_OFFSET))

const CGEN_HW_ENTRY m32r_cgen_hw_table[] =
{
  { "h-pc", HW_H_PC, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0|A(PROFILE)|A(PC), { (1<<MACH_BASE) } } },
  { "h-memory", HW_H_MEMORY, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-sint", HW_H_SINT, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-uint", HW_H_UINT, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-addr", HW_H_ADDR, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-iaddr", HW_H_IADDR, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-hi16", HW_H_HI16, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-slo16", HW_H_SLO16, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-ulo16", HW_H_ULO16, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-gr", HW_H_GR, CGEN_ASM_KEYWORD, (PTR) & m32r_cgen_opval_gr_names, { CGEN_HW_NBOOL_ATTRS, 0|A(CACHE_ADDR)|A(PROFILE), { (1<<MACH_BASE) } } },
  { "h-cr", HW_H_CR, CGEN_ASM_KEYWORD, (PTR) & m32r_cgen_opval_cr_names, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-accum", HW_H_ACCUM, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-accums", HW_H_ACCUMS, CGEN_ASM_KEYWORD, (PTR) & m32r_cgen_opval_h_accums, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_M32RX) } } },
  { "h-cond", HW_H_COND, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-psw", HW_H_PSW, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-bpsw", HW_H_BPSW, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-bbpsw", HW_H_BBPSW, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { "h-lock", HW_H_LOCK, CGEN_ASM_NONE, 0, { CGEN_HW_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } } },
  { 0 }
};

#undef A

/* The instruction field table.  */

#define A(a) (1 << (CONCAT2 (CGEN_IFLD_,a) - CGEN_ATTR_BOOL_OFFSET))

const CGEN_IFLD m32r_cgen_ifld_table[] =
{
  { M32R_F_NIL, "f-nil", 0, 0, 0, 0, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_OP1, "f-op1", 0, 32, 0, 4, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_OP2, "f-op2", 0, 32, 8, 4, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_COND, "f-cond", 0, 32, 4, 4, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_R1, "f-r1", 0, 32, 4, 4, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_R2, "f-r2", 0, 32, 12, 4, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_SIMM8, "f-simm8", 0, 32, 8, 8, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_SIMM16, "f-simm16", 0, 32, 16, 16, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_SHIFT_OP2, "f-shift-op2", 0, 32, 8, 3, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_UIMM4, "f-uimm4", 0, 32, 12, 4, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_UIMM5, "f-uimm5", 0, 32, 11, 5, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_UIMM16, "f-uimm16", 0, 32, 16, 16, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_UIMM24, "f-uimm24", 0, 32, 8, 24, { CGEN_IFLD_NBOOL_ATTRS, 0|A(RELOC)|A(ABS_ADDR), { (1<<MACH_BASE) } }  },
  { M32R_F_HI16, "f-hi16", 0, 32, 16, 16, { CGEN_IFLD_NBOOL_ATTRS, 0|A(SIGN_OPT), { (1<<MACH_BASE) } }  },
  { M32R_F_DISP8, "f-disp8", 0, 32, 8, 8, { CGEN_IFLD_NBOOL_ATTRS, 0|A(RELOC)|A(PCREL_ADDR), { (1<<MACH_BASE) } }  },
  { M32R_F_DISP16, "f-disp16", 0, 32, 16, 16, { CGEN_IFLD_NBOOL_ATTRS, 0|A(RELOC)|A(PCREL_ADDR), { (1<<MACH_BASE) } }  },
  { M32R_F_DISP24, "f-disp24", 0, 32, 8, 24, { CGEN_IFLD_NBOOL_ATTRS, 0|A(RELOC)|A(PCREL_ADDR), { (1<<MACH_BASE) } }  },
  { M32R_F_OP23, "f-op23", 0, 32, 9, 3, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_OP3, "f-op3", 0, 32, 14, 2, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_ACC, "f-acc", 0, 32, 8, 1, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_ACCS, "f-accs", 0, 32, 12, 2, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_ACCD, "f-accd", 0, 32, 4, 2, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_BITS67, "f-bits67", 0, 32, 6, 2, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_BIT14, "f-bit14", 0, 32, 14, 1, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { M32R_F_IMM1, "f-imm1", 0, 32, 15, 1, { CGEN_IFLD_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
  { 0 }
};

#undef A

/* The operand table.  */

#define A(a) (1 << (CONCAT2 (CGEN_OPERAND_,a) - CGEN_ATTR_BOOL_OFFSET))
#define OPERAND(op) CONCAT2 (M32R_OPERAND_,op)

const CGEN_OPERAND m32r_cgen_operand_table[] =
{
/* pc: program counter */
  { "pc", M32R_OPERAND_PC, HW_H_PC, 0, 0,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(SEM_ONLY), { (1<<MACH_BASE) } }  },
/* sr: source register */
  { "sr", M32R_OPERAND_SR, HW_H_GR, 12, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* dr: destination register */
  { "dr", M32R_OPERAND_DR, HW_H_GR, 4, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* src1: source register 1 */
  { "src1", M32R_OPERAND_SRC1, HW_H_GR, 4, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* src2: source register 2 */
  { "src2", M32R_OPERAND_SRC2, HW_H_GR, 12, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* scr: source control register */
  { "scr", M32R_OPERAND_SCR, HW_H_CR, 12, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* dcr: destination control register */
  { "dcr", M32R_OPERAND_DCR, HW_H_CR, 4, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* simm8: 8 bit signed immediate */
  { "simm8", M32R_OPERAND_SIMM8, HW_H_SINT, 8, 8,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX), { (1<<MACH_BASE) } }  },
/* simm16: 16 bit signed immediate */
  { "simm16", M32R_OPERAND_SIMM16, HW_H_SINT, 16, 16,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX), { (1<<MACH_BASE) } }  },
/* uimm4: 4 bit trap number */
  { "uimm4", M32R_OPERAND_UIMM4, HW_H_UINT, 12, 4,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX), { (1<<MACH_BASE) } }  },
/* uimm5: 5 bit shift count */
  { "uimm5", M32R_OPERAND_UIMM5, HW_H_UINT, 11, 5,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX), { (1<<MACH_BASE) } }  },
/* uimm16: 16 bit unsigned immediate */
  { "uimm16", M32R_OPERAND_UIMM16, HW_H_UINT, 16, 16,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX), { (1<<MACH_BASE) } }  },
/* imm1: 1 bit immediate */
  { "imm1", M32R_OPERAND_IMM1, HW_H_UINT, 15, 1,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX), { (1<<MACH_M32RX) } }  },
/* accd: accumulator destination register */
  { "accd", M32R_OPERAND_ACCD, HW_H_ACCUMS, 4, 2,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_M32RX) } }  },
/* accs: accumulator source register */
  { "accs", M32R_OPERAND_ACCS, HW_H_ACCUMS, 12, 2,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_M32RX) } }  },
/* acc: accumulator reg (d) */
  { "acc", M32R_OPERAND_ACC, HW_H_ACCUMS, 8, 1,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_M32RX) } }  },
/* hash: # prefix */
  { "hash", M32R_OPERAND_HASH, HW_H_SINT, 0, 0,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* hi16: high 16 bit immediate, sign optional */
  { "hi16", M32R_OPERAND_HI16, HW_H_HI16, 16, 16,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(SIGN_OPT), { (1<<MACH_BASE) } }  },
/* slo16: 16 bit signed immediate, for low() */
  { "slo16", M32R_OPERAND_SLO16, HW_H_SLO16, 16, 16,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* ulo16: 16 bit unsigned immediate, for low() */
  { "ulo16", M32R_OPERAND_ULO16, HW_H_ULO16, 16, 16,
    { CGEN_OPERAND_NBOOL_ATTRS, 0, { (1<<MACH_BASE) } }  },
/* uimm24: 24 bit address */
  { "uimm24", M32R_OPERAND_UIMM24, HW_H_ADDR, 8, 24,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(HASH_PREFIX)|A(RELOC)|A(ABS_ADDR), { (1<<MACH_BASE) } }  },
/* disp8: 8 bit displacement */
  { "disp8", M32R_OPERAND_DISP8, HW_H_IADDR, 8, 8,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(RELAX)|A(RELOC)|A(PCREL_ADDR), { (1<<MACH_BASE) } }  },
/* disp16: 16 bit displacement */
  { "disp16", M32R_OPERAND_DISP16, HW_H_IADDR, 16, 16,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(RELOC)|A(PCREL_ADDR), { (1<<MACH_BASE) } }  },
/* disp24: 24 bit displacement */
  { "disp24", M32R_OPERAND_DISP24, HW_H_IADDR, 8, 24,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(RELAX)|A(RELOC)|A(PCREL_ADDR), { (1<<MACH_BASE) } }  },
/* condbit: condition bit */
  { "condbit", M32R_OPERAND_CONDBIT, HW_H_COND, 0, 0,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(SEM_ONLY), { (1<<MACH_BASE) } }  },
/* accum: accumulator */
  { "accum", M32R_OPERAND_ACCUM, HW_H_ACCUM, 0, 0,
    { CGEN_OPERAND_NBOOL_ATTRS, 0|A(SEM_ONLY), { (1<<MACH_BASE) } }  },
  { 0 }
};

#undef A

#define A(a) (1 << (CONCAT2 (CGEN_INSN_,a) - CGEN_ATTR_BOOL_OFFSET))
#define OP(field) CGEN_SYNTAX_MAKE_FIELD (OPERAND (field))

/* The instruction table.  */

static const CGEN_IBASE m32r_cgen_insn_table[MAX_INSNS] =
{
  /* Special null first entry.
     A `num' value of zero is thus invalid.
     Also, the special `invalid' insn resides here.  */
  { 0, 0, 0 },
/* add $dr,$sr */
  {
    M32R_INSN_ADD, "add", "add", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* add3 $dr,$sr,$hash$slo16 */
  {
    M32R_INSN_ADD3, "add3", "add3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* and $dr,$sr */
  {
    M32R_INSN_AND, "and", "and", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* and3 $dr,$sr,$uimm16 */
  {
    M32R_INSN_AND3, "and3", "and3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* or $dr,$sr */
  {
    M32R_INSN_OR, "or", "or", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* or3 $dr,$sr,$hash$ulo16 */
  {
    M32R_INSN_OR3, "or3", "or3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* xor $dr,$sr */
  {
    M32R_INSN_XOR, "xor", "xor", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* xor3 $dr,$sr,$uimm16 */
  {
    M32R_INSN_XOR3, "xor3", "xor3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* addi $dr,$simm8 */
  {
    M32R_INSN_ADDI, "addi", "addi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* addv $dr,$sr */
  {
    M32R_INSN_ADDV, "addv", "addv", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* addv3 $dr,$sr,$simm16 */
  {
    M32R_INSN_ADDV3, "addv3", "addv3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* addx $dr,$sr */
  {
    M32R_INSN_ADDX, "addx", "addx", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* bc.s $disp8 */
  {
    M32R_INSN_BC8, "bc8", "bc.s", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* bc.l $disp24 */
  {
    M32R_INSN_BC24, "bc24", "bc.l", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* beq $src1,$src2,$disp16 */
  {
    M32R_INSN_BEQ, "beq", "beq", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* beqz $src2,$disp16 */
  {
    M32R_INSN_BEQZ, "beqz", "beqz", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bgez $src2,$disp16 */
  {
    M32R_INSN_BGEZ, "bgez", "bgez", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bgtz $src2,$disp16 */
  {
    M32R_INSN_BGTZ, "bgtz", "bgtz", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* blez $src2,$disp16 */
  {
    M32R_INSN_BLEZ, "blez", "blez", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bltz $src2,$disp16 */
  {
    M32R_INSN_BLTZ, "bltz", "bltz", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bnez $src2,$disp16 */
  {
    M32R_INSN_BNEZ, "bnez", "bnez", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bl.s $disp8 */
  {
    M32R_INSN_BL8, "bl8", "bl.s", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(FILL_SLOT)|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* bl.l $disp24 */
  {
    M32R_INSN_BL24, "bl24", "bl.l", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bcl.s $disp8 */
  {
    M32R_INSN_BCL8, "bcl8", "bcl.s", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(FILL_SLOT)|A(COND_CTI), { (1<<MACH_M32RX), PIPE_O } }
  },
/* bcl.l $disp24 */
  {
    M32R_INSN_BCL24, "bcl24", "bcl.l", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_M32RX), PIPE_NONE } }
  },
/* bnc.s $disp8 */
  {
    M32R_INSN_BNC8, "bnc8", "bnc.s", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* bnc.l $disp24 */
  {
    M32R_INSN_BNC24, "bnc24", "bnc.l", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bne $src1,$src2,$disp16 */
  {
    M32R_INSN_BNE, "bne", "bne", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bra.s $disp8 */
  {
    M32R_INSN_BRA8, "bra8", "bra.s", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(FILL_SLOT)|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* bra.l $disp24 */
  {
    M32R_INSN_BRA24, "bra24", "bra.l", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_NONE } }
  },
/* bncl.s $disp8 */
  {
    M32R_INSN_BNCL8, "bncl8", "bncl.s", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(FILL_SLOT)|A(COND_CTI), { (1<<MACH_M32RX), PIPE_O } }
  },
/* bncl.l $disp24 */
  {
    M32R_INSN_BNCL24, "bncl24", "bncl.l", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(COND_CTI), { (1<<MACH_M32RX), PIPE_NONE } }
  },
/* cmp $src1,$src2 */
  {
    M32R_INSN_CMP, "cmp", "cmp", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* cmpi $src2,$simm16 */
  {
    M32R_INSN_CMPI, "cmpi", "cmpi", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* cmpu $src1,$src2 */
  {
    M32R_INSN_CMPU, "cmpu", "cmpu", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* cmpui $src2,$simm16 */
  {
    M32R_INSN_CMPUI, "cmpui", "cmpui", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* cmpeq $src1,$src2 */
  {
    M32R_INSN_CMPEQ, "cmpeq", "cmpeq", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_OS } }
  },
/* cmpz $src2 */
  {
    M32R_INSN_CMPZ, "cmpz", "cmpz", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_OS } }
  },
/* div $dr,$sr */
  {
    M32R_INSN_DIV, "div", "div", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* divu $dr,$sr */
  {
    M32R_INSN_DIVU, "divu", "divu", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* rem $dr,$sr */
  {
    M32R_INSN_REM, "rem", "rem", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* remu $dr,$sr */
  {
    M32R_INSN_REMU, "remu", "remu", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* divh $dr,$sr */
  {
    M32R_INSN_DIVH, "divh", "divh", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_NONE } }
  },
/* jc $sr */
  {
    M32R_INSN_JC, "jc", "jc", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL)|A(COND_CTI), { (1<<MACH_M32RX), PIPE_O } }
  },
/* jnc $sr */
  {
    M32R_INSN_JNC, "jnc", "jnc", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL)|A(COND_CTI), { (1<<MACH_M32RX), PIPE_O } }
  },
/* jl $sr */
  {
    M32R_INSN_JL, "jl", "jl", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(FILL_SLOT)|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* jmp $sr */
  {
    M32R_INSN_JMP, "jmp", "jmp", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* ld $dr,@$sr */
  {
    M32R_INSN_LD, "ld", "ld", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* ld $dr,@($slo16,$sr) */
  {
    M32R_INSN_LD_D, "ld-d", "ld", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* ldb $dr,@$sr */
  {
    M32R_INSN_LDB, "ldb", "ldb", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* ldb $dr,@($slo16,$sr) */
  {
    M32R_INSN_LDB_D, "ldb-d", "ldb", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* ldh $dr,@$sr */
  {
    M32R_INSN_LDH, "ldh", "ldh", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* ldh $dr,@($slo16,$sr) */
  {
    M32R_INSN_LDH_D, "ldh-d", "ldh", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* ldub $dr,@$sr */
  {
    M32R_INSN_LDUB, "ldub", "ldub", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* ldub $dr,@($slo16,$sr) */
  {
    M32R_INSN_LDUB_D, "ldub-d", "ldub", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* lduh $dr,@$sr */
  {
    M32R_INSN_LDUH, "lduh", "lduh", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* lduh $dr,@($slo16,$sr) */
  {
    M32R_INSN_LDUH_D, "lduh-d", "lduh", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* ld $dr,@$sr+ */
  {
    M32R_INSN_LD_PLUS, "ld-plus", "ld", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* ld24 $dr,$uimm24 */
  {
    M32R_INSN_LD24, "ld24", "ld24", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* ldi8 $dr,$simm8 */
  {
    M32R_INSN_LDI8, "ldi8", "ldi8", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* ldi16 $dr,$hash$slo16 */
  {
    M32R_INSN_LDI16, "ldi16", "ldi16", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* lock $dr,@$sr */
  {
    M32R_INSN_LOCK, "lock", "lock", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* machi $src1,$src2 */
  {
    M32R_INSN_MACHI, "machi", "machi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* machi $src1,$src2,$acc */
  {
    M32R_INSN_MACHI_A, "machi-a", "machi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* maclo $src1,$src2 */
  {
    M32R_INSN_MACLO, "maclo", "maclo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* maclo $src1,$src2,$acc */
  {
    M32R_INSN_MACLO_A, "maclo-a", "maclo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* macwhi $src1,$src2 */
  {
    M32R_INSN_MACWHI, "macwhi", "macwhi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* macwhi $src1,$src2,$acc */
  {
    M32R_INSN_MACWHI_A, "macwhi-a", "macwhi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL), { (1<<MACH_M32RX), PIPE_S } }
  },
/* macwlo $src1,$src2 */
  {
    M32R_INSN_MACWLO, "macwlo", "macwlo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* macwlo $src1,$src2,$acc */
  {
    M32R_INSN_MACWLO_A, "macwlo-a", "macwlo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL), { (1<<MACH_M32RX), PIPE_S } }
  },
/* mul $dr,$sr */
  {
    M32R_INSN_MUL, "mul", "mul", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_S } }
  },
/* mulhi $src1,$src2 */
  {
    M32R_INSN_MULHI, "mulhi", "mulhi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mulhi $src1,$src2,$acc */
  {
    M32R_INSN_MULHI_A, "mulhi-a", "mulhi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mullo $src1,$src2 */
  {
    M32R_INSN_MULLO, "mullo", "mullo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mullo $src1,$src2,$acc */
  {
    M32R_INSN_MULLO_A, "mullo-a", "mullo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mulwhi $src1,$src2 */
  {
    M32R_INSN_MULWHI, "mulwhi", "mulwhi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mulwhi $src1,$src2,$acc */
  {
    M32R_INSN_MULWHI_A, "mulwhi-a", "mulwhi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL), { (1<<MACH_M32RX), PIPE_S } }
  },
/* mulwlo $src1,$src2 */
  {
    M32R_INSN_MULWLO, "mulwlo", "mulwlo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mulwlo $src1,$src2,$acc */
  {
    M32R_INSN_MULWLO_A, "mulwlo-a", "mulwlo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL), { (1<<MACH_M32RX), PIPE_S } }
  },
/* mv $dr,$sr */
  {
    M32R_INSN_MV, "mv", "mv", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* mvfachi $dr */
  {
    M32R_INSN_MVFACHI, "mvfachi", "mvfachi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mvfachi $dr,$accs */
  {
    M32R_INSN_MVFACHI_A, "mvfachi-a", "mvfachi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mvfaclo $dr */
  {
    M32R_INSN_MVFACLO, "mvfaclo", "mvfaclo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mvfaclo $dr,$accs */
  {
    M32R_INSN_MVFACLO_A, "mvfaclo-a", "mvfaclo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mvfacmi $dr */
  {
    M32R_INSN_MVFACMI, "mvfacmi", "mvfacmi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mvfacmi $dr,$accs */
  {
    M32R_INSN_MVFACMI_A, "mvfacmi-a", "mvfacmi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mvfc $dr,$scr */
  {
    M32R_INSN_MVFC, "mvfc", "mvfc", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* mvtachi $src1 */
  {
    M32R_INSN_MVTACHI, "mvtachi", "mvtachi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mvtachi $src1,$accs */
  {
    M32R_INSN_MVTACHI_A, "mvtachi-a", "mvtachi", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mvtaclo $src1 */
  {
    M32R_INSN_MVTACLO, "mvtaclo", "mvtaclo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* mvtaclo $src1,$accs */
  {
    M32R_INSN_MVTACLO_A, "mvtaclo-a", "mvtaclo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mvtc $sr,$dcr */
  {
    M32R_INSN_MVTC, "mvtc", "mvtc", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* neg $dr,$sr */
  {
    M32R_INSN_NEG, "neg", "neg", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* nop */
  {
    M32R_INSN_NOP, "nop", "nop", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* not $dr,$sr */
  {
    M32R_INSN_NOT, "not", "not", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* rac */
  {
    M32R_INSN_RAC, "rac", "rac", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* rac $accd,$accs,$imm1 */
  {
    M32R_INSN_RAC_DSI, "rac-dsi", "rac", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* rach */
  {
    M32R_INSN_RACH, "rach", "rach", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32R), PIPE_S } }
  },
/* rach $accd,$accs,$imm1 */
  {
    M32R_INSN_RACH_DSI, "rach-dsi", "rach", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* rte */
  {
    M32R_INSN_RTE, "rte", "rte", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* seth $dr,$hash$hi16 */
  {
    M32R_INSN_SETH, "seth", "seth", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* sll $dr,$sr */
  {
    M32R_INSN_SLL, "sll", "sll", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* sll3 $dr,$sr,$simm16 */
  {
    M32R_INSN_SLL3, "sll3", "sll3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* slli $dr,$uimm5 */
  {
    M32R_INSN_SLLI, "slli", "slli", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* sra $dr,$sr */
  {
    M32R_INSN_SRA, "sra", "sra", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* sra3 $dr,$sr,$simm16 */
  {
    M32R_INSN_SRA3, "sra3", "sra3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* srai $dr,$uimm5 */
  {
    M32R_INSN_SRAI, "srai", "srai", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* srl $dr,$sr */
  {
    M32R_INSN_SRL, "srl", "srl", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* srl3 $dr,$sr,$simm16 */
  {
    M32R_INSN_SRL3, "srl3", "srl3", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* srli $dr,$uimm5 */
  {
    M32R_INSN_SRLI, "srli", "srli", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* st $src1,@$src2 */
  {
    M32R_INSN_ST, "st", "st", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* st $src1,@($slo16,$src2) */
  {
    M32R_INSN_ST_D, "st-d", "st", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* stb $src1,@$src2 */
  {
    M32R_INSN_STB, "stb", "stb", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* stb $src1,@($slo16,$src2) */
  {
    M32R_INSN_STB_D, "stb-d", "stb", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* sth $src1,@$src2 */
  {
    M32R_INSN_STH, "sth", "sth", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* sth $src1,@($slo16,$src2) */
  {
    M32R_INSN_STH_D, "sth-d", "sth", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_NONE } }
  },
/* st $src1,@+$src2 */
  {
    M32R_INSN_ST_PLUS, "st-plus", "st", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* st $src1,@-$src2 */
  {
    M32R_INSN_ST_MINUS, "st-minus", "st", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* sub $dr,$sr */
  {
    M32R_INSN_SUB, "sub", "sub", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* subv $dr,$sr */
  {
    M32R_INSN_SUBV, "subv", "subv", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* subx $dr,$sr */
  {
    M32R_INSN_SUBX, "subx", "subx", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_OS } }
  },
/* trap $uimm4 */
  {
    M32R_INSN_TRAP, "trap", "trap", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(FILL_SLOT)|A(UNCOND_CTI), { (1<<MACH_BASE), PIPE_O } }
  },
/* unlock $src1,@$src2 */
  {
    M32R_INSN_UNLOCK, "unlock", "unlock", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_BASE), PIPE_O } }
  },
/* satb $dr,$sr */
  {
    M32R_INSN_SATB, "satb", "satb", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_NONE } }
  },
/* sath $dr,$sr */
  {
    M32R_INSN_SATH, "sath", "sath", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_NONE } }
  },
/* sat $dr,$sr */
  {
    M32R_INSN_SAT, "sat", "sat", 32,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL), { (1<<MACH_M32RX), PIPE_NONE } }
  },
/* pcmpbz $src2 */
  {
    M32R_INSN_PCMPBZ, "pcmpbz", "pcmpbz", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_OS } }
  },
/* sadd */
  {
    M32R_INSN_SADD, "sadd", "sadd", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* macwu1 $src1,$src2 */
  {
    M32R_INSN_MACWU1, "macwu1", "macwu1", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* msblo $src1,$src2 */
  {
    M32R_INSN_MSBLO, "msblo", "msblo", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* mulwu1 $src1,$src2 */
  {
    M32R_INSN_MULWU1, "mulwu1", "mulwu1", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* maclh1 $src1,$src2 */
  {
    M32R_INSN_MACLH1, "maclh1", "maclh1", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0, { (1<<MACH_M32RX), PIPE_S } }
  },
/* sc */
  {
    M32R_INSN_SC, "sc", "sc", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL)|A(SKIP_CTI), { (1<<MACH_M32RX), PIPE_O } }
  },
/* snc */
  {
    M32R_INSN_SNC, "snc", "snc", 16,
    { CGEN_INSN_NBOOL_ATTRS, 0|A(SPECIAL)|A(SKIP_CTI), { (1<<MACH_M32RX), PIPE_O } }
  },
};

#undef A
#undef MNEM
#undef OP

static void
init_tables ()
{
}

/* Initialize a cpu table and return a descriptor.
   It's much like opening a file, and must be the first function called.
   MACH is the desired machine, one of enum mach_attr.
   ISA is the desired isa, one of enum isa_attr.  */

CGEN_CPU_DESC
m32r_cgen_cpu_open (mach, isa, endian)
     int mach;
     int isa;
     enum cgen_endian endian;
{
  CGEN_CPU_TABLE *cd = (CGEN_CPU_TABLE *) xmalloc (sizeof (CGEN_CPU_TABLE));
  static int init_p;

  if (! init_p)
    {
      init_tables ();
      init_p = 1;
    }

  memset (cd, 0, sizeof (*cd));

  cd->mach = mach;
  cd->isa = isa;
  cd->endian = endian;
  /* FIXME: for the sparc case we can determine insn-endianness statically.
     The worry here is where both data and insn endian can be independently
     chosen, in which case this function will need another argument.
     Actually, will want to allow for more arguments in the future anyway.  */
  cd->insn_endian = endian;

  cd->int_insn_p = CGEN_INT_INSN_P;

  cd->max_insn_size = CGEN_MAX_INSN_SIZE;

  /* Determine which hw elements are used by MACH.  */
  {
    int i;
    const CGEN_HW_ENTRY *init = & m32r_cgen_hw_table[0];
    /* MAX_HW is only an upper bound on the number of selected entries.
       However each entry is indexed by it's enum so there can be holes in
       the table.  */
    const CGEN_HW_ENTRY **selected =
      (const CGEN_HW_ENTRY **) xmalloc (MAX_HW * sizeof (CGEN_HW_ENTRY *));

    cd->hw_table.init_entries = init;
    cd->hw_table.entry_size = sizeof (CGEN_HW_ENTRY);
    memset (selected, 0, MAX_HW * sizeof (CGEN_HW_ENTRY *));
    /* ??? For now we just use mach to determine which ones we want.  */
    for (i = 0; init[i].name != NULL; ++i)
      if (CGEN_HW_ATTR_VALUE (&init[i], CGEN_HW_MACH)
	  & ((1 << mach) | (1 << MACH_BASE)))
        selected[init[i].type] = &init[i];
    cd->hw_table.entries = selected;
    cd->hw_table.num_entries = MAX_HW;
  }

  cd->ifld_table = & m32r_cgen_ifld_table[0];

  /* Determine which operands are used by MACH/ISA.  */
  {
    int i;
    const CGEN_OPERAND *init = & m32r_cgen_operand_table[0];
    /* MAX_OPERANDS is only an upper bound on the number of selected entries.
       However each entry is indexed by it's enum so there can be holes in
       the table.  */
    const CGEN_OPERAND **selected =
      (const CGEN_OPERAND **) xmalloc (MAX_OPERANDS * sizeof (CGEN_OPERAND *));

    cd->operand_table.init_entries = init;
    cd->operand_table.entry_size = sizeof (CGEN_OPERAND);
    memset (selected, 0, MAX_OPERANDS * sizeof (CGEN_OPERAND *));
    /* ??? For now we just use mach to determine which ones we want.  */
    for (i = 0; init[i].name != NULL; ++i)
      if (CGEN_OPERAND_ATTR_VALUE (&init[i], CGEN_OPERAND_MACH)
	  & ((1 << mach) | (1 << MACH_BASE)))
        selected[init[i].type] = &init[i];
    cd->operand_table.entries = selected;
    cd->operand_table.num_entries = MAX_OPERANDS;
  }

  /* Build the instruction table.
     ??? This could leave out insns not supported by the specified mach/isa,
     but that would cause errors like "foo only supported by bar" to become
     "unknown insn", so for now we include all insns and require the app to
     do the checking later.  Might wish to add an argument or new function to
     discard such insns from the table.  */
  {
    int i;
    const CGEN_IBASE *ib = & m32r_cgen_insn_table[0];
    CGEN_INSN *insns = (CGEN_INSN *) xmalloc (MAX_INSNS * sizeof (CGEN_INSN));
    memset (insns, 0, MAX_INSNS * sizeof (CGEN_INSN));
    for (i = 0; i < MAX_INSNS; ++i)
      insns[i].base = &ib[i];
    cd->insn_table.init_entries = insns;
  }
  cd->insn_table.entry_size = sizeof (CGEN_IBASE);
  cd->insn_table.num_init_entries = MAX_INSNS;

  return (CGEN_CPU_DESC) cd;
}

/* Close a cpu table.  */

void
m32r_cgen_cpu_close (cd)
     CGEN_CPU_DESC cd;
{
  if (cd->insn_table.init_entries)
    free ((CGEN_INSN *) cd->insn_table.init_entries);
  if (cd->hw_table.entries)
    free ((CGEN_HW_ENTRY *) cd->hw_table.entries);
  free (cd);
}
