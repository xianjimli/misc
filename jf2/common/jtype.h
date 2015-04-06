/*
 * File:    jtype.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   common used types and macros.
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

#ifndef JF2_TYPE_H
#define JF2_TYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef int jbool_t;
typedef int jsword_t;
typedef unsigned char jbyte_t;
typedef unsigned int  jinst_t;
typedef unsigned int  jword_t;

typedef enum _JRet
{
	JRET_OK = 0,
	JRET_FAIL,
	JRET_OOM,
	JRET_IO,
	JRET_PC_CHANGED,
	JRET_INVALID_PARAM,
}JRet;

#define I_SIZE 4
#define A_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define REG_NR    32
#define IOPORT_NR 32
#define J_FALSE   0
#define J_TRUE    1
#define J_LOW     0
#define J_HIGH    1
#define J_LOWHIGH 1
#define J_HIGHLOW 2
#define J_NEG(i)           ((i) >> 31)
#define J_POS(i)           ((~(i)) >> 31)
#define J_TOPBITS(data, n) (data >> (n))
#define J_BIT(data, n)     ((jword_t)(data>>(n))&1) 
#define J_ROTATER(n, b)    (((n) >> (b)) | ((n) << (32 - (b))))
#define J_BITS(data, m, n) ((jword_t)(data<<(31-(n)))>>((31-(n))+(m)) ) 

#define j_ret_if_fail(p) if(!(p)) {return;}
#define j_ret_val_if_fail(p, v) if(!(p)) {return (v);}

#define DECL_PRIV() PrivInfo* priv = NULL; \
	if(thiz != NULL)\
	{\
		priv = (PrivInfo*)thiz->priv;\
	}

struct _JMachine;
typedef struct _JMachine JMachine;

#define J_UTXBUF  0x0C
#define J_URXBUF  0x10
#define J_UART0_BASE 0xf3ffd000
#define J_UART1_BASE 0xf3ffe000

#endif/*JF2_TYPE_H*/

