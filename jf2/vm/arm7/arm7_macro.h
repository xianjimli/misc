/*
 * File:    arm7_macro.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   common macro definition.
 *
 * Copyright (c) 2009  Li XianJing
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-1-25 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef ARM7_MACRO_H
#define ARM7_MACRO_H

#include <jmachine.h>

#define J_ARM_COND(instr)   J_TOPBITS(instr, 28)
#define J_ARM_INSTR(instr)  J_BITS(instr, 20, 27)
#define J_RDEST(instr)      (J_BITS (instr, 12, 15))
#define J_RLHS(instr)       (J_BITS (instr, 16, 19))
#define J_RRHS(instr)       (J_BITS (instr, 0,  3))
#define J_LHS               J_R_RD(m, J_RLHS(instr))
#define J_RHS               J_R_RD(m, J_RRHS(instr))
#define J_DEST              J_R_RD(m, J_RDEST(instr))
#define J_RMULDEST(instr)   (J_BITS (instr, 16, 19))
#define J_RMULLHS(instr)    (J_BITS (instr, 0,  3))
#define J_RMULRHS(instr)    (J_BITS (instr, 8, 11)) 
#define J_RMULACC(instr)    (J_BITS (instr, 12, 15))
#define J_MULLHS            J_R_RD(m, J_RMULLHS(instr))
#define J_MULRHS            J_R_RD(m, J_RMULRHS(instr))
#define J_NEED_DP           (J_BITS(instr,4,11)!=0)
#define J_DPRHS             ((!J_NEED_DP)?J_RHS:arm7_get_dprhs (m, instr))
#define J_DPSRHS            ((!J_NEED_DP)?J_RHS:arm7_get_dpsrhs (m, instr))
#define J_LSREGRHS          ((!J_NEED_DP)?J_RHS:arm7_get_lsregrhs(m, instr))
#define J_POS_BL(instr)     ((instr & 0x7fffff) << 2)
#define J_NEG_BL(instr)     ((0xff000000 |(instr & 0xffffff)) << 2)

typedef enum _Arm7Cond
{
	J_EQ = 0,
	J_NE = 1,
	J_CS = 2,
	J_CC = 3,
	J_MI = 4,
	J_PL = 5,
	J_VS = 6,
	J_VC = 7,
	J_HI = 8,
	J_LS = 9,
	J_GE = 10,
	J_LT = 11,
	J_GT = 12,
	J_LE = 13,
	J_AL = 14,
	J_NV = 15
}Arm7Cond;

typedef enum _Arm7Logic
{
	J_LSL = 0,
	J_LSR = 1,
	J_ASR = 2,
	J_ROR = 3
}Arm7Logic;

typedef enum _Arm7Register
{
	J_RFP = 11,
	J_RIP = 12,
	J_RSP = 13,
	J_RLR = 14,
	J_RPC = 15
}Arm7Register;

typedef enum _Arm7Mode
{
	J_USER26_MODE  = 0L,
	J_FIQ26_MODE   = 1L,
	J_IRQ26_MODE   = 2L,
	J_SVC26_MODE   = 3L,
	J_USER32_MODE  = 16L,
	J_FIQ32_MODE   = 17L,
	J_IRQ32_MODE   = 18L,
	J_SVC32_MODE   = 19L,
	J_ABORT32_MODE = 23L,
	J_UNDEF32_MODE = 27L,
	J_SYSTEMMODE  = 31L
}Arm7Mode;

typedef enum _Arm7Bank
{
	J_USER_BANK  = 0,
	J_FIQ_BANK   = 1,
	J_IRQ_BANK   = 2,
	J_SVC_BANK   = 3,
	J_ABORT_BANK = 4,
	J_UNDEF_BANK = 5,
	J_DUMMY_BANK = 6,
	J_SYSTEM_BANK = J_USER_BANK,
	J_BANK_NR = 7
}Arm7Bank;

#define J_PSR_FBITS (0xff000000L)
#define J_PSR_SBITS (0x00ff0000L)
#define J_PSR_XBITS (0x0000ff00L)
#define J_PSR_CBITS (0x000000ffL)

#define J_CCBITS      (0xf8000000L)
#define J_INTBITS     (0xc0L)
#define J_R15MODEBITS (0x3L)
#define J_MODEBITS    (0x1fL)
#define J_R15INTBITS  (3L << 26)
#define J_R15PCBITS   (0x03fffffcL)

#define J_CPSR (J_ECC | J_EINT | J_EMODE)
#define J_GETSPSR(bank) (arm7_get_spsr (m, J_EMODE))
#define J_SETPSR_F(d,s) d = ((d) & ~J_PSR_FBITS) | ((s) & J_PSR_FBITS)
#define J_SETPSR_S(d,s) d = ((d) & ~J_PSR_SBITS) | ((s) & J_PSR_SBITS)
#define J_SETPSR_X(d,s) d = ((d) & ~J_PSR_XBITS) | ((s) & J_PSR_XBITS)
#define J_SETPSR_C(d,s) d = ((d) & ~J_PSR_CBITS) | ((s) & J_PSR_CBITS)

#define J_ER15INT (J_IFFLAGS << 26)
#define J_ECC ((J_NFLAG << 31) | (J_ZFLAG << 30) \
	    | (J_CFLAG << 29) | (J_VFLAG << 28) | (J_SFLAG << 27))
#define J_EINT    (J_IFFLAGS << 6)

typedef enum _Arm7StatusBit
{
	J_NBIT      = ((unsigned)1L << 31),
	J_ZBIT      = (1L << 30),
	J_CBIT      = (1L << 29),
	J_VBIT      = (1L << 28),
	J_SBIT      = (1L << 27),
	J_IBIT      = (1L << 7),
	J_FBIT      = (1L << 6),
	J_TBIT      = (1L << 5),
	J_IFBITS    = (3L << 6),
	J_R15IBIT   = (1L << 27),
	J_R15FBIT   = (1L << 26),
	J_R15IFBITS = (3L << 26)
}Arm7StatusBit;

typedef enum _Arm7Vector
{
	ARM7_V_RESET           = 0L,
	ARM7_V_UNDEF_INSTR     = 4L,
	ARM7_V_SWI             = 8L,
	ARM7_V_PREFETCH_ABORT  = 12L,
	ARM7_V_DATA_ABORT      = 16L,
	ARM7_V_ADDR_EXECEPTION = 20L,
	ARM7_V_IRQ             = 24L,
	ARM7_V_FIQ             = 28L
}Arm7Vector;

#endif/*ARM7_MACRO_H*/

