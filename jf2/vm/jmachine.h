/*
 * File:    jmachine.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   machine data struct. 
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

#ifndef JMACHINE_H
#define JMACHINE_H

#include <jioport.h>
#include <jinstruction.h>

struct _JMachine
{
	jword_t*  mem;
	jword_t*  text;
	size_t    mlen;
	size_t    tlen;
	jword_t   pc;
	jword_t   nflag;
	jword_t   zflag;
	jword_t   cflag; 
	jword_t   vflag;
	jword_t   ifflags;
	jword_t   sflag;
	jword_t   mode;
	jword_t   bank;
	jword_t   cpsr;
	jword_t   spsr[7];
	jword_t   aborted;
	jbool_t   check_mem;
	jsword_t  r[REG_NR];
	jword_t   r_bank[7][REG_NR];
	JIoPort*  ioports[IOPORT_NR];
	JInstruction* instructions[256];
};

JMachine* jmachine_create(jword_t* mem, size_t tlen, size_t mlen);
JRet      jmachine_reg_ioport(JMachine* thiz, JIoPort* ioport);
JRet      jmachine_reg_instruction(JMachine* thiz, unsigned char pos, JInstruction* i);
int       jmachine_ioport_find(JMachine* thiz, jsword_t addr);
void      jmachine_put_word (JMachine* thiz, jword_t addr, jword_t data);
void      jmachine_put_byte (JMachine* thiz, jword_t addr, jbyte_t data);
jword_t   jmachine_get_word (JMachine* thiz, jword_t addr);
jbyte_t   jmachine_get_byte (JMachine* thiz, jword_t addr);
void      jmachine_destroy(JMachine* thiz);

#define J_EMODE             (m->mode)

#define J_NFLAG             m->nflag
#define J_SETN              m->nflag = 1
#define J_CLEARN            m->nflag = 0
#define J_ASSIGNN(res)      m->nflag = res

#define J_ZFLAG             m->zflag
#define J_SETZ              m->zflag = 1
#define J_CLEARZ            m->zflag = 0
#define J_ASSIGNZ(res)      m->zflag = res

#define J_CFLAG             m->cflag
#define J_SETC              m->cflag = 1
#define J_CLEARC            m->cflag = 0
#define J_ASSIGNC(res)      m->cflag = res

#define J_VFLAG             m->vflag
#define J_SETV              m->vflag = 1
#define J_CLEARV            m->vflag = 0
#define J_ASSIGNV(res)      m->vflag = res

#define J_SFLAG             m->sflag
#define J_SETS              m->sflag = 1
#define J_CLEARS            m->sflag = 0
#define J_ASSIGNS(res)      m->sflag = res

#define J_IFLAG             (m->ifflags >> 1)
#define J_FFLAG             (m->ifflags & 1)
#define J_IFFLAGS           m->ifflags
#define J_ASSIGNINT(res)    m->ifflags = (((res) >> 6) & 3)
#define J_ASSIGNR15INT(res) m->ifflags = (((res) >> 26) & 3) ;

#define J_R_RD(m, _r)       ((m)->r[(_r)])
#define J_R_WR(m, _r, _d)   (((m)->r[(_r)]) = (_d))

#endif/*JMACHINE_H*/

