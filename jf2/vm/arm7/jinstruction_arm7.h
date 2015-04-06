/*
 * File:    jinstruction_arm7.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
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

#ifndef JINSTRUCTION_ARM7_H
#define JINSTRUCTION_ARM7_H

#include <arm7_nv.h>
#include <arm7_macro.h>
#include <arm7_memory.h>
#include <jinstruction.h>

JInstruction* jinstruction_arm7_create(int opcode, 
	JInstructionExecuteFunc execute,
	JInstructionDasFunc das, 
	JInstructionAsFunc as);

JMachine*     jinstruction_arm7_get_machine(JInstruction* thiz);

int  arm7_count_one(jword_t data);
void arm7_subcarry (JMachine* m, jword_t a, jword_t b, jword_t result);
void arm7_sub_overflow (JMachine* m, jword_t a, jword_t b, jword_t res);

void arm7_cpsr_changed(JMachine* m);
void arm7_neg_zero (JMachine* m, jsword_t result);
void arm7_undef_instr(JMachine* m, jword_t instr);
void arm7_abort(JMachine* m, jword_t vector);

jword_t arm7_get_lsregrhs(JMachine* m, jword_t instr);
jword_t arm7_get_dprhs(JMachine* m, jword_t instr);
jword_t arm7_get_dpsrhs(JMachine* m, jword_t instr);
void arm7_fix_cpsr(JMachine* m, jword_t instr, jword_t cpsr);
void arm7_fix_spsr(JMachine* m, jword_t instr, jword_t spsr);
jword_t arm7_mode_to_bank(jword_t mode);
void arm7_set_cpsr(JMachine* m, jword_t cpsr);
void arm7_set_spsr(JMachine* m, jword_t mode, jword_t spsr);
jword_t arm7_get_cpsr(JMachine* m);
jword_t arm7_get_spsr(JMachine* m, jword_t mode);
jword_t arm7_decode_immed(jword_t index);

#define J_DECL_MACHINE(inst) JMachine* m = jinstruction_arm7_get_machine(inst)

#define ARM7_INSTR_CREATE(opcode) jinstruction_arm7_create(0x##opcode, \
        arm7_##opcode##_execute, arm7_##opcode##_das, arm7_##opcode##_as)

#endif/*JINSTRUCTION_ARM7_H*/

