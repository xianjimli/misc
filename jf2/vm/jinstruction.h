/*
 * File:    jinstruction.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   instruction interface. 
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

#ifndef JINSTRUCTION_H
#define JINSTRUCTION_H

#include <jtype.h>

struct _JInstruction;
typedef struct _JInstruction JInstruction;

typedef JRet (*JInstructionInitFunc)(JInstruction* thiz, JMachine* machine);
typedef JRet (*JInstructionExecuteFunc)(JInstruction* thiz, jinst_t instr); 
typedef JRet (*JInstructionDasFunc)(JInstruction* thiz, jinst_t instr, char* t);
typedef JRet (*JInstructionAsFunc)(JInstruction* thiz, const char* t, jinst_t* instr);
typedef void (*JInstructionDestroyFunc)(JInstruction* thiz);

struct _JInstruction
{
	JInstructionInitFunc    init;
	JInstructionExecuteFunc execute;
	JInstructionDasFunc     das;
	JInstructionAsFunc      as;
	JInstructionDestroyFunc destroy;

	char priv[0];
};

static inline JRet jinstruction_init(JInstruction* thiz, JMachine* machine)
{
	j_ret_val_if_fail(thiz != NULL && thiz->init != NULL, JRET_INVALID_PARAM);

	return thiz->init(thiz, machine);
}

static inline JRet jinstruction_execute(JInstruction* thiz, jinst_t instr)
{
	j_ret_val_if_fail(thiz != NULL && thiz->execute != NULL, JRET_INVALID_PARAM);

	return thiz->execute(thiz, instr);
}

static inline JRet jinstruction_das(JInstruction* thiz, jinst_t instr, char* t)
{
	j_ret_val_if_fail(thiz != NULL && thiz->das != NULL, JRET_INVALID_PARAM);

	return thiz->das(thiz, instr, t);
}

static inline JRet jinstruction_as(JInstruction* thiz, const char* t, jinst_t* instr)
{
	j_ret_val_if_fail(thiz != NULL && thiz->as != NULL, JRET_INVALID_PARAM);
	j_ret_val_if_fail(t != NULL && instr != NULL, JRET_INVALID_PARAM);

	return thiz->as(thiz, t, instr);
}

static inline void jinstruction_destroy(JInstruction* thiz)
{
	j_ret_if_fail(thiz != NULL && thiz->destroy != NULL);

	thiz->destroy(thiz);

	return;
}

#endif/*JINSTRUCTION_H*/

