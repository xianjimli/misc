/*
 * File:   start.s 
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  vector handlers. 
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
 * 2009-1-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */
	.text
	.code 32
	.align 0
	.global _start
	.extern os_init,shell_main,swi_dispach,irq_dispatch,firq_dispatch

_start:
	b reset_handler
	b undef_instr_handler
	b swi_handler
	b prefetch_abort_handler
	b data_abort_handler
	b dummy_handler
	b irq_handler
	b fiq_handler

reset_handler:
	bl  init_fiq_registers
	bl  setup_stack
	bl  os_init
	msr CPSR_c,#0x50
	bl  shell_main 

undef_instr_handler:
	b undef_instr_handler
	
swi_handler:
	stmfd   sp!,       {r0-r12,lr}
	ldr     r10,       [lr,#-4]
	bic     r10,       r10,#0xff000000
	mov     r0,        r10
	mov     r1,        sp
	mrs     r2,        SPSR
	stmfd   sp!,       {r2}
	bl      swi_dispatch
	ldmfd   sp!,       {r2}
	msr     SPSR_cxsf, r2
	ldmfd   sp!,       {r0-r12,pc}

prefetch_abort_handler:
	b prefetch_abort_handler

data_abort_handler:
	b data_abort_handler

dummy_handler:
	b dummy_handler

irq_handler:
	stmfd   sp!,       {r0-r12,lr}
	mrs     r2,        SPSR
	stmfd   sp!,       {r2}
	bl      irq_dispach
	ldmfd   sp!,       {r2}
	msr     SPSR_cxsf, r2
	ldmfd   sp!,       {r0-r12,pc}

fiq_handler:
	stmfd   sp!,       {r0-r12,lr}
	mrs     r2,        SPSR
	stmfd   sp!,       {r2}
	bl      firq_dispatch
	ldmfd   sp!,       {r2}
	msr     SPSR_cxsf, r2
	ldmfd   sp!,       {r0-r12,pc}

switch_to_fiq_mode:
	mov     r3,     lr
	mrs     r1,     CPSR
	bic     r1,     r1,   #0x1f
	orr     r1,     r1,   #0x11
	msr     CPSR_c, r1
	mov     pc,     r3

switch_to_svc_mode:
	mov     r3,     lr
	mrs     r1,     CPSR
	bic     r1,     r1, #0x1f
	orr     r1,     r1, #0x13
	msr     CPSR_c, r1
	mov     pc,     r3

init_fiq_registers:
	mov     r2,     lr 
	bl      switch_to_fiq_mode
	mov     r8,     #0           
	mov     r9,     #0          
	mov     r10,    #0        
	bl      switch_to_svc_mode 
	mov     pc,     r2

setup_stack:
	mov sp,     #0x1c000
	msr CPSR_c, #0xdf
	mov sp,     #0x18000
	msr CPSR_c, #0xd2
	mov sp,     #0x14000
	msr CPSR_c, #0xd3
	.end
