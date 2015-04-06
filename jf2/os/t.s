
jos.elf:     file format elf32-littlearm

Disassembly of section .text:

00000000 <_start>:
       0:	ea000006 	b	20 <reset_handler>
       4:	ea00000a 	b	34 <undef_instr_handler>
       8:	ea00000a 	b	38 <swi_handler>
       c:	ea000014 	b	64 <prefetch_abort_handler>
      10:	ea000014 	b	68 <data_abort_handler>
      14:	ea000014 	b	6c <dummy_handler>
      18:	ea000014 	b	70 <irq_handler>
      1c:	ea00001a 	b	8c <fiq_handler>

00000020 <reset_handler>:
      20:	eb00002c 	bl	d8 <init_fiq_registers>
      24:	eb000032 	bl	f4 <setup_stack>
      28:	eb0000a1 	bl	2b4 <os_init>
      2c:	e321f050 	msr	CPSR_c, #80	; 0x50
      30:	eb0000a9 	bl	2dc <shell_main>

00000034 <undef_instr_handler>:
      34:	eafffffe 	b	34 <undef_instr_handler>

00000038 <swi_handler>:
      38:	e92d5fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
      3c:	e51ea004 	ldr	sl, [lr, #-4]
      40:	e3caa4ff 	bic	sl, sl, #-16777216	; 0xff000000
      44:	e1a0000a 	mov	r0, sl
      48:	e1a0100d 	mov	r1, sp
      4c:	e14f2000 	mrs	r2, SPSR
      50:	e92d0004 	stmdb	sp!, {r2}
      54:	eb000032 	bl	124 <swi_dispatch>
      58:	e8bd0004 	ldmia	sp!, {r2}
      5c:	e16ff002 	msr	SPSR_fsxc, r2
      60:	e8bd9fff 	ldmia	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, pc}

00000064 <prefetch_abort_handler>:
      64:	eafffffe 	b	64 <prefetch_abort_handler>

00000068 <data_abort_handler>:
      68:	eafffffe 	b	68 <data_abort_handler>

0000006c <dummy_handler>:
      6c:	eafffffe 	b	6c <dummy_handler>

00000070 <irq_handler>:
      70:	e92d5fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
      74:	e14f2000 	mrs	r2, SPSR
      78:	e92d0004 	stmdb	sp!, {r2}
      7c:	eb000055 	bl	1d8 <irq_dispach>
      80:	e8bd0004 	ldmia	sp!, {r2}
      84:	e16ff002 	msr	SPSR_fsxc, r2
      88:	e8bd9fff 	ldmia	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, pc}

0000008c <fiq_handler>:
      8c:	e92d5fff 	stmdb	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, lr}
      90:	e14f2000 	mrs	r2, SPSR
      94:	e92d0004 	stmdb	sp!, {r2}
      98:	eb00003e 	bl	198 <firq_dispatch>
      9c:	e8bd0004 	ldmia	sp!, {r2}
      a0:	e16ff002 	msr	SPSR_fsxc, r2
      a4:	e8bd9fff 	ldmia	sp!, {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, sl, fp, ip, pc}

000000a8 <switch_to_fiq_mode>:
      a8:	e1a0300e 	mov	r3, lr
      ac:	e10f1000 	mrs	r1, CPSR
      b0:	e3c1101f 	bic	r1, r1, #31	; 0x1f
      b4:	e3811011 	orr	r1, r1, #17	; 0x11
      b8:	e121f001 	msr	CPSR_c, r1
      bc:	e1a0f003 	mov	pc, r3

000000c0 <switch_to_svc_mode>:
      c0:	e1a0300e 	mov	r3, lr
      c4:	e10f1000 	mrs	r1, CPSR
      c8:	e3c1101f 	bic	r1, r1, #31	; 0x1f
      cc:	e3811013 	orr	r1, r1, #19	; 0x13
      d0:	e121f001 	msr	CPSR_c, r1
      d4:	e1a0f003 	mov	pc, r3

000000d8 <init_fiq_registers>:
      d8:	e1a0200e 	mov	r2, lr
      dc:	ebfffff1 	bl	a8 <switch_to_fiq_mode>
      e0:	e3a08000 	mov	r8, #0	; 0x0
      e4:	e3a09000 	mov	r9, #0	; 0x0
      e8:	e3a0a000 	mov	sl, #0	; 0x0
      ec:	ebfffff3 	bl	c0 <switch_to_svc_mode>
      f0:	e1a0f002 	mov	pc, r2

000000f4 <setup_stack>:
      f4:	e3a0d907 	mov	sp, #114688	; 0x1c000
      f8:	e321f0df 	msr	CPSR_c, #223	; 0xdf
      fc:	e3a0d906 	mov	sp, #98304	; 0x18000
     100:	e321f0d2 	msr	CPSR_c, #210	; 0xd2
     104:	e3a0d905 	mov	sp, #81920	; 0x14000
     108:	e321f0d3 	msr	CPSR_c, #211	; 0xd3

0000010c <_syscall>:
     10c:	e92d501f 	stmdb	sp!, {r0, r1, r2, r3, r4, ip, lr}
     110:	e1a04000 	mov	r4, r0
     114:	e894000f 	ldmia	r4, {r0, r1, r2, r3}
     118:	ef000000 	svc	0x00000000
     11c:	e884000f 	stmia	r4, {r0, r1, r2, r3}
     120:	e8bd901f 	ldmia	sp!, {r0, r1, r2, r3, r4, ip, pc}

00000124 <swi_dispatch>:
	jword_t pc; 
} SwiRegs;

int swi_dispatch(jword_t swi_no, SwiRegs* regs)
{
     124:	e1a0c00d 	mov	ip, sp
     128:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     12c:	e24cb004 	sub	fp, ip, #4	; 0x4
     130:	e1a04001 	mov	r4, r1
	os_trace(__func__, __LINE__, "enter");
     134:	e59f0048 	ldr	r0, [pc, #72]	; 184 <.text+0x184>
     138:	e3a0102c 	mov	r1, #44	; 0x2c
     13c:	e59f2044 	ldr	r2, [pc, #68]	; 188 <.text+0x188>
     140:	eb000034 	bl	218 <os_trace>

	switch(regs->r[0])
     144:	e5943000 	ldr	r3, [r4]
     148:	e3530001 	cmp	r3, #1	; 0x1
     14c:	1a000002 	bne	15c <swi_dispatch+0x38>
	{
		case SYS_TRACE:
		{
			os_trace((const char*)regs->r[1], regs->r[2], (const char*)regs->r[3]);
     150:	e9940007 	ldmib	r4, {r0, r1, r2}
     154:	eb00002f 	bl	218 <os_trace>
     158:	ea000003 	b	16c <swi_dispatch+0x48>
			break;
		}
		default:
		{
			os_trace(__func__, __LINE__, "unhandle.");
     15c:	e59f0020 	ldr	r0, [pc, #32]	; 184 <.text+0x184>
     160:	e3a01037 	mov	r1, #55	; 0x37
     164:	e59f2020 	ldr	r2, [pc, #32]	; 18c <.text+0x18c>
     168:	eb00002a 	bl	218 <os_trace>
			break;
		}
	}
	os_trace(__func__, __LINE__, "leave");
     16c:	e59f0010 	ldr	r0, [pc, #16]	; 184 <.text+0x184>
     170:	e3a0103b 	mov	r1, #59	; 0x3b
     174:	e59f2014 	ldr	r2, [pc, #20]	; 190 <.text+0x190>
     178:	eb000026 	bl	218 <os_trace>

	return 0;
}
     17c:	e3a00000 	mov	r0, #0	; 0x0
     180:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
     184:	00001b50 	andeq	r1, r0, r0, asr fp
     188:	00001b30 	andeq	r1, r0, r0, lsr fp
     18c:	00001b38 	andeq	r1, r0, r8, lsr fp
     190:	00001b48 	andeq	r1, r0, r8, asr #22

00000194 <irq_real_dispach>:

static void irq_real_dispach(void)
{
	return;
}
     194:	e12fff1e 	bx	lr

00000198 <firq_dispatch>:

void irq_dispach(void)
{
	os_trace(__func__, __LINE__, "irq enter");
	irq_real_dispach();
	os_trace(__func__, __LINE__, "irq leave");

	return;
}

void firq_dispatch(void)
{
     198:	e1a0c00d 	mov	ip, sp
     19c:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     1a0:	e24cb004 	sub	fp, ip, #4	; 0x4
	os_trace(__func__, __LINE__, "irq enter");
     1a4:	e59f4020 	ldr	r4, [pc, #32]	; 1cc <.text+0x1cc>
     1a8:	e1a00004 	mov	r0, r4
     1ac:	e3a01013 	mov	r1, #19	; 0x13
     1b0:	e59f2018 	ldr	r2, [pc, #24]	; 1d0 <.text+0x1d0>
     1b4:	eb000017 	bl	218 <os_trace>
	irq_real_dispach();
	os_trace(__func__, __LINE__, "irq leave");
     1b8:	e1a00004 	mov	r0, r4
     1bc:	e3a01015 	mov	r1, #21	; 0x15
     1c0:	e59f200c 	ldr	r2, [pc, #12]	; 1d4 <.text+0x1d4>
     1c4:	eb000013 	bl	218 <os_trace>
	
	return;
}
     1c8:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
     1cc:	00001b80 	andeq	r1, r0, r0, lsl #23
     1d0:	00001b60 	andeq	r1, r0, r0, ror #22
     1d4:	00001b70 	andeq	r1, r0, r0, ror fp

000001d8 <irq_dispach>:
     1d8:	e1a0c00d 	mov	ip, sp
     1dc:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     1e0:	e24cb004 	sub	fp, ip, #4	; 0x4
     1e4:	e59f4020 	ldr	r4, [pc, #32]	; 20c <.text+0x20c>
     1e8:	e1a00004 	mov	r0, r4
     1ec:	e3a0100a 	mov	r1, #10	; 0xa
     1f0:	e59f2018 	ldr	r2, [pc, #24]	; 210 <.text+0x210>
     1f4:	eb000007 	bl	218 <os_trace>
     1f8:	e1a00004 	mov	r0, r4
     1fc:	e3a0100c 	mov	r1, #12	; 0xc
     200:	e59f200c 	ldr	r2, [pc, #12]	; 214 <.text+0x214>
     204:	eb000003 	bl	218 <os_trace>
     208:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
     20c:	00001b90 	muleq	r0, r0, fp
     210:	00001b60 	andeq	r1, r0, r0, ror #22
     214:	00001b70 	andeq	r1, r0, r0, ror fp

00000218 <os_trace>:
 */
#include <jtype.h>

void os_trace(const char* func, int line, const char* str)
{
     218:	e1a0c002 	mov	ip, r2
	int i = 0;
	int* tx_port = (int*)(J_UART0_BASE + J_UTXBUF);

	for(i = 0; func[i]; i++)
     21c:	e5d03000 	ldrb	r3, [r0]
     220:	e3530000 	cmp	r3, #0	; 0x0
     224:	0a000007 	beq	248 <os_trace+0x30>
     228:	e3a02000 	mov	r2, #0	; 0x0
     22c:	e3e01303 	mvn	r1, #201326592	; 0xc000000
     230:	e2411a02 	sub	r1, r1, #8192	; 0x2000
	{
		*tx_port = func[i];
     234:	e5013ff3 	str	r3, [r1, #-4083]
     238:	e2822001 	add	r2, r2, #1	; 0x1
     23c:	e7d23000 	ldrb	r3, [r2, r0]
     240:	e3530000 	cmp	r3, #0	; 0x0
     244:	1afffffa 	bne	234 <os_trace+0x1c>
	}
	*tx_port = ':';
     248:	e3e03303 	mvn	r3, #201326592	; 0xc000000
     24c:	e2433a02 	sub	r3, r3, #8192	; 0x2000
     250:	e3a0203a 	mov	r2, #58	; 0x3a
     254:	e5032ff3 	str	r2, [r3, #-4083]
	for(i = 0; str[i]; i++)
     258:	e5dc3000 	ldrb	r3, [ip]
     25c:	e3530000 	cmp	r3, #0	; 0x0
     260:	0a000007 	beq	284 <os_trace+0x6c>
     264:	e242203a 	sub	r2, r2, #58	; 0x3a
     268:	e3e01303 	mvn	r1, #201326592	; 0xc000000
     26c:	e2411a02 	sub	r1, r1, #8192	; 0x2000
	{
		*tx_port = str[i];
     270:	e5013ff3 	str	r3, [r1, #-4083]
     274:	e2822001 	add	r2, r2, #1	; 0x1
     278:	e7d2300c 	ldrb	r3, [r2, ip]
     27c:	e3530000 	cmp	r3, #0	; 0x0
     280:	1afffffa 	bne	270 <os_trace+0x58>
	}
	*tx_port = '\n';
     284:	e3e03303 	mvn	r3, #201326592	; 0xc000000
     288:	e2433a02 	sub	r3, r3, #8192	; 0x2000
     28c:	e3a0200a 	mov	r2, #10	; 0xa
     290:	e5032ff3 	str	r2, [r3, #-4083]

	return;
}
     294:	e12fff1e 	bx	lr

00000298 <kernel_mem_init>:

JRet kernel_mem_init(char* start, jword_t length)
{
	return JRET_OK;
}
     298:	e3a00000 	mov	r0, #0	; 0x0
     29c:	e12fff1e 	bx	lr

000002a0 <kernel_mem_alloc>:

void* kernel_mem_alloc(jword_t length)
{
	return NULL;
}
     2a0:	e3a00000 	mov	r0, #0	; 0x0
     2a4:	e12fff1e 	bx	lr

000002a8 <kernel_mem_free>:

void kernel_mem_free(void* ptr)
{
	return;
}
     2a8:	e12fff1e 	bx	lr

000002ac <kernel_mem_realloc>:

void* kernel_mem_realloc(void* ptr, jword_t length)
{
	return NULL;
}
     2ac:	e3a00000 	mov	r0, #0	; 0x0
     2b0:	e12fff1e 	bx	lr

000002b4 <os_init>:

#include <trace.h>

void os_init(void)
{
     2b4:	e1a0c00d 	mov	ip, sp
     2b8:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     2bc:	e24cb004 	sub	fp, ip, #4	; 0x4
	os_trace(__func__, __LINE__, "hello jos!");
     2c0:	e59f000c 	ldr	r0, [pc, #12]	; 2d4 <.text+0x2d4>
     2c4:	e3a01024 	mov	r1, #36	; 0x24
     2c8:	e59f2008 	ldr	r2, [pc, #8]	; 2d8 <.text+0x2d8>
     2cc:	ebffffd1 	bl	218 <os_trace>
	return;
}
     2d0:	e89da800 	ldmia	sp, {fp, sp, pc}
     2d4:	00001bb0 	streqh	r1, [r0], -r0
     2d8:	00001ba0 	andeq	r1, r0, r0, lsr #23

000002dc <shell_main>:
#include <stdio.h>
extern void test_all(void);

void shell_main(void)
{
     2dc:	e1a0c00d 	mov	ip, sp
     2e0:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     2e4:	e24cb004 	sub	fp, ip, #4	; 0x4
     2e8:	e24dd010 	sub	sp, sp, #16	; 0x10
	int i = 0;
	char str[12];
	jmemset(str, 'a', 11);
     2ec:	e24b0018 	sub	r0, fp, #24	; 0x18
     2f0:	e3a01061 	mov	r1, #97	; 0x61
     2f4:	e3a0200b 	mov	r2, #11	; 0xb
     2f8:	eb0000e9 	bl	6a4 <jmemset>
	str[11] = '\0';
     2fc:	e3a03000 	mov	r3, #0	; 0x0
     300:	e54b300d 	strb	r3, [fp, #-13]

//	jitoa_test();
//	return 0;
	test_all();
     304:	eb00031a 	bl	f74 <test_all>

	return;
	while(1)
	{
		i++;
		jprintf("aaa:%d\n", __func__, __LINE__);
	}

	return;
}
     308:	e24bd00c 	sub	sp, fp, #12	; 0xc
     30c:	e89da800 	ldmia	sp, {fp, sp, pc}

00000310 <syscall>:

extern int _syscall(SysCallParam* param);

int syscall(jword_t p1, jword_t p2, jword_t p3, jword_t p4)
{
     310:	e1a0c00d 	mov	ip, sp
     314:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     318:	e24cb004 	sub	fp, ip, #4	; 0x4
     31c:	e24dd010 	sub	sp, sp, #16	; 0x10
	SysCallParam param = {0};
	param.r[0] = p1;
     320:	e50b001c 	str	r0, [fp, #-28]
	param.r[1] = p2;
     324:	e50b1018 	str	r1, [fp, #-24]
	param.r[2] = p3;
     328:	e50b2014 	str	r2, [fp, #-20]
	param.r[3] = p4;
     32c:	e50b3010 	str	r3, [fp, #-16]

	return _syscall(&param);
     330:	e24b001c 	sub	r0, fp, #28	; 0x1c
     334:	ebffff74 	bl	10c <_syscall>
}
     338:	e24bd00c 	sub	sp, fp, #12	; 0xc
     33c:	e89da800 	ldmia	sp, {fp, sp, pc}

00000340 <jstrtoul_h>:
	
}

static long int jstrtoul_h(const char *nptr, char **endptr)
{
     340:	e92d4010 	stmdb	sp!, {r4, lr}
     344:	e1a04001 	mov	r4, r1
     348:	e3a01000 	mov	r1, #0	; 0x0
     34c:	ea000007 	b	370 <jstrtoul_h+0x30>
	int digit = 0;
	long int value = 0;
	const char* p = nptr;

	while(((*p >= '0') && (*p <= '9')) || ((*p >= 'a') && (*p <= 'f')) || ((*p >= 'A') && (*p <= 'F')))
	{
		if(*p >= '0' && *p <= '9')
     350:	e35c0000 	cmp	ip, #0	; 0x0
		{
			digit = *p - '0';
     354:	12423030 	subne	r3, r2, #48	; 0x30
     358:	1a000002 	bne	368 <jstrtoul_h+0x28>
		}
		else if((*p >= 'a' && *p <= 'f'))
     35c:	e35e0000 	cmp	lr, #0	; 0x0
		{
			digit = *p - 'a' + 10;
     360:	12423057 	subne	r3, r2, #87	; 0x57
		}
		else 
		{
			digit = *p -'A' + 10;
     364:	02423037 	subeq	r3, r2, #55	; 0x37
		}

		value = (value << 4) + digit;
     368:	e0831201 	add	r1, r3, r1, lsl #4
		p++;
     36c:	e2800001 	add	r0, r0, #1	; 0x1
     370:	e5d02000 	ldrb	r2, [r0]
     374:	e2423030 	sub	r3, r2, #48	; 0x30
     378:	e3530009 	cmp	r3, #9	; 0x9
     37c:	83a0c000 	movhi	ip, #0	; 0x0
     380:	93a0c001 	movls	ip, #1	; 0x1
     384:	e2423061 	sub	r3, r2, #97	; 0x61
     388:	e3530005 	cmp	r3, #5	; 0x5
     38c:	83a0e000 	movhi	lr, #0	; 0x0
     390:	93a0e001 	movls	lr, #1	; 0x1
     394:	e19c300e 	orrs	r3, ip, lr
     398:	1affffec 	bne	350 <jstrtoul_h+0x10>
     39c:	e2423041 	sub	r3, r2, #65	; 0x41
     3a0:	e3530005 	cmp	r3, #5	; 0x5
     3a4:	9affffe9 	bls	350 <jstrtoul_h+0x10>
	}

	if(endptr != NULL)
     3a8:	e3540000 	cmp	r4, #0	; 0x0
	{
		*endptr = (char*)p;
     3ac:	15840000 	strne	r0, [r4]
	}

	return value;
}
     3b0:	e1a00001 	mov	r0, r1
     3b4:	e8bd8010 	ldmia	sp!, {r4, pc}

000003b8 <jstrtoul>:

unsigned long int jstrtoul(const char *nptr, char **endptr, int base)
{
     3b8:	e1a0c00d 	mov	ip, sp
     3bc:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     3c0:	e24cb004 	sub	fp, ip, #4	; 0x4
	if(nptr[0] == '0')
     3c4:	e5d0c000 	ldrb	ip, [r0]
     3c8:	e35c0030 	cmp	ip, #48	; 0x30
     3cc:	1a000016 	bne	42c <jstrtoul+0x74>
	{
		if(nptr[1] == 'x')
     3d0:	e280c001 	add	ip, r0, #1	; 0x1
     3d4:	e5d02001 	ldrb	r2, [r0, #1]
     3d8:	e3520078 	cmp	r2, #120	; 0x78
     3dc:	0a000004 	beq	3f4 <jstrtoul+0x3c>
     3e0:	e2423030 	sub	r3, r2, #48	; 0x30
     3e4:	e3530007 	cmp	r3, #7	; 0x7
     3e8:	83a00000 	movhi	r0, #0	; 0x0
     3ec:	8a00000a 	bhi	41c <jstrtoul+0x64>
     3f0:	ea000002 	b	400 <jstrtoul+0x48>
		{
			return jstrtoul_h(nptr+2, endptr);
     3f4:	e2800002 	add	r0, r0, #2	; 0x2
     3f8:	ebffffd0 	bl	340 <jstrtoul_h>
     3fc:	e89da800 	ldmia	sp, {fp, sp, pc}
     400:	e3a00000 	mov	r0, #0	; 0x0
     404:	e0823180 	add	r3, r2, r0, lsl #3
     408:	e2430030 	sub	r0, r3, #48	; 0x30
     40c:	e5fc2001 	ldrb	r2, [ip, #1]!
     410:	e2423030 	sub	r3, r2, #48	; 0x30
     414:	e3530007 	cmp	r3, #7	; 0x7
     418:	9afffff9 	bls	404 <jstrtoul+0x4c>
     41c:	e3510000 	cmp	r1, #0	; 0x0
     420:	0a000016 	beq	480 <jstrtoul+0xc8>
     424:	e581c000 	str	ip, [r1]
     428:	e89da800 	ldmia	sp, {fp, sp, pc}
		}
		else
		{
			return jstrtoul_o(nptr+1, endptr);
		}
	}
	else if(base == 16)
     42c:	e3520010 	cmp	r2, #16	; 0x10
     430:	0a000004 	beq	448 <jstrtoul+0x90>
     434:	e24c3030 	sub	r3, ip, #48	; 0x30
     438:	e3530009 	cmp	r3, #9	; 0x9
     43c:	83a02000 	movhi	r2, #0	; 0x0
     440:	8a00000b 	bhi	474 <jstrtoul+0xbc>
     444:	ea000001 	b	450 <jstrtoul+0x98>
	{
		return jstrtoul_h(nptr, endptr);
     448:	ebffffbc 	bl	340 <jstrtoul_h>
     44c:	e89da800 	ldmia	sp, {fp, sp, pc}
     450:	e3a02000 	mov	r2, #0	; 0x0
     454:	e1a03082 	mov	r3, r2, lsl #1
     458:	e0833182 	add	r3, r3, r2, lsl #3
     45c:	e083300c 	add	r3, r3, ip
     460:	e2432030 	sub	r2, r3, #48	; 0x30
     464:	e5f0c001 	ldrb	ip, [r0, #1]!
     468:	e24c3030 	sub	r3, ip, #48	; 0x30
     46c:	e3530009 	cmp	r3, #9	; 0x9
     470:	9afffff7 	bls	454 <jstrtoul+0x9c>
     474:	e3510000 	cmp	r1, #0	; 0x0
     478:	15810000 	strne	r0, [r1]
	}
	else
	{
		return jstrtoul_d(nptr, endptr);
     47c:	e1a00002 	mov	r0, r2
	}
}
     480:	e89da800 	ldmia	sp, {fp, sp, pc}

00000484 <jstrtol>:

long int jstrtol(const char *nptr, char **endptr, int base)
{
     484:	e1a0c00d 	mov	ip, sp
     488:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     48c:	e24cb004 	sub	fp, ip, #4	; 0x4
	long int value = 0;
	const char* p = nptr;

	if(nptr == NULL) return 0;
     490:	e2504000 	subs	r4, r0, #0	; 0x0
     494:	1a000001 	bne	4a0 <jstrtol+0x1c>
     498:	e1a00004 	mov	r0, r4
     49c:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}

	while(*nptr == ' ' || *nptr == '\t') nptr++;
     4a0:	e5d43000 	ldrb	r3, [r4]
     4a4:	e3530020 	cmp	r3, #32	; 0x20
     4a8:	13530009 	cmpne	r3, #9	; 0x9
     4ac:	1a000005 	bne	4c8 <jstrtol+0x44>
     4b0:	e1a00004 	mov	r0, r4
     4b4:	e5f03001 	ldrb	r3, [r0, #1]!
     4b8:	e3530009 	cmp	r3, #9	; 0x9
     4bc:	13530020 	cmpne	r3, #32	; 0x20
     4c0:	0afffffb 	beq	4b4 <jstrtol+0x30>
     4c4:	e1a04000 	mov	r4, r0

	p = nptr;
	if(*p == '+' || *p == '-')
     4c8:	e353002d 	cmp	r3, #45	; 0x2d
     4cc:	1353002b 	cmpne	r3, #43	; 0x2b
     4d0:	11a00004 	movne	r0, r4
	{
		p++;
     4d4:	02840001 	addeq	r0, r4, #1	; 0x1
	}

	value = jstrtoul(p, endptr, base);
     4d8:	ebffffb6 	bl	3b8 <jstrtoul>

	return *nptr == '-' ? -value : value;
     4dc:	e5d43000 	ldrb	r3, [r4]
     4e0:	e353002d 	cmp	r3, #45	; 0x2d
     4e4:	02600000 	rsbeq	r0, r0, #0	; 0x0
}
     4e8:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}

000004ec <jatoi>:

int jatoi(const char* str)
{
     4ec:	e1a0c00d 	mov	ip, sp
     4f0:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     4f4:	e24cb004 	sub	fp, ip, #4	; 0x4
	return jstrtol(str, NULL, 0);
     4f8:	e3a01000 	mov	r1, #0	; 0x0
     4fc:	e1a02001 	mov	r2, r1
     500:	ebffffdf 	bl	484 <jstrtol>
}
     504:	e89da800 	ldmia	sp, {fp, sp, pc}

00000508 <jitoa_ex>:

static int mod(int a, int b)
{
	if(b == 8)
	{
		return a & 0x07;
	}

	if(b == 16)
	{
		return a & 0x0f;
	}

	if(b == 10)
	{
		return a % 10;
	}
	/*FIXME*/
	return 0;
}

static int div(int a, int b)
{
	if(b == 8)
	{
		return a >> 3;
	}
	
	if(b == 16)
	{
		return a >> 4;
	}

	if(b == 10)
	{
		return b / 10;
	}

	return 0;
}

char *jitoa_ex(int v, char* str, int prefix, int base, int upper)
{
     508:	e92d41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
     50c:	e24dd020 	sub	sp, sp, #32	; 0x20
     510:	e1a04002 	mov	r4, r2
	char a = upper ? 'A' : 'a';
     514:	e59d2038 	ldr	r2, [sp, #56]
     518:	e3520000 	cmp	r2, #0	; 0x0
     51c:	03a05061 	moveq	r5, #97	; 0x61
     520:	13a05041 	movne	r5, #65	; 0x41
	char c = 0;
	char rnum[32];
	char* d = str;
	char* s = rnum;

	base = base == 0 ? 10 : base;
     524:	e3530000 	cmp	r3, #0	; 0x0
     528:	11a0c003 	movne	ip, r3
     52c:	03a0c00a 	moveq	ip, #10	; 0xa

	if(str == NULL)
     530:	e3510000 	cmp	r1, #0	; 0x0
     534:	0a00004b 	beq	668 <jitoa_ex+0x160>
	{
		return str;
	}
	
	if(v < 0)
     538:	e3500000 	cmp	r0, #0	; 0x0
     53c:	a1a0e001 	movge	lr, r1
	{
		*d++ = '-'; 
     540:	b1a0e001 	movlt	lr, r1
     544:	b3a0302d 	movlt	r3, #45	; 0x2d
     548:	b4ce3001 	strltb	r3, [lr], #1
		v = -v;
     54c:	b2600000 	rsblt	r0, r0, #0	; 0x0
	}

	if(prefix)
     550:	e3540000 	cmp	r4, #0	; 0x0
     554:	0a00000b 	beq	588 <jitoa_ex+0x80>
	{
		if(base == 16)
     558:	e35c0010 	cmp	ip, #16	; 0x10
     55c:	1a000006 	bne	57c <jitoa_ex+0x74>
		{
			*d++ = '0';
     560:	e1a0300e 	mov	r3, lr
     564:	e3a02030 	mov	r2, #48	; 0x30
     568:	e4c32001 	strb	r2, [r3], #1
			*d++ = 'x';
     56c:	e2822048 	add	r2, r2, #72	; 0x48
     570:	e5ce2001 	strb	r2, [lr, #1]
     574:	e283e001 	add	lr, r3, #1	; 0x1
     578:	ea000002 	b	588 <jitoa_ex+0x80>
		}
		else if(base == 8)
     57c:	e35c0008 	cmp	ip, #8	; 0x8
		{
			*d++ = '0';
     580:	03a03030 	moveq	r3, #48	; 0x30
     584:	04ce3001 	streqb	r3, [lr], #1
		}
	}

	for(; v > 0; s++)
     588:	e3500000 	cmp	r0, #0	; 0x0
     58c:	d1a0400d 	movle	r4, sp
     590:	c1a0400d 	movgt	r4, sp
     594:	c59f60d8 	ldrgt	r6, [pc, #216]	; 674 <.text+0x674>
     598:	c3a0700a 	movgt	r7, #10	; 0xa
     59c:	da000024 	ble	634 <jitoa_ex+0x12c>
     5a0:	e35c0008 	cmp	ip, #8	; 0x8
     5a4:	02003007 	andeq	r3, r0, #7	; 0x7
     5a8:	0a00000a 	beq	5d8 <jitoa_ex+0xd0>
     5ac:	e35c0010 	cmp	ip, #16	; 0x10
     5b0:	0200300f 	andeq	r3, r0, #15	; 0xf
     5b4:	0a000007 	beq	5d8 <jitoa_ex+0xd0>
     5b8:	e35c000a 	cmp	ip, #10	; 0xa
     5bc:	13a03000 	movne	r3, #0	; 0x0
     5c0:	1a00000a 	bne	5f0 <jitoa_ex+0xe8>
     5c4:	e0c32096 	smull	r2, r3, r6, r0
     5c8:	e1a02fc0 	mov	r2, r0, asr #31
     5cc:	e0623143 	rsb	r3, r2, r3, asr #2
     5d0:	e0030397 	mul	r3, r7, r3
     5d4:	e0633000 	rsb	r3, r3, r0
	{
		if((c = mod(v, base)) < 10)
     5d8:	e20330ff 	and	r3, r3, #255	; 0xff
     5dc:	e3530009 	cmp	r3, #9	; 0x9
		{
			c += '0';
		}
		else
		{
			c = c - 10 + a;
     5e0:	80853003 	addhi	r3, r5, r3
     5e4:	8243300a 	subhi	r3, r3, #10	; 0xa
     5e8:	820330ff 	andhi	r3, r3, #255	; 0xff
     5ec:	8a000001 	bhi	5f8 <jitoa_ex+0xf0>
     5f0:	e2833030 	add	r3, r3, #48	; 0x30
     5f4:	e20330ff 	and	r3, r3, #255	; 0xff
		}

		*s = c;
     5f8:	e5c43000 	strb	r3, [r4]
     5fc:	e35c0008 	cmp	ip, #8	; 0x8
     600:	01a001c0 	moveq	r0, r0, asr #3
     604:	0a000007 	beq	628 <jitoa_ex+0x120>
     608:	e35c0010 	cmp	ip, #16	; 0x10
     60c:	01a00240 	moveq	r0, r0, asr #4
     610:	0a000004 	beq	628 <jitoa_ex+0x120>
     614:	e35c000a 	cmp	ip, #10	; 0xa
     618:	1a000010 	bne	660 <jitoa_ex+0x158>
     61c:	e2844001 	add	r4, r4, #1	; 0x1
     620:	e3a00001 	mov	r0, #1	; 0x1
     624:	eaffffdd 	b	5a0 <jitoa_ex+0x98>
     628:	e2844001 	add	r4, r4, #1	; 0x1
     62c:	e3500000 	cmp	r0, #0	; 0x0
     630:	caffffda 	bgt	5a0 <jitoa_ex+0x98>
		v = div(v, base);
	}
	s--;
     634:	e2442001 	sub	r2, r4, #1	; 0x1

	for(; s >= rnum; s--, d++)
     638:	e15d0002 	cmp	sp, r2
     63c:	8a000004 	bhi	654 <jitoa_ex+0x14c>
     640:	e1a0c00d 	mov	ip, sp
	{
		*d = *s;
     644:	e4523001 	ldrb	r3, [r2], #-1
     648:	e4ce3001 	strb	r3, [lr], #1
     64c:	e15c0002 	cmp	ip, r2
     650:	9afffffb 	bls	644 <jitoa_ex+0x13c>
	}
	*d = '\0';
     654:	e3a03000 	mov	r3, #0	; 0x0
     658:	e5ce3000 	strb	r3, [lr]
     65c:	ea000001 	b	668 <jitoa_ex+0x160>
     660:	e2844001 	add	r4, r4, #1	; 0x1
     664:	eafffff2 	b	634 <jitoa_ex+0x12c>

	return str;
}
     668:	e1a00001 	mov	r0, r1
     66c:	e28dd020 	add	sp, sp, #32	; 0x20
     670:	e8bd81f0 	ldmia	sp!, {r4, r5, r6, r7, r8, pc}
     674:	66666667 	strvsbt	r6, [r6], -r7, ror #12

00000678 <jitoa>:

char *jitoa(int v, char* str, int base)
{
     678:	e1a0c00d 	mov	ip, sp
     67c:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     680:	e24cb004 	sub	fp, ip, #4	; 0x4
     684:	e24dd008 	sub	sp, sp, #8	; 0x8
     688:	e1a03002 	mov	r3, r2
	return jitoa_ex(v, str, 0, base, 0);
     68c:	e3a02000 	mov	r2, #0	; 0x0
     690:	e58d2000 	str	r2, [sp]
     694:	ebffff9b 	bl	508 <jitoa_ex>
}
     698:	e24bd00c 	sub	sp, fp, #12	; 0xc
     69c:	e89da800 	ldmia	sp, {fp, sp, pc}

000006a0 <raise>:

void raise(void)
{
}
     6a0:	e12fff1e 	bx	lr

000006a4 <jmemset>:
#include <stdlib.h>

void *jmemset(void *s, int c, size_t n)
{
	if(s != NULL)
     6a4:	e3500000 	cmp	r0, #0	; 0x0
     6a8:	012fff1e 	bxeq	lr
	{
		size_t i = 0;

		for(i = 0; i < n; i++)
     6ac:	e3520000 	cmp	r2, #0	; 0x0
     6b0:	012fff1e 	bxeq	lr
     6b4:	e3a03000 	mov	r3, #0	; 0x0
		{
			((char*)s)[i] = (char)c;
     6b8:	e7c31000 	strb	r1, [r3, r0]
     6bc:	e2833001 	add	r3, r3, #1	; 0x1
     6c0:	e1520003 	cmp	r2, r3
     6c4:	1afffffb 	bne	6b8 <jmemset+0x14>
		}
	}

	return s;
}
     6c8:	e12fff1e 	bx	lr

000006cc <jmemcpy>:

void *jmemcpy(void *dest, const void *src, size_t n)
{
     6cc:	e92d4010 	stmdb	sp!, {r4, lr}
	if(dest != NULL && src != NULL)
     6d0:	e1a0e000 	mov	lr, r0
     6d4:	e1a0c001 	mov	ip, r1
     6d8:	e3500000 	cmp	r0, #0	; 0x0
     6dc:	13510000 	cmpne	r1, #0	; 0x0
     6e0:	0a000007 	beq	704 <jmemcpy+0x38>
	{
		size_t i = 0;
		for(i = 0; i < n; i++)
     6e4:	e3520000 	cmp	r2, #0	; 0x0
     6e8:	0a000005 	beq	704 <jmemcpy+0x38>
     6ec:	e3a01000 	mov	r1, #0	; 0x0
		{
			((char*)dest)[i] = ((char*)src)[i];
     6f0:	e7d1300c 	ldrb	r3, [r1, ip]
     6f4:	e7c1300e 	strb	r3, [r1, lr]
     6f8:	e2811001 	add	r1, r1, #1	; 0x1
     6fc:	e1520001 	cmp	r2, r1
     700:	1afffffa 	bne	6f0 <jmemcpy+0x24>
		}
	}

	return dest;
}
     704:	e1a0000e 	mov	r0, lr
     708:	e8bd8010 	ldmia	sp!, {r4, pc}

0000070c <jmemcmp>:

int jmemcmp(const void *s1, const void *s2, size_t n)
{
     70c:	e92d4070 	stmdb	sp!, {r4, r5, r6, lr}
     710:	e1a04001 	mov	r4, r1
     714:	e1a0c002 	mov	ip, r2
	size_t i = 0;
	if(s1 == NULL) return -1;
     718:	e2505000 	subs	r5, r0, #0	; 0x0
     71c:	1a000001 	bne	728 <jmemcmp+0x1c>
     720:	e2400001 	sub	r0, r0, #1	; 0x1
     724:	e8bd8070 	ldmia	sp!, {r4, r5, r6, pc}
	if(s2 == NULL) return 1;
     728:	e3510000 	cmp	r1, #0	; 0x0
     72c:	1a000001 	bne	738 <jmemcmp+0x2c>
     730:	e3a00001 	mov	r0, #1	; 0x1
     734:	e8bd8070 	ldmia	sp!, {r4, r5, r6, pc}
	if(s1 == s2) return 0;
     738:	e1550001 	cmp	r5, r1
     73c:	1a000001 	bne	748 <jmemcmp+0x3c>
     740:	e3a00000 	mov	r0, #0	; 0x0
     744:	e8bd8070 	ldmia	sp!, {r4, r5, r6, pc}

	for(i = 0; i < n; i++)
     748:	e3520000 	cmp	r2, #0	; 0x0
     74c:	01a03002 	moveq	r3, r2
     750:	0a000010 	beq	798 <jmemcmp+0x8c>
	{
		if(((char*)s1)[i] != ((char*)s2)[i])
     754:	e1a01005 	mov	r1, r5
     758:	e5d52000 	ldrb	r2, [r5]
     75c:	e1a0e004 	mov	lr, r4
     760:	e5d40000 	ldrb	r0, [r4]
     764:	e1500002 	cmp	r0, r2
		{
			return ((char*)s1)[i] - ((char*)s2)[i];
     768:	03a03000 	moveq	r3, #0	; 0x0
     76c:	0a000006 	beq	78c <jmemcmp+0x80>
     770:	ea000003 	b	784 <jmemcmp+0x78>
     774:	e7d32001 	ldrb	r2, [r3, r1]
     778:	e7d3000e 	ldrb	r0, [r3, lr]
     77c:	e1520000 	cmp	r2, r0
     780:	0a000001 	beq	78c <jmemcmp+0x80>
     784:	e0600002 	rsb	r0, r0, r2
     788:	e8bd8070 	ldmia	sp!, {r4, r5, r6, pc}
     78c:	e2833001 	add	r3, r3, #1	; 0x1
     790:	e15c0003 	cmp	ip, r3
     794:	1afffff6 	bne	774 <jmemcmp+0x68>
		}
	}

	return ((char*)s1)[i] - ((char*)s2)[i];
     798:	e7d52003 	ldrb	r2, [r5, r3]
     79c:	e7d33004 	ldrb	r3, [r3, r4]
     7a0:	e0630002 	rsb	r0, r3, r2
}
     7a4:	e8bd8070 	ldmia	sp!, {r4, r5, r6, pc}

000007a8 <jstrcpy>:

char *jstrcpy(char *dest, const char *src)
{
	char* d = dest;
	const char* s = src;
	
	if(dest == NULL || src == NULL)
     7a8:	e1a0c000 	mov	ip, r0
     7ac:	e1a02001 	mov	r2, r1
     7b0:	e3510000 	cmp	r1, #0	; 0x0
     7b4:	13500000 	cmpne	r0, #0	; 0x0
     7b8:	0a00000b 	beq	7ec <jstrcpy+0x44>
	{
		return dest;
	}

	for(; *s; s++, d++)
     7bc:	e5d13000 	ldrb	r3, [r1]
     7c0:	e3530000 	cmp	r3, #0	; 0x0
     7c4:	01a02000 	moveq	r2, r0
     7c8:	0a000005 	beq	7e4 <jstrcpy+0x3c>
     7cc:	e1a01002 	mov	r1, r2
     7d0:	e1a02000 	mov	r2, r0
	{
		*d = *s;
     7d4:	e4c23001 	strb	r3, [r2], #1
     7d8:	e5f13001 	ldrb	r3, [r1, #1]!
     7dc:	e3530000 	cmp	r3, #0	; 0x0
     7e0:	1afffffb 	bne	7d4 <jstrcpy+0x2c>
	}
	*d = '\0';
     7e4:	e3a03000 	mov	r3, #0	; 0x0
     7e8:	e5c23000 	strb	r3, [r2]

	return dest;
}
     7ec:	e1a0000c 	mov	r0, ip
     7f0:	e12fff1e 	bx	lr

000007f4 <jstrncpy>:

char* jstrncpy(char* dest, const char* src, size_t n)
{
     7f4:	e92d4010 	stmdb	sp!, {r4, lr}
	char* d = dest;
	const char* s = src;
	size_t i = 0;

	if(dest == NULL || src == NULL || n == 0)
     7f8:	e1a0c000 	mov	ip, r0
     7fc:	e1a0e001 	mov	lr, r1
     800:	e3510000 	cmp	r1, #0	; 0x0
     804:	13500000 	cmpne	r0, #0	; 0x0
     808:	0a00000f 	beq	84c <jstrncpy+0x58>
     80c:	e3520000 	cmp	r2, #0	; 0x0
     810:	0a00000d 	beq	84c <jstrncpy+0x58>
	{
		return dest;
	}

	for(; *s && i < n; s++, d++, i++)
     814:	e5d13000 	ldrb	r3, [r1]
     818:	e3530000 	cmp	r3, #0	; 0x0
     81c:	01a02000 	moveq	r2, r0
     820:	0a000007 	beq	844 <jstrncpy+0x50>
     824:	e3a01000 	mov	r1, #0	; 0x0
	{
		*d = *s;
     828:	e7c1300c 	strb	r3, [r1, ip]
     82c:	e2811001 	add	r1, r1, #1	; 0x1
     830:	e7d1300e 	ldrb	r3, [r1, lr]
     834:	e3530000 	cmp	r3, #0	; 0x0
     838:	11520001 	cmpne	r2, r1
     83c:	8afffff9 	bhi	828 <jstrncpy+0x34>
     840:	e08c2001 	add	r2, ip, r1
	}
	
	*d = '\0';
     844:	e3a03000 	mov	r3, #0	; 0x0
     848:	e5c23000 	strb	r3, [r2]
	for(; i < n; i++)
	{
		*d = '\0';
	}

	return dest;
}
     84c:	e1a0000c 	mov	r0, ip
     850:	e8bd8010 	ldmia	sp!, {r4, pc}

00000854 <jstrcmp>:

int jstrcmp(const char *s1, const char *s2)
{
	if(s1 == NULL || s2 == NULL)
     854:	e1a0c000 	mov	ip, r0
     858:	e1a03001 	mov	r3, r1
     85c:	e3510000 	cmp	r1, #0	; 0x0
     860:	13500000 	cmpne	r0, #0	; 0x0
	{
		return s1 - s2;
     864:	00610000 	rsbeq	r0, r1, r0
     868:	012fff1e 	bxeq	lr
	}

	for(; *s1 != '\0' && *s2 != '\0'; s1++, s2++)
     86c:	e5dc2000 	ldrb	r2, [ip]
     870:	e3520000 	cmp	r2, #0	; 0x0
     874:	0a000012 	beq	8c4 <jstrcmp+0x70>
     878:	e5d11000 	ldrb	r1, [r1]
     87c:	e3510000 	cmp	r1, #0	; 0x0
     880:	0a00000f 	beq	8c4 <jstrcmp+0x70>
	{
		if(*s1 != *s2)
     884:	e1520001 	cmp	r2, r1
		{
			return *s1 - *s2;
     888:	01a0000c 	moveq	r0, ip
     88c:	0a000005 	beq	8a8 <jstrcmp+0x54>
     890:	ea000002 	b	8a0 <jstrcmp+0x4c>
     894:	e2800001 	add	r0, r0, #1	; 0x1
     898:	e1520001 	cmp	r2, r1
     89c:	0a000001 	beq	8a8 <jstrcmp+0x54>
     8a0:	e0610002 	rsb	r0, r1, r2
     8a4:	e12fff1e 	bx	lr
     8a8:	e2833001 	add	r3, r3, #1	; 0x1
     8ac:	e5d02001 	ldrb	r2, [r0, #1]
     8b0:	e3520000 	cmp	r2, #0	; 0x0
     8b4:	0a000002 	beq	8c4 <jstrcmp+0x70>
     8b8:	e5d31000 	ldrb	r1, [r3]
     8bc:	e3510000 	cmp	r1, #0	; 0x0
     8c0:	1afffff3 	bne	894 <jstrcmp+0x40>
		}
	}

	return *s1 - *s2;
     8c4:	e5d33000 	ldrb	r3, [r3]
     8c8:	e0630002 	rsb	r0, r3, r2
}
     8cc:	e12fff1e 	bx	lr

000008d0 <jstrncmp>:

int jstrncmp(const char *s1, const char *s2, size_t n)
{
     8d0:	e92d4010 	stmdb	sp!, {r4, lr}
	if(s1 == NULL || s2 == NULL)
     8d4:	e1a03000 	mov	r3, r0
     8d8:	e1a0e001 	mov	lr, r1
     8dc:	e3510000 	cmp	r1, #0	; 0x0
     8e0:	13500000 	cmpne	r0, #0	; 0x0
     8e4:	0a00000a 	beq	914 <jstrncmp+0x44>
	{
		return s1 - s2;
	}

	for(; *s1 != '\0' && *s2 != '\0' && n > 0; s1++, s2++, n--)
     8e8:	e5d00000 	ldrb	r0, [r0]
     8ec:	e3500000 	cmp	r0, #0	; 0x0
     8f0:	0a00001b 	beq	964 <jstrncmp+0x94>
     8f4:	e5d11000 	ldrb	r1, [r1]
     8f8:	e3510000 	cmp	r1, #0	; 0x0
     8fc:	13520000 	cmpne	r2, #0	; 0x0
     900:	0a000017 	beq	964 <jstrncmp+0x94>
	{
		if(*s1 != *s2)
     904:	e1500001 	cmp	r0, r1
		{
			return *s1 - *s2;
     908:	01a0c003 	moveq	ip, r3
     90c:	0a000007 	beq	930 <jstrncmp+0x60>
     910:	ea000004 	b	928 <jstrncmp+0x58>
     914:	e0610000 	rsb	r0, r1, r0
     918:	e8bd8010 	ldmia	sp!, {r4, pc}
     91c:	e28cc001 	add	ip, ip, #1	; 0x1
     920:	e1500001 	cmp	r0, r1
     924:	0a000001 	beq	930 <jstrncmp+0x60>
     928:	e0610000 	rsb	r0, r1, r0
     92c:	e8bd8010 	ldmia	sp!, {r4, pc}
     930:	e28ee001 	add	lr, lr, #1	; 0x1
     934:	e5dc0001 	ldrb	r0, [ip, #1]
     938:	e3500000 	cmp	r0, #0	; 0x0
     93c:	0a000008 	beq	964 <jstrncmp+0x94>
     940:	e5de1000 	ldrb	r1, [lr]
     944:	e2522001 	subs	r2, r2, #1	; 0x1
     948:	03a03000 	moveq	r3, #0	; 0x0
     94c:	13a03001 	movne	r3, #1	; 0x1
     950:	e3510000 	cmp	r1, #0	; 0x0
     954:	03a03000 	moveq	r3, #0	; 0x0
     958:	12033001 	andne	r3, r3, #1	; 0x1
     95c:	e3530000 	cmp	r3, #0	; 0x0
     960:	1affffed 	bne	91c <jstrncmp+0x4c>
		}
	}

	return *s1 - *s2;
     964:	e5de3000 	ldrb	r3, [lr]
     968:	e0630000 	rsb	r0, r3, r0
}
     96c:	e8bd8010 	ldmia	sp!, {r4, pc}

00000970 <jstrlen>:

size_t jstrlen(const char *s)
{
	size_t n = 0;

	if(s == NULL || *s == '\0')
     970:	e2502000 	subs	r2, r0, #0	; 0x0
     974:	0a000008 	beq	99c <jstrlen+0x2c>
     978:	e5d23000 	ldrb	r3, [r2]
     97c:	e3530000 	cmp	r3, #0	; 0x0
     980:	0a000005 	beq	99c <jstrlen+0x2c>
     984:	e3a00000 	mov	r0, #0	; 0x0
	{
		return 0;
	}

	while(s[n]) n++;
     988:	e2800001 	add	r0, r0, #1	; 0x1
     98c:	e7d03002 	ldrb	r3, [r0, r2]
     990:	e3530000 	cmp	r3, #0	; 0x0
     994:	012fff1e 	bxeq	lr
     998:	eafffffa 	b	988 <jstrlen+0x18>
     99c:	e3a00000 	mov	r0, #0	; 0x0

	return n;
}
     9a0:	e12fff1e 	bx	lr

000009a4 <print_test>:
	return;
}

void print_test(void)
{
     9a4:	e1a0c00d 	mov	ip, sp
     9a8:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     9ac:	e24cb004 	sub	fp, ip, #4	; 0x4
     9b0:	e24dde41 	sub	sp, sp, #1040	; 0x410
     9b4:	e24dd008 	sub	sp, sp, #8	; 0x8
	char str[1024];
	char str1[10];
	jsnprintf(str, sizeof(str), "%s%d0x%x", "aaa", 123, 0xabc);
     9b8:	e24b4e41 	sub	r4, fp, #1040	; 0x410
     9bc:	e2444004 	sub	r4, r4, #4	; 0x4
     9c0:	e3a0307b 	mov	r3, #123	; 0x7b
     9c4:	e58d3000 	str	r3, [sp]
     9c8:	e3a03eab 	mov	r3, #2736	; 0xab0
     9cc:	e283300c 	add	r3, r3, #12	; 0xc
     9d0:	e58d3004 	str	r3, [sp, #4]
     9d4:	e1a00004 	mov	r0, r4
     9d8:	e3a01b01 	mov	r1, #1024	; 0x400
     9dc:	e59f2150 	ldr	r2, [pc, #336]	; b34 <.text+0xb34>
     9e0:	e59f3150 	ldr	r3, [pc, #336]	; b38 <.text+0xb38>
     9e4:	eb0003ef 	bl	19a8 <jsnprintf>
	assert(jstrcmp(str, "aaa1230xabc") == 0);
     9e8:	e1a00004 	mov	r0, r4
     9ec:	e59f1148 	ldr	r1, [pc, #328]	; b3c <.text+0xb3c>
     9f0:	ebffff97 	bl	854 <jstrcmp>
     9f4:	e3500000 	cmp	r0, #0	; 0x0
     9f8:	0a000003 	beq	a0c <print_test+0x68>
     9fc:	e59f013c 	ldr	r0, [pc, #316]	; b40 <.text+0xb40>
     a00:	e3a01069 	mov	r1, #105	; 0x69
     a04:	e59f2138 	ldr	r2, [pc, #312]	; b44 <.text+0xb44>
     a08:	eb00031b 	bl	167c <jtrace>
	
	jsnprintf(str, sizeof(str), "%s%d0x%X", "aaa", 123, 0xabc);
     a0c:	e24b4e41 	sub	r4, fp, #1040	; 0x410
     a10:	e2444004 	sub	r4, r4, #4	; 0x4
     a14:	e3a0307b 	mov	r3, #123	; 0x7b
     a18:	e58d3000 	str	r3, [sp]
     a1c:	e3a03eab 	mov	r3, #2736	; 0xab0
     a20:	e283300c 	add	r3, r3, #12	; 0xc
     a24:	e58d3004 	str	r3, [sp, #4]
     a28:	e1a00004 	mov	r0, r4
     a2c:	e3a01b01 	mov	r1, #1024	; 0x400
     a30:	e59f2110 	ldr	r2, [pc, #272]	; b48 <.text+0xb48>
     a34:	e59f30fc 	ldr	r3, [pc, #252]	; b38 <.text+0xb38>
     a38:	eb0003da 	bl	19a8 <jsnprintf>
	assert(jstrcmp(str, "aaa1230xABC") == 0);
     a3c:	e1a00004 	mov	r0, r4
     a40:	e59f1104 	ldr	r1, [pc, #260]	; b4c <.text+0xb4c>
     a44:	ebffff82 	bl	854 <jstrcmp>
     a48:	e3500000 	cmp	r0, #0	; 0x0
     a4c:	0a000003 	beq	a60 <print_test+0xbc>
     a50:	e59f00e8 	ldr	r0, [pc, #232]	; b40 <.text+0xb40>
     a54:	e3a0106c 	mov	r1, #108	; 0x6c
     a58:	e59f20f0 	ldr	r2, [pc, #240]	; b50 <.text+0xb50>
     a5c:	eb000306 	bl	167c <jtrace>
	
	jsnprintf(str, sizeof(str), "%s%d%p", "aaa", 123, 0xabc);
     a60:	e24b4e41 	sub	r4, fp, #1040	; 0x410
     a64:	e2444004 	sub	r4, r4, #4	; 0x4
     a68:	e3a0307b 	mov	r3, #123	; 0x7b
     a6c:	e58d3000 	str	r3, [sp]
     a70:	e3a03eab 	mov	r3, #2736	; 0xab0
     a74:	e283300c 	add	r3, r3, #12	; 0xc
     a78:	e58d3004 	str	r3, [sp, #4]
     a7c:	e1a00004 	mov	r0, r4
     a80:	e3a01b01 	mov	r1, #1024	; 0x400
     a84:	e59f20c8 	ldr	r2, [pc, #200]	; b54 <.text+0xb54>
     a88:	e59f30a8 	ldr	r3, [pc, #168]	; b38 <.text+0xb38>
     a8c:	eb0003c5 	bl	19a8 <jsnprintf>
	assert(jstrcmp(str, "aaa1230xabc") == 0);
     a90:	e1a00004 	mov	r0, r4
     a94:	e59f10a0 	ldr	r1, [pc, #160]	; b3c <.text+0xb3c>
     a98:	ebffff6d 	bl	854 <jstrcmp>
     a9c:	e3500000 	cmp	r0, #0	; 0x0
     aa0:	0a000003 	beq	ab4 <print_test+0x110>
     aa4:	e59f0094 	ldr	r0, [pc, #148]	; b40 <.text+0xb40>
     aa8:	e3a0106f 	mov	r1, #111	; 0x6f
     aac:	e59f2090 	ldr	r2, [pc, #144]	; b44 <.text+0xb44>
     ab0:	eb0002f1 	bl	167c <jtrace>
	
	assert(jsnprintf(str1, sizeof(str1), "%s%d%p", "aaa", 123, 0xabc) == 10);
     ab4:	e3a0307b 	mov	r3, #123	; 0x7b
     ab8:	e58d3000 	str	r3, [sp]
     abc:	e3a03eab 	mov	r3, #2736	; 0xab0
     ac0:	e283300c 	add	r3, r3, #12	; 0xc
     ac4:	e58d3004 	str	r3, [sp, #4]
     ac8:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     acc:	e2400004 	sub	r0, r0, #4	; 0x4
     ad0:	e240000a 	sub	r0, r0, #10	; 0xa
     ad4:	e3a0100a 	mov	r1, #10	; 0xa
     ad8:	e59f2074 	ldr	r2, [pc, #116]	; b54 <.text+0xb54>
     adc:	e59f3054 	ldr	r3, [pc, #84]	; b38 <.text+0xb38>
     ae0:	eb0003b0 	bl	19a8 <jsnprintf>
     ae4:	e350000a 	cmp	r0, #10	; 0xa
     ae8:	0a000003 	beq	afc <print_test+0x158>
     aec:	e59f004c 	ldr	r0, [pc, #76]	; b40 <.text+0xb40>
     af0:	e3a01071 	mov	r1, #113	; 0x71
     af4:	e59f205c 	ldr	r2, [pc, #92]	; b58 <.text+0xb58>
     af8:	eb0002df 	bl	167c <jtrace>
	assert(jstrncmp(str1, "aaa1230xabc", sizeof(str1)-1) == 0);
     afc:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     b00:	e2400004 	sub	r0, r0, #4	; 0x4
     b04:	e240000a 	sub	r0, r0, #10	; 0xa
     b08:	e59f102c 	ldr	r1, [pc, #44]	; b3c <.text+0xb3c>
     b0c:	e3a02009 	mov	r2, #9	; 0x9
     b10:	ebffff6e 	bl	8d0 <jstrncmp>
     b14:	e3500000 	cmp	r0, #0	; 0x0
     b18:	0a000003 	beq	b2c <print_test+0x188>
     b1c:	e59f001c 	ldr	r0, [pc, #28]	; b40 <.text+0xb40>
     b20:	e3a01072 	mov	r1, #114	; 0x72
     b24:	e59f2030 	ldr	r2, [pc, #48]	; b5c <.text+0xb5c>
     b28:	eb0002d3 	bl	167c <jtrace>

	return;
}
     b2c:	e24bd014 	sub	sp, fp, #20	; 0x14
     b30:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
     b34:	00001d58 	andeq	r1, r0, r8, asr sp
     b38:	00001d68 	andeq	r1, r0, r8, ror #26
     b3c:	00001d70 	andeq	r1, r0, r0, ror sp
     b40:	00002600 	andeq	r2, r0, r0, lsl #12
     b44:	00001d80 	andeq	r1, r0, r0, lsl #27
     b48:	00001da8 	andeq	r1, r0, r8, lsr #27
     b4c:	00001db8 	streqh	r1, [r0], -r8
     b50:	00001dc8 	andeq	r1, r0, r8, asr #27
     b54:	00001df0 	streqd	r1, [r0], -r0
     b58:	00001df8 	streqd	r1, [r0], -r8
     b5c:	00001e40 	andeq	r1, r0, r0, asr #28

00000b60 <mem_test>:
     b60:	e1a0c00d 	mov	ip, sp
     b64:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     b68:	e24cb004 	sub	fp, ip, #4	; 0x4
     b6c:	e24ddb01 	sub	sp, sp, #1024	; 0x400
     b70:	e24b4e41 	sub	r4, fp, #1040	; 0x410
     b74:	e2444004 	sub	r4, r4, #4	; 0x4
     b78:	e1a00004 	mov	r0, r4
     b7c:	e3a01000 	mov	r1, #0	; 0x0
     b80:	e3a02b01 	mov	r2, #1024	; 0x400
     b84:	ebfffec6 	bl	6a4 <jmemset>
     b88:	e1a00004 	mov	r0, r4
     b8c:	e3a01061 	mov	r1, #97	; 0x61
     b90:	e3a02005 	mov	r2, #5	; 0x5
     b94:	ebfffec2 	bl	6a4 <jmemset>
     b98:	e59f118c 	ldr	r1, [pc, #396]	; d2c <.text+0xd2c>
     b9c:	e3a02005 	mov	r2, #5	; 0x5
     ba0:	ebfffed9 	bl	70c <jmemcmp>
     ba4:	e3500000 	cmp	r0, #0	; 0x0
     ba8:	0a000003 	beq	bbc <mem_test+0x5c>
     bac:	e59f017c 	ldr	r0, [pc, #380]	; d30 <.text+0xd30>
     bb0:	e3a01059 	mov	r1, #89	; 0x59
     bb4:	e59f2178 	ldr	r2, [pc, #376]	; d34 <.text+0xd34>
     bb8:	eb0002af 	bl	167c <jtrace>
     bbc:	e59f4174 	ldr	r4, [pc, #372]	; d38 <.text+0xd38>
     bc0:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     bc4:	e2400004 	sub	r0, r0, #4	; 0x4
     bc8:	e1a01004 	mov	r1, r4
     bcc:	e3a02005 	mov	r2, #5	; 0x5
     bd0:	ebfffebd 	bl	6cc <jmemcpy>
     bd4:	e1a01004 	mov	r1, r4
     bd8:	e3a02005 	mov	r2, #5	; 0x5
     bdc:	ebfffeca 	bl	70c <jmemcmp>
     be0:	e3500000 	cmp	r0, #0	; 0x0
     be4:	0a000003 	beq	bf8 <mem_test+0x98>
     be8:	e59f0140 	ldr	r0, [pc, #320]	; d30 <.text+0xd30>
     bec:	e3a0105a 	mov	r1, #90	; 0x5a
     bf0:	e59f2144 	ldr	r2, [pc, #324]	; d3c <.text+0xd3c>
     bf4:	eb0002a0 	bl	167c <jtrace>
     bf8:	e59f4138 	ldr	r4, [pc, #312]	; d38 <.text+0xd38>
     bfc:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     c00:	e2400004 	sub	r0, r0, #4	; 0x4
     c04:	e1a01004 	mov	r1, r4
     c08:	e3a02001 	mov	r2, #1	; 0x1
     c0c:	ebfffeae 	bl	6cc <jmemcpy>
     c10:	e1a01004 	mov	r1, r4
     c14:	e3a02005 	mov	r2, #5	; 0x5
     c18:	ebfffebb 	bl	70c <jmemcmp>
     c1c:	e3500000 	cmp	r0, #0	; 0x0
     c20:	0a000003 	beq	c34 <mem_test+0xd4>
     c24:	e59f0104 	ldr	r0, [pc, #260]	; d30 <.text+0xd30>
     c28:	e3a0105b 	mov	r1, #91	; 0x5b
     c2c:	e59f210c 	ldr	r2, [pc, #268]	; d40 <.text+0xd40>
     c30:	eb000291 	bl	167c <jtrace>
     c34:	e59f40fc 	ldr	r4, [pc, #252]	; d38 <.text+0xd38>
     c38:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     c3c:	e2400004 	sub	r0, r0, #4	; 0x4
     c40:	e1a01004 	mov	r1, r4
     c44:	e3a02004 	mov	r2, #4	; 0x4
     c48:	ebfffe9f 	bl	6cc <jmemcpy>
     c4c:	e1a01004 	mov	r1, r4
     c50:	e3a02005 	mov	r2, #5	; 0x5
     c54:	ebfffeac 	bl	70c <jmemcmp>
     c58:	e3500000 	cmp	r0, #0	; 0x0
     c5c:	0a000003 	beq	c70 <mem_test+0x110>
     c60:	e59f00c8 	ldr	r0, [pc, #200]	; d30 <.text+0xd30>
     c64:	e3a0105c 	mov	r1, #92	; 0x5c
     c68:	e59f20d4 	ldr	r2, [pc, #212]	; d44 <.text+0xd44>
     c6c:	eb000282 	bl	167c <jtrace>
     c70:	e59f40c0 	ldr	r4, [pc, #192]	; d38 <.text+0xd38>
     c74:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     c78:	e2400004 	sub	r0, r0, #4	; 0x4
     c7c:	e1a01004 	mov	r1, r4
     c80:	e3a02006 	mov	r2, #6	; 0x6
     c84:	ebfffe90 	bl	6cc <jmemcpy>
     c88:	e1a01004 	mov	r1, r4
     c8c:	e3a02005 	mov	r2, #5	; 0x5
     c90:	ebfffe9d 	bl	70c <jmemcmp>
     c94:	e3500000 	cmp	r0, #0	; 0x0
     c98:	0a000003 	beq	cac <mem_test+0x14c>
     c9c:	e59f008c 	ldr	r0, [pc, #140]	; d30 <.text+0xd30>
     ca0:	e3a0105d 	mov	r1, #93	; 0x5d
     ca4:	e59f209c 	ldr	r2, [pc, #156]	; d48 <.text+0xd48>
     ca8:	eb000273 	bl	167c <jtrace>
     cac:	e59f4084 	ldr	r4, [pc, #132]	; d38 <.text+0xd38>
     cb0:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     cb4:	e2400004 	sub	r0, r0, #4	; 0x4
     cb8:	e1a01004 	mov	r1, r4
     cbc:	e3a02005 	mov	r2, #5	; 0x5
     cc0:	ebfffe81 	bl	6cc <jmemcpy>
     cc4:	e1a01004 	mov	r1, r4
     cc8:	e3a02001 	mov	r2, #1	; 0x1
     ccc:	ebfffe8e 	bl	70c <jmemcmp>
     cd0:	e3500000 	cmp	r0, #0	; 0x0
     cd4:	0a000003 	beq	ce8 <mem_test+0x188>
     cd8:	e59f0050 	ldr	r0, [pc, #80]	; d30 <.text+0xd30>
     cdc:	e3a0105e 	mov	r1, #94	; 0x5e
     ce0:	e59f2064 	ldr	r2, [pc, #100]	; d4c <.text+0xd4c>
     ce4:	eb000264 	bl	167c <jtrace>
     ce8:	e59f4048 	ldr	r4, [pc, #72]	; d38 <.text+0xd38>
     cec:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     cf0:	e2400004 	sub	r0, r0, #4	; 0x4
     cf4:	e1a01004 	mov	r1, r4
     cf8:	e3a02005 	mov	r2, #5	; 0x5
     cfc:	ebfffe72 	bl	6cc <jmemcpy>
     d00:	e1a01004 	mov	r1, r4
     d04:	e3a02004 	mov	r2, #4	; 0x4
     d08:	ebfffe7f 	bl	70c <jmemcmp>
     d0c:	e3500000 	cmp	r0, #0	; 0x0
     d10:	0a000003 	beq	d24 <mem_test+0x1c4>
     d14:	e59f0014 	ldr	r0, [pc, #20]	; d30 <.text+0xd30>
     d18:	e3a0105f 	mov	r1, #95	; 0x5f
     d1c:	e59f202c 	ldr	r2, [pc, #44]	; d50 <.text+0xd50>
     d20:	eb000255 	bl	167c <jtrace>
     d24:	e24bd014 	sub	sp, fp, #20	; 0x14
     d28:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
     d2c:	00001e78 	andeq	r1, r0, r8, ror lr
     d30:	00002610 	andeq	r2, r0, r0, lsl r6
     d34:	00001e80 	andeq	r1, r0, r0, lsl #29
     d38:	00001eb0 	streqh	r1, [r0], -r0
     d3c:	00001eb8 	streqh	r1, [r0], -r8
     d40:	00001ef0 	streqd	r1, [r0], -r0
     d44:	00001f28 	andeq	r1, r0, r8, lsr #30
     d48:	00001f60 	andeq	r1, r0, r0, ror #30
     d4c:	00001f98 	muleq	r0, r8, pc
     d50:	00001fd0 	ldreqd	r1, [r0], -r0

00000d54 <str_test>:
     d54:	e1a0c00d 	mov	ip, sp
     d58:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
     d5c:	e24cb004 	sub	fp, ip, #4	; 0x4
     d60:	e24ddb01 	sub	sp, sp, #1024	; 0x400
     d64:	e59f41d4 	ldr	r4, [pc, #468]	; f40 <.text+0xf40>
     d68:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     d6c:	e2400004 	sub	r0, r0, #4	; 0x4
     d70:	e1a01004 	mov	r1, r4
     d74:	ebfffe8b 	bl	7a8 <jstrcpy>
     d78:	e1a01004 	mov	r1, r4
     d7c:	ebfffeb4 	bl	854 <jstrcmp>
     d80:	e3500000 	cmp	r0, #0	; 0x0
     d84:	0a000003 	beq	d98 <str_test+0x44>
     d88:	e59f01b4 	ldr	r0, [pc, #436]	; f44 <.text+0xf44>
     d8c:	e3a01045 	mov	r1, #69	; 0x45
     d90:	e59f21b0 	ldr	r2, [pc, #432]	; f48 <.text+0xf48>
     d94:	eb000238 	bl	167c <jtrace>
     d98:	e59f41ac 	ldr	r4, [pc, #428]	; f4c <.text+0xf4c>
     d9c:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     da0:	e2400004 	sub	r0, r0, #4	; 0x4
     da4:	e1a01004 	mov	r1, r4
     da8:	ebfffe7e 	bl	7a8 <jstrcpy>
     dac:	e1a01004 	mov	r1, r4
     db0:	ebfffea7 	bl	854 <jstrcmp>
     db4:	e3500000 	cmp	r0, #0	; 0x0
     db8:	0a000003 	beq	dcc <str_test+0x78>
     dbc:	e59f0180 	ldr	r0, [pc, #384]	; f44 <.text+0xf44>
     dc0:	e3a01046 	mov	r1, #70	; 0x46
     dc4:	e59f2184 	ldr	r2, [pc, #388]	; f50 <.text+0xf50>
     dc8:	eb00022b 	bl	167c <jtrace>
     dcc:	e59f4180 	ldr	r4, [pc, #384]	; f54 <.text+0xf54>
     dd0:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     dd4:	e2400004 	sub	r0, r0, #4	; 0x4
     dd8:	e1a01004 	mov	r1, r4
     ddc:	ebfffe71 	bl	7a8 <jstrcpy>
     de0:	e1a01004 	mov	r1, r4
     de4:	ebfffe9a 	bl	854 <jstrcmp>
     de8:	e3500000 	cmp	r0, #0	; 0x0
     dec:	0a000003 	beq	e00 <str_test+0xac>
     df0:	e59f014c 	ldr	r0, [pc, #332]	; f44 <.text+0xf44>
     df4:	e3a01047 	mov	r1, #71	; 0x47
     df8:	e59f2158 	ldr	r2, [pc, #344]	; f58 <.text+0xf58>
     dfc:	eb00021e 	bl	167c <jtrace>
     e00:	e24b4e41 	sub	r4, fp, #1040	; 0x410
     e04:	e2444004 	sub	r4, r4, #4	; 0x4
     e08:	e1a00004 	mov	r0, r4
     e0c:	e3a01000 	mov	r1, #0	; 0x0
     e10:	e3a02b01 	mov	r2, #1024	; 0x400
     e14:	ebfffe22 	bl	6a4 <jmemset>
     e18:	e1a00004 	mov	r0, r4
     e1c:	e59f1138 	ldr	r1, [pc, #312]	; f5c <.text+0xf5c>
     e20:	e3a02001 	mov	r2, #1	; 0x1
     e24:	ebfffe72 	bl	7f4 <jstrncpy>
     e28:	e59f111c 	ldr	r1, [pc, #284]	; f4c <.text+0xf4c>
     e2c:	ebfffe88 	bl	854 <jstrcmp>
     e30:	e3500000 	cmp	r0, #0	; 0x0
     e34:	0a000003 	beq	e48 <str_test+0xf4>
     e38:	e59f0104 	ldr	r0, [pc, #260]	; f44 <.text+0xf44>
     e3c:	e3a0104a 	mov	r1, #74	; 0x4a
     e40:	e59f2118 	ldr	r2, [pc, #280]	; f60 <.text+0xf60>
     e44:	eb00020c 	bl	167c <jtrace>
     e48:	e24b4e41 	sub	r4, fp, #1040	; 0x410
     e4c:	e2444004 	sub	r4, r4, #4	; 0x4
     e50:	e1a00004 	mov	r0, r4
     e54:	e3a01000 	mov	r1, #0	; 0x0
     e58:	e3a02b01 	mov	r2, #1024	; 0x400
     e5c:	ebfffe10 	bl	6a4 <jmemset>
     e60:	e1a00004 	mov	r0, r4
     e64:	e59f10f0 	ldr	r1, [pc, #240]	; f5c <.text+0xf5c>
     e68:	e3a02003 	mov	r2, #3	; 0x3
     e6c:	ebfffe60 	bl	7f4 <jstrncpy>
     e70:	e59f10dc 	ldr	r1, [pc, #220]	; f54 <.text+0xf54>
     e74:	ebfffe76 	bl	854 <jstrcmp>
     e78:	e3500000 	cmp	r0, #0	; 0x0
     e7c:	0a000003 	beq	e90 <str_test+0x13c>
     e80:	e59f00bc 	ldr	r0, [pc, #188]	; f44 <.text+0xf44>
     e84:	e3a0104d 	mov	r1, #77	; 0x4d
     e88:	e59f20d4 	ldr	r2, [pc, #212]	; f64 <.text+0xf64>
     e8c:	eb0001fa 	bl	167c <jtrace>
     e90:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     e94:	e2400004 	sub	r0, r0, #4	; 0x4
     e98:	e59f10bc 	ldr	r1, [pc, #188]	; f5c <.text+0xf5c>
     e9c:	e3a02003 	mov	r2, #3	; 0x3
     ea0:	ebfffe53 	bl	7f4 <jstrncpy>
     ea4:	e59f10a8 	ldr	r1, [pc, #168]	; f54 <.text+0xf54>
     ea8:	e3a02001 	mov	r2, #1	; 0x1
     eac:	ebfffe87 	bl	8d0 <jstrncmp>
     eb0:	e3500000 	cmp	r0, #0	; 0x0
     eb4:	0a000003 	beq	ec8 <str_test+0x174>
     eb8:	e59f0084 	ldr	r0, [pc, #132]	; f44 <.text+0xf44>
     ebc:	e3a0104e 	mov	r1, #78	; 0x4e
     ec0:	e59f20a0 	ldr	r2, [pc, #160]	; f68 <.text+0xf68>
     ec4:	eb0001ec 	bl	167c <jtrace>
     ec8:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     ecc:	e2400004 	sub	r0, r0, #4	; 0x4
     ed0:	e59f1084 	ldr	r1, [pc, #132]	; f5c <.text+0xf5c>
     ed4:	e3a02003 	mov	r2, #3	; 0x3
     ed8:	ebfffe45 	bl	7f4 <jstrncpy>
     edc:	e59f1070 	ldr	r1, [pc, #112]	; f54 <.text+0xf54>
     ee0:	e3a02002 	mov	r2, #2	; 0x2
     ee4:	ebfffe79 	bl	8d0 <jstrncmp>
     ee8:	e3500000 	cmp	r0, #0	; 0x0
     eec:	0a000003 	beq	f00 <str_test+0x1ac>
     ef0:	e59f004c 	ldr	r0, [pc, #76]	; f44 <.text+0xf44>
     ef4:	e3a0104f 	mov	r1, #79	; 0x4f
     ef8:	e59f206c 	ldr	r2, [pc, #108]	; f6c <.text+0xf6c>
     efc:	eb0001de 	bl	167c <jtrace>
     f00:	e24b0e41 	sub	r0, fp, #1040	; 0x410
     f04:	e2400004 	sub	r0, r0, #4	; 0x4
     f08:	e59f104c 	ldr	r1, [pc, #76]	; f5c <.text+0xf5c>
     f0c:	e3a02003 	mov	r2, #3	; 0x3
     f10:	ebfffe37 	bl	7f4 <jstrncpy>
     f14:	e59f1038 	ldr	r1, [pc, #56]	; f54 <.text+0xf54>
     f18:	e3a02003 	mov	r2, #3	; 0x3
     f1c:	ebfffe6b 	bl	8d0 <jstrncmp>
     f20:	e3500000 	cmp	r0, #0	; 0x0
     f24:	0a000003 	beq	f38 <str_test+0x1e4>
     f28:	e59f0014 	ldr	r0, [pc, #20]	; f44 <.text+0xf44>
     f2c:	e3a01050 	mov	r1, #80	; 0x50
     f30:	e59f2038 	ldr	r2, [pc, #56]	; f70 <.text+0xf70>
     f34:	eb0001d0 	bl	167c <jtrace>
     f38:	e24bd014 	sub	sp, fp, #20	; 0x14
     f3c:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
     f40:	000025c0 	andeq	r2, r0, r0, asr #11
     f44:	00002620 	andeq	r2, r0, r0, lsr #12
     f48:	00001bb8 	streqh	r1, [r0], -r8
     f4c:	00001be0 	andeq	r1, r0, r0, ror #23
     f50:	00001be8 	andeq	r1, r0, r8, ror #23
     f54:	00001c10 	andeq	r1, r0, r0, lsl ip
     f58:	00001c18 	andeq	r1, r0, r8, lsl ip
     f5c:	00001c48 	andeq	r1, r0, r8, asr #24
     f60:	00001c50 	andeq	r1, r0, r0, asr ip
     f64:	00001c80 	andeq	r1, r0, r0, lsl #25
     f68:	00001cb0 	streqh	r1, [r0], -r0
     f6c:	00001ce8 	andeq	r1, r0, r8, ror #25
     f70:	00001d20 	andeq	r1, r0, r0, lsr #26

00000f74 <test_all>:

void test_all(void)
{
     f74:	e1a0c00d 	mov	ip, sp
     f78:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     f7c:	e24cb004 	sub	fp, ip, #4	; 0x4
//	print_test();
//	jitoa_test();
//	jatoi_test();
	str_test();
     f80:	ebffff73 	bl	d54 <str_test>
	mem_test();
     f84:	ebfffef5 	bl	b60 <mem_test>

	return;
}
     f88:	e89da800 	ldmia	sp, {fp, sp, pc}

00000f8c <main>:

int main(int argc, char* argv[])
{
     f8c:	e1a0c00d 	mov	ip, sp
     f90:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     f94:	e24cb004 	sub	fp, ip, #4	; 0x4
	test_all();
     f98:	ebfffff5 	bl	f74 <test_all>

	return 0;
}
     f9c:	e3a00000 	mov	r0, #0	; 0x0
     fa0:	e89da800 	ldmia	sp, {fp, sp, pc}

00000fa4 <jitoa_test>:
     fa4:	e1a0c00d 	mov	ip, sp
     fa8:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
     fac:	e24cb004 	sub	fp, ip, #4	; 0x4
     fb0:	e24dd028 	sub	sp, sp, #40	; 0x28
     fb4:	e3e00063 	mvn	r0, #99	; 0x63
     fb8:	e24b102c 	sub	r1, fp, #44	; 0x2c
     fbc:	e3a0200a 	mov	r2, #10	; 0xa
     fc0:	ebfffdac 	bl	678 <jitoa>
     fc4:	e59f12b8 	ldr	r1, [pc, #696]	; 1284 <.text+0x1284>
     fc8:	ebfffe21 	bl	854 <jstrcmp>
     fcc:	e3500000 	cmp	r0, #0	; 0x0
     fd0:	0a000003 	beq	fe4 <jitoa_test+0x40>
     fd4:	e59f02ac 	ldr	r0, [pc, #684]	; 1288 <.text+0x1288>
     fd8:	e3a0102c 	mov	r1, #44	; 0x2c
     fdc:	e59f22a8 	ldr	r2, [pc, #680]	; 128c <.text+0x128c>
     fe0:	eb0001a5 	bl	167c <jtrace>
     fe4:	e3a00e4d 	mov	r0, #1232	; 0x4d0
     fe8:	e2800002 	add	r0, r0, #2	; 0x2
     fec:	e24b102c 	sub	r1, fp, #44	; 0x2c
     ff0:	e3a0200a 	mov	r2, #10	; 0xa
     ff4:	ebfffd9f 	bl	678 <jitoa>
     ff8:	e59f1290 	ldr	r1, [pc, #656]	; 1290 <.text+0x1290>
     ffc:	ebfffe14 	bl	854 <jstrcmp>
    1000:	e3500000 	cmp	r0, #0	; 0x0
    1004:	0a000003 	beq	1018 <jitoa_test+0x74>
    1008:	e59f0278 	ldr	r0, [pc, #632]	; 1288 <.text+0x1288>
    100c:	e3a0102d 	mov	r1, #45	; 0x2d
    1010:	e59f227c 	ldr	r2, [pc, #636]	; 1294 <.text+0x1294>
    1014:	eb000198 	bl	167c <jtrace>
    1018:	e3a0000a 	mov	r0, #10	; 0xa
    101c:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1020:	e1a02000 	mov	r2, r0
    1024:	ebfffd93 	bl	678 <jitoa>
    1028:	e59f1268 	ldr	r1, [pc, #616]	; 1298 <.text+0x1298>
    102c:	ebfffe08 	bl	854 <jstrcmp>
    1030:	e3500000 	cmp	r0, #0	; 0x0
    1034:	0a000003 	beq	1048 <jitoa_test+0xa4>
    1038:	e59f0248 	ldr	r0, [pc, #584]	; 1288 <.text+0x1288>
    103c:	e3a0102e 	mov	r1, #46	; 0x2e
    1040:	e59f2254 	ldr	r2, [pc, #596]	; 129c <.text+0x129c>
    1044:	eb00018c 	bl	167c <jtrace>
    1048:	e3e00063 	mvn	r0, #99	; 0x63
    104c:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1050:	e3a02000 	mov	r2, #0	; 0x0
    1054:	ebfffd87 	bl	678 <jitoa>
    1058:	e59f1224 	ldr	r1, [pc, #548]	; 1284 <.text+0x1284>
    105c:	ebfffdfc 	bl	854 <jstrcmp>
    1060:	e3500000 	cmp	r0, #0	; 0x0
    1064:	0a000003 	beq	1078 <jitoa_test+0xd4>
    1068:	e59f0218 	ldr	r0, [pc, #536]	; 1288 <.text+0x1288>
    106c:	e3a01030 	mov	r1, #48	; 0x30
    1070:	e59f2228 	ldr	r2, [pc, #552]	; 12a0 <.text+0x12a0>
    1074:	eb000180 	bl	167c <jtrace>
    1078:	e3a00e4d 	mov	r0, #1232	; 0x4d0
    107c:	e2800002 	add	r0, r0, #2	; 0x2
    1080:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1084:	e3a02000 	mov	r2, #0	; 0x0
    1088:	ebfffd7a 	bl	678 <jitoa>
    108c:	e59f11fc 	ldr	r1, [pc, #508]	; 1290 <.text+0x1290>
    1090:	ebfffdef 	bl	854 <jstrcmp>
    1094:	e3500000 	cmp	r0, #0	; 0x0
    1098:	0a000003 	beq	10ac <jitoa_test+0x108>
    109c:	e59f01e4 	ldr	r0, [pc, #484]	; 1288 <.text+0x1288>
    10a0:	e3a01031 	mov	r1, #49	; 0x31
    10a4:	e59f21f8 	ldr	r2, [pc, #504]	; 12a4 <.text+0x12a4>
    10a8:	eb000173 	bl	167c <jtrace>
    10ac:	e3a0000a 	mov	r0, #10	; 0xa
    10b0:	e24b102c 	sub	r1, fp, #44	; 0x2c
    10b4:	e3a02000 	mov	r2, #0	; 0x0
    10b8:	ebfffd6e 	bl	678 <jitoa>
    10bc:	e59f11d4 	ldr	r1, [pc, #468]	; 1298 <.text+0x1298>
    10c0:	ebfffde3 	bl	854 <jstrcmp>
    10c4:	e3500000 	cmp	r0, #0	; 0x0
    10c8:	0a000003 	beq	10dc <jitoa_test+0x138>
    10cc:	e59f01b4 	ldr	r0, [pc, #436]	; 1288 <.text+0x1288>
    10d0:	e3a01032 	mov	r1, #50	; 0x32
    10d4:	e59f21cc 	ldr	r2, [pc, #460]	; 12a8 <.text+0x12a8>
    10d8:	eb000167 	bl	167c <jtrace>
    10dc:	e3e000ff 	mvn	r0, #255	; 0xff
    10e0:	e24b102c 	sub	r1, fp, #44	; 0x2c
    10e4:	e3a02010 	mov	r2, #16	; 0x10
    10e8:	ebfffd62 	bl	678 <jitoa>
    10ec:	e59f1190 	ldr	r1, [pc, #400]	; 1284 <.text+0x1284>
    10f0:	ebfffdd7 	bl	854 <jstrcmp>
    10f4:	e3500000 	cmp	r0, #0	; 0x0
    10f8:	0a000003 	beq	110c <jitoa_test+0x168>
    10fc:	e59f0184 	ldr	r0, [pc, #388]	; 1288 <.text+0x1288>
    1100:	e3a01034 	mov	r1, #52	; 0x34
    1104:	e59f21a0 	ldr	r2, [pc, #416]	; 12ac <.text+0x12ac>
    1108:	eb00015b 	bl	167c <jtrace>
    110c:	e3a00c12 	mov	r0, #4608	; 0x1200
    1110:	e2800034 	add	r0, r0, #52	; 0x34
    1114:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1118:	e3a02010 	mov	r2, #16	; 0x10
    111c:	ebfffd55 	bl	678 <jitoa>
    1120:	e59f1168 	ldr	r1, [pc, #360]	; 1290 <.text+0x1290>
    1124:	ebfffdca 	bl	854 <jstrcmp>
    1128:	e3500000 	cmp	r0, #0	; 0x0
    112c:	0a000003 	beq	1140 <jitoa_test+0x19c>
    1130:	e59f0150 	ldr	r0, [pc, #336]	; 1288 <.text+0x1288>
    1134:	e3a01035 	mov	r1, #53	; 0x35
    1138:	e59f2170 	ldr	r2, [pc, #368]	; 12b0 <.text+0x12b0>
    113c:	eb00014e 	bl	167c <jtrace>
    1140:	e3a00010 	mov	r0, #16	; 0x10
    1144:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1148:	e1a02000 	mov	r2, r0
    114c:	ebfffd49 	bl	678 <jitoa>
    1150:	e59f1140 	ldr	r1, [pc, #320]	; 1298 <.text+0x1298>
    1154:	ebfffdbe 	bl	854 <jstrcmp>
    1158:	e3500000 	cmp	r0, #0	; 0x0
    115c:	0a000003 	beq	1170 <jitoa_test+0x1cc>
    1160:	e59f0120 	ldr	r0, [pc, #288]	; 1288 <.text+0x1288>
    1164:	e3a01036 	mov	r1, #54	; 0x36
    1168:	e59f2144 	ldr	r2, [pc, #324]	; 12b4 <.text+0x12b4>
    116c:	eb000142 	bl	167c <jtrace>
    1170:	e3e0003f 	mvn	r0, #63	; 0x3f
    1174:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1178:	e3a02008 	mov	r2, #8	; 0x8
    117c:	ebfffd3d 	bl	678 <jitoa>
    1180:	e59f10fc 	ldr	r1, [pc, #252]	; 1284 <.text+0x1284>
    1184:	ebfffdb2 	bl	854 <jstrcmp>
    1188:	e3500000 	cmp	r0, #0	; 0x0
    118c:	0a000003 	beq	11a0 <jitoa_test+0x1fc>
    1190:	e59f00f0 	ldr	r0, [pc, #240]	; 1288 <.text+0x1288>
    1194:	e3a01038 	mov	r1, #56	; 0x38
    1198:	e59f2118 	ldr	r2, [pc, #280]	; 12b8 <.text+0x12b8>
    119c:	eb000136 	bl	167c <jtrace>
    11a0:	e3a00fa7 	mov	r0, #668	; 0x29c
    11a4:	e24b102c 	sub	r1, fp, #44	; 0x2c
    11a8:	e3a02008 	mov	r2, #8	; 0x8
    11ac:	ebfffd31 	bl	678 <jitoa>
    11b0:	e59f10d8 	ldr	r1, [pc, #216]	; 1290 <.text+0x1290>
    11b4:	ebfffda6 	bl	854 <jstrcmp>
    11b8:	e3500000 	cmp	r0, #0	; 0x0
    11bc:	0a000003 	beq	11d0 <jitoa_test+0x22c>
    11c0:	e59f00c0 	ldr	r0, [pc, #192]	; 1288 <.text+0x1288>
    11c4:	e3a01039 	mov	r1, #57	; 0x39
    11c8:	e59f20ec 	ldr	r2, [pc, #236]	; 12bc <.text+0x12bc>
    11cc:	eb00012a 	bl	167c <jtrace>
    11d0:	e3a00008 	mov	r0, #8	; 0x8
    11d4:	e24b102c 	sub	r1, fp, #44	; 0x2c
    11d8:	e1a02000 	mov	r2, r0
    11dc:	ebfffd25 	bl	678 <jitoa>
    11e0:	e59f10b0 	ldr	r1, [pc, #176]	; 1298 <.text+0x1298>
    11e4:	ebfffd9a 	bl	854 <jstrcmp>
    11e8:	e3500000 	cmp	r0, #0	; 0x0
    11ec:	0a000003 	beq	1200 <jitoa_test+0x25c>
    11f0:	e59f0090 	ldr	r0, [pc, #144]	; 1288 <.text+0x1288>
    11f4:	e3a0103a 	mov	r1, #58	; 0x3a
    11f8:	e59f20c0 	ldr	r2, [pc, #192]	; 12c0 <.text+0x12c0>
    11fc:	eb00011e 	bl	167c <jtrace>
    1200:	e3a03000 	mov	r3, #0	; 0x0
    1204:	e58d3000 	str	r3, [sp]
    1208:	e3e00eab 	mvn	r0, #2736	; 0xab0
    120c:	e240000b 	sub	r0, r0, #11	; 0xb
    1210:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1214:	e3a02001 	mov	r2, #1	; 0x1
    1218:	e2833010 	add	r3, r3, #16	; 0x10
    121c:	ebfffcb9 	bl	508 <jitoa_ex>
    1220:	e59f109c 	ldr	r1, [pc, #156]	; 12c4 <.text+0x12c4>
    1224:	ebfffd8a 	bl	854 <jstrcmp>
    1228:	e3500000 	cmp	r0, #0	; 0x0
    122c:	0a000003 	beq	1240 <jitoa_test+0x29c>
    1230:	e59f0050 	ldr	r0, [pc, #80]	; 1288 <.text+0x1288>
    1234:	e3a0103c 	mov	r1, #60	; 0x3c
    1238:	e59f2088 	ldr	r2, [pc, #136]	; 12c8 <.text+0x12c8>
    123c:	eb00010e 	bl	167c <jtrace>
    1240:	e3a02001 	mov	r2, #1	; 0x1
    1244:	e58d2000 	str	r2, [sp]
    1248:	e3a00eab 	mov	r0, #2736	; 0xab0
    124c:	e280000c 	add	r0, r0, #12	; 0xc
    1250:	e24b102c 	sub	r1, fp, #44	; 0x2c
    1254:	e3a03010 	mov	r3, #16	; 0x10
    1258:	ebfffcaa 	bl	508 <jitoa_ex>
    125c:	e59f1068 	ldr	r1, [pc, #104]	; 12cc <.text+0x12cc>
    1260:	ebfffd7b 	bl	854 <jstrcmp>
    1264:	e3500000 	cmp	r0, #0	; 0x0
    1268:	0a000003 	beq	127c <jitoa_test+0x2d8>
    126c:	e59f0014 	ldr	r0, [pc, #20]	; 1288 <.text+0x1288>
    1270:	e3a0103d 	mov	r1, #61	; 0x3d
    1274:	e59f2054 	ldr	r2, [pc, #84]	; 12d0 <.text+0x12d0>
    1278:	eb0000ff 	bl	167c <jtrace>
    127c:	e24bd00c 	sub	sp, fp, #12	; 0xc
    1280:	e89da800 	ldmia	sp, {fp, sp, pc}
    1284:	00002008 	andeq	r2, r0, r8
    1288:	00002630 	andeq	r2, r0, r0, lsr r6
    128c:	00002010 	andeq	r2, r0, r0, lsl r0
    1290:	00002040 	andeq	r2, r0, r0, asr #32
    1294:	00002048 	andeq	r2, r0, r8, asr #32
    1298:	00002078 	andeq	r2, r0, r8, ror r0
    129c:	00002080 	andeq	r2, r0, r0, lsl #1
    12a0:	000020a8 	andeq	r2, r0, r8, lsr #1
    12a4:	000020d8 	ldreqd	r2, [r0], -r8
    12a8:	00002108 	andeq	r2, r0, r8, lsl #2
    12ac:	00002130 	andeq	r2, r0, r0, lsr r1
    12b0:	00002160 	andeq	r2, r0, r0, ror #2
    12b4:	00002190 	muleq	r0, r0, r1
    12b8:	000021c0 	andeq	r2, r0, r0, asr #3
    12bc:	000021f0 	streqd	r2, [r0], -r0
    12c0:	00002220 	andeq	r2, r0, r0, lsr #4
    12c4:	00002248 	andeq	r2, r0, r8, asr #4
    12c8:	00002250 	andeq	r2, r0, r0, asr r2
    12cc:	00002288 	andeq	r2, r0, r8, lsl #5
    12d0:	00002290 	muleq	r0, r0, r2

000012d4 <jatoi_test>:
    12d4:	e1a0c00d 	mov	ip, sp
    12d8:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
    12dc:	e24cb004 	sub	fp, ip, #4	; 0x4
    12e0:	e24dd008 	sub	sp, sp, #8	; 0x8
    12e4:	e3a03000 	mov	r3, #0	; 0x0
    12e8:	e50b3010 	str	r3, [fp, #-16]
    12ec:	e59f02e8 	ldr	r0, [pc, #744]	; 15dc <.text+0x15dc>
    12f0:	ebfffc7d 	bl	4ec <jatoi>
    12f4:	e3500c01 	cmp	r0, #256	; 0x100
    12f8:	0a000003 	beq	130c <jatoi_test+0x38>
    12fc:	e59f02dc 	ldr	r0, [pc, #732]	; 15e0 <.text+0x15e0>
    1300:	e3a01009 	mov	r1, #9	; 0x9
    1304:	e59f22d8 	ldr	r2, [pc, #728]	; 15e4 <.text+0x15e4>
    1308:	eb0000db 	bl	167c <jtrace>
    130c:	e59f02d4 	ldr	r0, [pc, #724]	; 15e8 <.text+0x15e8>
    1310:	ebfffc75 	bl	4ec <jatoi>
    1314:	e3500040 	cmp	r0, #64	; 0x40
    1318:	0a000003 	beq	132c <jatoi_test+0x58>
    131c:	e59f02bc 	ldr	r0, [pc, #700]	; 15e0 <.text+0x15e0>
    1320:	e3a0100a 	mov	r1, #10	; 0xa
    1324:	e59f22c0 	ldr	r2, [pc, #704]	; 15ec <.text+0x15ec>
    1328:	eb0000d3 	bl	167c <jtrace>
    132c:	e59f02bc 	ldr	r0, [pc, #700]	; 15f0 <.text+0x15f0>
    1330:	ebfffc6d 	bl	4ec <jatoi>
    1334:	e3500064 	cmp	r0, #100	; 0x64
    1338:	0a000003 	beq	134c <jatoi_test+0x78>
    133c:	e59f029c 	ldr	r0, [pc, #668]	; 15e0 <.text+0x15e0>
    1340:	e3a0100b 	mov	r1, #11	; 0xb
    1344:	e59f22a8 	ldr	r2, [pc, #680]	; 15f4 <.text+0x15f4>
    1348:	eb0000cb 	bl	167c <jtrace>
    134c:	e59f02a4 	ldr	r0, [pc, #676]	; 15f8 <.text+0x15f8>
    1350:	ebfffc65 	bl	4ec <jatoi>
    1354:	e3500c01 	cmp	r0, #256	; 0x100
    1358:	0a000003 	beq	136c <jatoi_test+0x98>
    135c:	e59f027c 	ldr	r0, [pc, #636]	; 15e0 <.text+0x15e0>
    1360:	e3a0100d 	mov	r1, #13	; 0xd
    1364:	e59f2290 	ldr	r2, [pc, #656]	; 15fc <.text+0x15fc>
    1368:	eb0000c3 	bl	167c <jtrace>
    136c:	e59f028c 	ldr	r0, [pc, #652]	; 1600 <.text+0x1600>
    1370:	ebfffc5d 	bl	4ec <jatoi>
    1374:	e3500040 	cmp	r0, #64	; 0x40
    1378:	0a000003 	beq	138c <jatoi_test+0xb8>
    137c:	e59f025c 	ldr	r0, [pc, #604]	; 15e0 <.text+0x15e0>
    1380:	e3a0100e 	mov	r1, #14	; 0xe
    1384:	e59f2278 	ldr	r2, [pc, #632]	; 1604 <.text+0x1604>
    1388:	eb0000bb 	bl	167c <jtrace>
    138c:	e59f0274 	ldr	r0, [pc, #628]	; 1608 <.text+0x1608>
    1390:	ebfffc55 	bl	4ec <jatoi>
    1394:	e3500064 	cmp	r0, #100	; 0x64
    1398:	0a000003 	beq	13ac <jatoi_test+0xd8>
    139c:	e59f023c 	ldr	r0, [pc, #572]	; 15e0 <.text+0x15e0>
    13a0:	e3a0100f 	mov	r1, #15	; 0xf
    13a4:	e59f2260 	ldr	r2, [pc, #608]	; 160c <.text+0x160c>
    13a8:	eb0000b3 	bl	167c <jtrace>
    13ac:	e59f025c 	ldr	r0, [pc, #604]	; 1610 <.text+0x1610>
    13b0:	ebfffc4d 	bl	4ec <jatoi>
    13b4:	e3700c01 	cmn	r0, #256	; 0x100
    13b8:	0a000003 	beq	13cc <jatoi_test+0xf8>
    13bc:	e59f021c 	ldr	r0, [pc, #540]	; 15e0 <.text+0x15e0>
    13c0:	e3a01011 	mov	r1, #17	; 0x11
    13c4:	e59f2248 	ldr	r2, [pc, #584]	; 1614 <.text+0x1614>
    13c8:	eb0000ab 	bl	167c <jtrace>
    13cc:	e59f0244 	ldr	r0, [pc, #580]	; 1618 <.text+0x1618>
    13d0:	ebfffc45 	bl	4ec <jatoi>
    13d4:	e3700040 	cmn	r0, #64	; 0x40
    13d8:	0a000003 	beq	13ec <jatoi_test+0x118>
    13dc:	e59f01fc 	ldr	r0, [pc, #508]	; 15e0 <.text+0x15e0>
    13e0:	e3a01012 	mov	r1, #18	; 0x12
    13e4:	e59f2230 	ldr	r2, [pc, #560]	; 161c <.text+0x161c>
    13e8:	eb0000a3 	bl	167c <jtrace>
    13ec:	e59f022c 	ldr	r0, [pc, #556]	; 1620 <.text+0x1620>
    13f0:	ebfffc3d 	bl	4ec <jatoi>
    13f4:	e3700064 	cmn	r0, #100	; 0x64
    13f8:	0a000003 	beq	140c <jatoi_test+0x138>
    13fc:	e59f01dc 	ldr	r0, [pc, #476]	; 15e0 <.text+0x15e0>
    1400:	e3a01013 	mov	r1, #19	; 0x13
    1404:	e59f2218 	ldr	r2, [pc, #536]	; 1624 <.text+0x1624>
    1408:	eb00009b 	bl	167c <jtrace>
    140c:	e59f0214 	ldr	r0, [pc, #532]	; 1628 <.text+0x1628>
    1410:	ebfffc35 	bl	4ec <jatoi>
    1414:	e3500c01 	cmp	r0, #256	; 0x100
    1418:	0a000003 	beq	142c <jatoi_test+0x158>
    141c:	e59f01bc 	ldr	r0, [pc, #444]	; 15e0 <.text+0x15e0>
    1420:	e3a01015 	mov	r1, #21	; 0x15
    1424:	e59f2200 	ldr	r2, [pc, #512]	; 162c <.text+0x162c>
    1428:	eb000093 	bl	167c <jtrace>
    142c:	e59f01fc 	ldr	r0, [pc, #508]	; 1630 <.text+0x1630>
    1430:	ebfffc2d 	bl	4ec <jatoi>
    1434:	e3500040 	cmp	r0, #64	; 0x40
    1438:	0a000003 	beq	144c <jatoi_test+0x178>
    143c:	e59f019c 	ldr	r0, [pc, #412]	; 15e0 <.text+0x15e0>
    1440:	e3a01016 	mov	r1, #22	; 0x16
    1444:	e59f21e8 	ldr	r2, [pc, #488]	; 1634 <.text+0x1634>
    1448:	eb00008b 	bl	167c <jtrace>
    144c:	e59f01e4 	ldr	r0, [pc, #484]	; 1638 <.text+0x1638>
    1450:	ebfffc25 	bl	4ec <jatoi>
    1454:	e3500064 	cmp	r0, #100	; 0x64
    1458:	0a000003 	beq	146c <jatoi_test+0x198>
    145c:	e59f017c 	ldr	r0, [pc, #380]	; 15e0 <.text+0x15e0>
    1460:	e3a01017 	mov	r1, #23	; 0x17
    1464:	e59f21d0 	ldr	r2, [pc, #464]	; 163c <.text+0x163c>
    1468:	eb000083 	bl	167c <jtrace>
    146c:	e59f01cc 	ldr	r0, [pc, #460]	; 1640 <.text+0x1640>
    1470:	ebfffc1d 	bl	4ec <jatoi>
    1474:	e3500c01 	cmp	r0, #256	; 0x100
    1478:	0a000003 	beq	148c <jatoi_test+0x1b8>
    147c:	e59f015c 	ldr	r0, [pc, #348]	; 15e0 <.text+0x15e0>
    1480:	e3a01019 	mov	r1, #25	; 0x19
    1484:	e59f21b8 	ldr	r2, [pc, #440]	; 1644 <.text+0x1644>
    1488:	eb00007b 	bl	167c <jtrace>
    148c:	e59f01b4 	ldr	r0, [pc, #436]	; 1648 <.text+0x1648>
    1490:	ebfffc15 	bl	4ec <jatoi>
    1494:	e3500040 	cmp	r0, #64	; 0x40
    1498:	0a000003 	beq	14ac <jatoi_test+0x1d8>
    149c:	e59f013c 	ldr	r0, [pc, #316]	; 15e0 <.text+0x15e0>
    14a0:	e3a0101a 	mov	r1, #26	; 0x1a
    14a4:	e59f21a0 	ldr	r2, [pc, #416]	; 164c <.text+0x164c>
    14a8:	eb000073 	bl	167c <jtrace>
    14ac:	e59f019c 	ldr	r0, [pc, #412]	; 1650 <.text+0x1650>
    14b0:	ebfffc0d 	bl	4ec <jatoi>
    14b4:	e3500064 	cmp	r0, #100	; 0x64
    14b8:	0a000003 	beq	14cc <jatoi_test+0x1f8>
    14bc:	e59f011c 	ldr	r0, [pc, #284]	; 15e0 <.text+0x15e0>
    14c0:	e3a0101b 	mov	r1, #27	; 0x1b
    14c4:	e59f2188 	ldr	r2, [pc, #392]	; 1654 <.text+0x1654>
    14c8:	eb00006b 	bl	167c <jtrace>
    14cc:	e59f0184 	ldr	r0, [pc, #388]	; 1658 <.text+0x1658>
    14d0:	ebfffc05 	bl	4ec <jatoi>
    14d4:	e3500c01 	cmp	r0, #256	; 0x100
    14d8:	0a000003 	beq	14ec <jatoi_test+0x218>
    14dc:	e59f00fc 	ldr	r0, [pc, #252]	; 15e0 <.text+0x15e0>
    14e0:	e3a0101d 	mov	r1, #29	; 0x1d
    14e4:	e59f2170 	ldr	r2, [pc, #368]	; 165c <.text+0x165c>
    14e8:	eb000063 	bl	167c <jtrace>
    14ec:	e59f016c 	ldr	r0, [pc, #364]	; 1660 <.text+0x1660>
    14f0:	ebfffbfd 	bl	4ec <jatoi>
    14f4:	e3500040 	cmp	r0, #64	; 0x40
    14f8:	0a000003 	beq	150c <jatoi_test+0x238>
    14fc:	e59f00dc 	ldr	r0, [pc, #220]	; 15e0 <.text+0x15e0>
    1500:	e3a0101e 	mov	r1, #30	; 0x1e
    1504:	e59f2158 	ldr	r2, [pc, #344]	; 1664 <.text+0x1664>
    1508:	eb00005b 	bl	167c <jtrace>
    150c:	e59f0154 	ldr	r0, [pc, #340]	; 1668 <.text+0x1668>
    1510:	ebfffbf5 	bl	4ec <jatoi>
    1514:	e3500064 	cmp	r0, #100	; 0x64
    1518:	0a000003 	beq	152c <jatoi_test+0x258>
    151c:	e59f00bc 	ldr	r0, [pc, #188]	; 15e0 <.text+0x15e0>
    1520:	e3a0101f 	mov	r1, #31	; 0x1f
    1524:	e59f2140 	ldr	r2, [pc, #320]	; 166c <.text+0x166c>
    1528:	eb000053 	bl	167c <jtrace>
    152c:	e59f0124 	ldr	r0, [pc, #292]	; 1658 <.text+0x1658>
    1530:	e24b1010 	sub	r1, fp, #16	; 0x10
    1534:	e3a02000 	mov	r2, #0	; 0x0
    1538:	ebfffbd1 	bl	484 <jstrtol>
    153c:	e3500c01 	cmp	r0, #256	; 0x100
    1540:	1a000003 	bne	1554 <jatoi_test+0x280>
    1544:	e51b3010 	ldr	r3, [fp, #-16]
    1548:	e5d33000 	ldrb	r3, [r3]
    154c:	e3530068 	cmp	r3, #104	; 0x68
    1550:	0a000003 	beq	1564 <jatoi_test+0x290>
    1554:	e59f0084 	ldr	r0, [pc, #132]	; 15e0 <.text+0x15e0>
    1558:	e3a01021 	mov	r1, #33	; 0x21
    155c:	e59f210c 	ldr	r2, [pc, #268]	; 1670 <.text+0x1670>
    1560:	eb000045 	bl	167c <jtrace>
    1564:	e59f00f4 	ldr	r0, [pc, #244]	; 1660 <.text+0x1660>
    1568:	e24b1010 	sub	r1, fp, #16	; 0x10
    156c:	e3a02000 	mov	r2, #0	; 0x0
    1570:	ebfffbc3 	bl	484 <jstrtol>
    1574:	e3500040 	cmp	r0, #64	; 0x40
    1578:	1a000003 	bne	158c <jatoi_test+0x2b8>
    157c:	e51b3010 	ldr	r3, [fp, #-16]
    1580:	e5d33000 	ldrb	r3, [r3]
    1584:	e3530038 	cmp	r3, #56	; 0x38
    1588:	0a000003 	beq	159c <jatoi_test+0x2c8>
    158c:	e59f004c 	ldr	r0, [pc, #76]	; 15e0 <.text+0x15e0>
    1590:	e3a01022 	mov	r1, #34	; 0x22
    1594:	e59f20d8 	ldr	r2, [pc, #216]	; 1674 <.text+0x1674>
    1598:	eb000037 	bl	167c <jtrace>
    159c:	e59f00c4 	ldr	r0, [pc, #196]	; 1668 <.text+0x1668>
    15a0:	e24b1010 	sub	r1, fp, #16	; 0x10
    15a4:	e3a02000 	mov	r2, #0	; 0x0
    15a8:	ebfffbb5 	bl	484 <jstrtol>
    15ac:	e3500064 	cmp	r0, #100	; 0x64
    15b0:	1a000003 	bne	15c4 <jatoi_test+0x2f0>
    15b4:	e51b3010 	ldr	r3, [fp, #-16]
    15b8:	e5d33000 	ldrb	r3, [r3]
    15bc:	e3530061 	cmp	r3, #97	; 0x61
    15c0:	0a000003 	beq	15d4 <jatoi_test+0x300>
    15c4:	e59f0014 	ldr	r0, [pc, #20]	; 15e0 <.text+0x15e0>
    15c8:	e3a01023 	mov	r1, #35	; 0x23
    15cc:	e59f20a4 	ldr	r2, [pc, #164]	; 1678 <.text+0x1678>
    15d0:	eb000029 	bl	167c <jtrace>
    15d4:	e24bd00c 	sub	sp, fp, #12	; 0xc
    15d8:	e89da800 	ldmia	sp, {fp, sp, pc}
    15dc:	000022c8 	andeq	r2, r0, r8, asr #5
    15e0:	00002640 	andeq	r2, r0, r0, asr #12
    15e4:	000022d0 	ldreqd	r2, [r0], -r0
    15e8:	000022e8 	andeq	r2, r0, r8, ror #5
    15ec:	000022f0 	streqd	r2, [r0], -r0
    15f0:	00002318 	andeq	r2, r0, r8, lsl r3
    15f4:	00002308 	andeq	r2, r0, r8, lsl #6
    15f8:	00002320 	andeq	r2, r0, r0, lsr #6
    15fc:	00002328 	andeq	r2, r0, r8, lsr #6
    1600:	00002348 	andeq	r2, r0, r8, asr #6
    1604:	00002350 	andeq	r2, r0, r0, asr r3
    1608:	00002368 	andeq	r2, r0, r8, ror #6
    160c:	00002370 	andeq	r2, r0, r0, ror r3
    1610:	00002388 	andeq	r2, r0, r8, lsl #7
    1614:	00002390 	muleq	r0, r0, r3
    1618:	000023b0 	streqh	r2, [r0], -r0
    161c:	000023b8 	streqh	r2, [r0], -r8
    1620:	00002008 	andeq	r2, r0, r8
    1624:	000023d0 	ldreqd	r2, [r0], -r0
    1628:	000023e8 	andeq	r2, r0, r8, ror #7
    162c:	000023f8 	streqd	r2, [r0], -r8
    1630:	00002418 	andeq	r2, r0, r8, lsl r4
    1634:	00002420 	andeq	r2, r0, r0, lsr #8
    1638:	00002438 	andeq	r2, r0, r8, lsr r4
    163c:	00002440 	andeq	r2, r0, r0, asr #8
    1640:	00002458 	andeq	r2, r0, r8, asr r4
    1644:	00002468 	andeq	r2, r0, r8, ror #8
    1648:	00002488 	andeq	r2, r0, r8, lsl #9
    164c:	00002490 	muleq	r0, r0, r4
    1650:	000024b0 	streqh	r2, [r0], -r0
    1654:	000024b8 	streqh	r2, [r0], -r8
    1658:	000024d0 	ldreqd	r2, [r0], -r0
    165c:	000024e0 	andeq	r2, r0, r0, ror #9
    1660:	00002500 	andeq	r2, r0, r0, lsl #10
    1664:	00002508 	andeq	r2, r0, r8, lsl #10
    1668:	00002528 	andeq	r2, r0, r8, lsr #10
    166c:	00002530 	andeq	r2, r0, r0, lsr r5
    1670:	00002548 	andeq	r2, r0, r8, asr #10
    1674:	00002588 	andeq	r2, r0, r8, lsl #11
    1678:	000025c8 	andeq	r2, r0, r8, asr #11

0000167c <jtrace>:
	return sizeof(str) - info.avail_length;
}

void jtrace(const char* func, int line, const char* message)
{
    167c:	e1a0c00d 	mov	ip, sp
    1680:	e92dd800 	stmdb	sp!, {fp, ip, lr, pc}
    1684:	e24cb004 	sub	fp, ip, #4	; 0x4
    1688:	e1a0c000 	mov	ip, r0
    168c:	e1a0e001 	mov	lr, r1
    1690:	e1a03002 	mov	r3, r2
#ifndef PC
	syscall(SYS_TRACE, (jword_t)func, line, (jword_t)message);
    1694:	e3a00001 	mov	r0, #1	; 0x1
    1698:	e1a0100c 	mov	r1, ip
    169c:	e1a0200e 	mov	r2, lr
    16a0:	ebfffb1a 	bl	310 <syscall>
#endif
	return;
}
    16a4:	e89da800 	ldmia	sp, {fp, sp, pc}

000016a8 <str_save>:
    16a8:	e1a0c00d 	mov	ip, sp
    16ac:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
    16b0:	e24cb004 	sub	fp, ip, #4	; 0x4
    16b4:	e1a05000 	mov	r5, r0
    16b8:	e3500000 	cmp	r0, #0	; 0x0
    16bc:	13510000 	cmpne	r1, #0	; 0x0
    16c0:	0a00000d 	beq	16fc <str_save+0x54>
    16c4:	e3520000 	cmp	r2, #0	; 0x0
    16c8:	0a00000b 	beq	16fc <str_save+0x54>
    16cc:	e5904008 	ldr	r4, [r0, #8]
    16d0:	e1520004 	cmp	r2, r4
    16d4:	31a04002 	movcc	r4, r2
    16d8:	e5900004 	ldr	r0, [r0, #4]
    16dc:	e1a02004 	mov	r2, r4
    16e0:	ebfffc43 	bl	7f4 <jstrncpy>
    16e4:	e5953004 	ldr	r3, [r5, #4]
    16e8:	e0833004 	add	r3, r3, r4
    16ec:	e5853004 	str	r3, [r5, #4]
    16f0:	e5953008 	ldr	r3, [r5, #8]
    16f4:	e0643003 	rsb	r3, r4, r3
    16f8:	e5853008 	str	r3, [r5, #8]
    16fc:	e3a00000 	mov	r0, #0	; 0x0
    1700:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}

00001704 <jvprintf>:
    1704:	e1a0c00d 	mov	ip, sp
    1708:	e92dddf0 	stmdb	sp!, {r4, r5, r6, r7, r8, sl, fp, ip, lr, pc}
    170c:	e24cb004 	sub	fp, ip, #4	; 0x4
    1710:	e24dd028 	sub	sp, sp, #40	; 0x28
    1714:	e1a07001 	mov	r7, r1
    1718:	e1a08003 	mov	r8, r3
    171c:	e1a06000 	mov	r6, r0
    1720:	e3520000 	cmp	r2, #0	; 0x0
    1724:	13500000 	cmpne	r0, #0	; 0x0
    1728:	0a00007c 	beq	1920 <.text+0x1920>
    172c:	e5d23000 	ldrb	r3, [r2]
    1730:	e3530000 	cmp	r3, #0	; 0x0
    1734:	0a000079 	beq	1920 <.text+0x1920>
    1738:	e1a04002 	mov	r4, r2
    173c:	e24ba044 	sub	sl, fp, #68	; 0x44
    1740:	e3530025 	cmp	r3, #37	; 0x25
    1744:	1a00006c 	bne	18fc <.text+0x18fc>
    1748:	e2845001 	add	r5, r4, #1	; 0x1
    174c:	e5d43001 	ldrb	r3, [r4, #1]
    1750:	e2433058 	sub	r3, r3, #88	; 0x58
    1754:	e3530020 	cmp	r3, #32	; 0x20
    1758:	979ff103 	ldrls	pc, [pc, r3, lsl #2]
    175c:	ea000061 	b	18e8 <.text+0x18e8>
    1760:	00001878 	andeq	r1, r0, r8, ror r8
    1764:	000018e8 	andeq	r1, r0, r8, ror #17
    1768:	000018e8 	andeq	r1, r0, r8, ror #17
    176c:	000018e8 	andeq	r1, r0, r8, ror #17
    1770:	000018e8 	andeq	r1, r0, r8, ror #17
    1774:	000018e8 	andeq	r1, r0, r8, ror #17
    1778:	000018e8 	andeq	r1, r0, r8, ror #17
    177c:	000018e8 	andeq	r1, r0, r8, ror #17
    1780:	000018e8 	andeq	r1, r0, r8, ror #17
    1784:	000018e8 	andeq	r1, r0, r8, ror #17
    1788:	000018e8 	andeq	r1, r0, r8, ror #17
    178c:	000018e8 	andeq	r1, r0, r8, ror #17
    1790:	00001810 	andeq	r1, r0, r0, lsl r8
    1794:	000018e8 	andeq	r1, r0, r8, ror #17
    1798:	000018e8 	andeq	r1, r0, r8, ror #17
    179c:	000018e8 	andeq	r1, r0, r8, ror #17
    17a0:	000018e8 	andeq	r1, r0, r8, ror #17
    17a4:	000018e8 	andeq	r1, r0, r8, ror #17
    17a8:	000018e8 	andeq	r1, r0, r8, ror #17
    17ac:	000018e8 	andeq	r1, r0, r8, ror #17
    17b0:	000018e8 	andeq	r1, r0, r8, ror #17
    17b4:	000018e8 	andeq	r1, r0, r8, ror #17
    17b8:	000018e8 	andeq	r1, r0, r8, ror #17
    17bc:	000018e8 	andeq	r1, r0, r8, ror #17
    17c0:	000018b0 	streqh	r1, [r0], -r0
    17c4:	000018e8 	andeq	r1, r0, r8, ror #17
    17c8:	000018e8 	andeq	r1, r0, r8, ror #17
    17cc:	000017e4 	andeq	r1, r0, r4, ror #15
    17d0:	000018e8 	andeq	r1, r0, r8, ror #17
    17d4:	000018e8 	andeq	r1, r0, r8, ror #17
    17d8:	000018e8 	andeq	r1, r0, r8, ror #17
    17dc:	000018e8 	andeq	r1, r0, r8, ror #17
    17e0:	0000183c 	andeq	r1, r0, ip, lsr r8
    17e4:	e4984004 	ldr	r4, [r8], #4
    17e8:	e59f313c 	ldr	r3, [pc, #316]	; 192c <.text+0x192c>
    17ec:	e3540000 	cmp	r4, #0	; 0x0
    17f0:	01a04003 	moveq	r4, r3
    17f4:	e1a00004 	mov	r0, r4
    17f8:	ebfffc5c 	bl	970 <jstrlen>
    17fc:	e1a02000 	mov	r2, r0
    1800:	e1a00007 	mov	r0, r7
    1804:	e1a01004 	mov	r1, r4
    1808:	e12fff36 	blx	r6
    180c:	ea00003f 	b	1910 <.text+0x1910>
    1810:	e4980004 	ldr	r0, [r8], #4
    1814:	e1a0100a 	mov	r1, sl
    1818:	e3a0200a 	mov	r2, #10	; 0xa
    181c:	ebfffb95 	bl	678 <jitoa>
    1820:	e1a0000a 	mov	r0, sl
    1824:	ebfffc51 	bl	970 <jstrlen>
    1828:	e1a02000 	mov	r2, r0
    182c:	e1a00007 	mov	r0, r7
    1830:	e1a0100a 	mov	r1, sl
    1834:	e12fff36 	blx	r6
    1838:	ea000034 	b	1910 <.text+0x1910>
    183c:	e4980004 	ldr	r0, [r8], #4
    1840:	e1a0100a 	mov	r1, sl
    1844:	e3a02010 	mov	r2, #16	; 0x10
    1848:	ebfffb8a 	bl	678 <jitoa>
    184c:	e59f00dc 	ldr	r0, [pc, #220]	; 1930 <.text+0x1930>
    1850:	e3a0102d 	mov	r1, #45	; 0x2d
    1854:	e1a0200a 	mov	r2, sl
    1858:	ebffff87 	bl	167c <jtrace>
    185c:	e1a0000a 	mov	r0, sl
    1860:	ebfffc42 	bl	970 <jstrlen>
    1864:	e1a02000 	mov	r2, r0
    1868:	e1a00007 	mov	r0, r7
    186c:	e1a0100a 	mov	r1, sl
    1870:	e12fff36 	blx	r6
    1874:	ea000025 	b	1910 <.text+0x1910>
    1878:	e4980004 	ldr	r0, [r8], #4
    187c:	e3a03001 	mov	r3, #1	; 0x1
    1880:	e58d3000 	str	r3, [sp]
    1884:	e1a0100a 	mov	r1, sl
    1888:	e3a02000 	mov	r2, #0	; 0x0
    188c:	e283300f 	add	r3, r3, #15	; 0xf
    1890:	ebfffb1c 	bl	508 <jitoa_ex>
    1894:	e1a0000a 	mov	r0, sl
    1898:	ebfffc34 	bl	970 <jstrlen>
    189c:	e1a02000 	mov	r2, r0
    18a0:	e1a00007 	mov	r0, r7
    18a4:	e1a0100a 	mov	r1, sl
    18a8:	e12fff36 	blx	r6
    18ac:	ea000017 	b	1910 <.text+0x1910>
    18b0:	e4980004 	ldr	r0, [r8], #4
    18b4:	e3a03000 	mov	r3, #0	; 0x0
    18b8:	e58d3000 	str	r3, [sp]
    18bc:	e1a0100a 	mov	r1, sl
    18c0:	e3a02001 	mov	r2, #1	; 0x1
    18c4:	e2833010 	add	r3, r3, #16	; 0x10
    18c8:	ebfffb0e 	bl	508 <jitoa_ex>
    18cc:	e1a0000a 	mov	r0, sl
    18d0:	ebfffc26 	bl	970 <jstrlen>
    18d4:	e1a02000 	mov	r2, r0
    18d8:	e1a00007 	mov	r0, r7
    18dc:	e1a0100a 	mov	r1, sl
    18e0:	e12fff36 	blx	r6
    18e4:	ea000009 	b	1910 <.text+0x1910>
    18e8:	e1a00007 	mov	r0, r7
    18ec:	e1a01004 	mov	r1, r4
    18f0:	e3a02001 	mov	r2, #1	; 0x1
    18f4:	e12fff36 	blx	r6
    18f8:	ea000004 	b	1910 <.text+0x1910>
    18fc:	e1a00007 	mov	r0, r7
    1900:	e1a01004 	mov	r1, r4
    1904:	e3a02001 	mov	r2, #1	; 0x1
    1908:	e12fff36 	blx	r6
    190c:	e1a05004 	mov	r5, r4
    1910:	e2854001 	add	r4, r5, #1	; 0x1
    1914:	e5d53001 	ldrb	r3, [r5, #1]
    1918:	e3530000 	cmp	r3, #0	; 0x0
    191c:	1affff87 	bne	1740 <jvprintf+0x3c>
    1920:	e3a00000 	mov	r0, #0	; 0x0
    1924:	e24bd024 	sub	sp, fp, #36	; 0x24
    1928:	e89dadf0 	ldmia	sp, {r4, r5, r6, r7, r8, sl, fp, sp, pc}
    192c:	00002650 	andeq	r2, r0, r0, asr r6
    1930:	00002660 	andeq	r2, r0, r0, ror #12

00001934 <jprintf>:
    1934:	e1a0c00d 	mov	ip, sp
    1938:	e92d000f 	stmdb	sp!, {r0, r1, r2, r3}
    193c:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
    1940:	e24cb014 	sub	fp, ip, #20	; 0x14
    1944:	e24dde21 	sub	sp, sp, #528	; 0x210
    1948:	e24b4f85 	sub	r4, fp, #532	; 0x214
    194c:	e50b4220 	str	r4, [fp, #-544]
    1950:	e50b421c 	str	r4, [fp, #-540]
    1954:	e3a02c02 	mov	r2, #512	; 0x200
    1958:	e50b2218 	str	r2, [fp, #-536]
    195c:	e1a00004 	mov	r0, r4
    1960:	e3a01000 	mov	r1, #0	; 0x0
    1964:	ebfffb4e 	bl	6a4 <jmemset>
    1968:	e59f0030 	ldr	r0, [pc, #48]	; 19a0 <.text+0x19a0>
    196c:	e24b1e22 	sub	r1, fp, #544	; 0x220
    1970:	e59b2004 	ldr	r2, [fp, #4]
    1974:	e28b3004 	add	r3, fp, #4	; 0x4
    1978:	e2833004 	add	r3, r3, #4	; 0x4
    197c:	ebffff60 	bl	1704 <jvprintf>
    1980:	e59f001c 	ldr	r0, [pc, #28]	; 19a4 <.text+0x19a4>
    1984:	e3a0107d 	mov	r1, #125	; 0x7d
    1988:	e1a02004 	mov	r2, r4
    198c:	ebffff3a 	bl	167c <jtrace>
    1990:	e51b0218 	ldr	r0, [fp, #-536]
    1994:	e2600c02 	rsb	r0, r0, #512	; 0x200
    1998:	e24bd014 	sub	sp, fp, #20	; 0x14
    199c:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
    19a0:	000016a8 	andeq	r1, r0, r8, lsr #13
    19a4:	00002658 	andeq	r2, r0, r8, asr r6

000019a8 <jsnprintf>:
    19a8:	e1a0c00d 	mov	ip, sp
    19ac:	e92d000c 	stmdb	sp!, {r2, r3}
    19b0:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
    19b4:	e24cb00c 	sub	fp, ip, #12	; 0xc
    19b8:	e24dd010 	sub	sp, sp, #16	; 0x10
    19bc:	e1a04001 	mov	r4, r1
    19c0:	e50b0020 	str	r0, [fp, #-32]
    19c4:	e50b001c 	str	r0, [fp, #-28]
    19c8:	e50b1018 	str	r1, [fp, #-24]
    19cc:	e59f001c 	ldr	r0, [pc, #28]	; 19f0 <.text+0x19f0>
    19d0:	e24b1020 	sub	r1, fp, #32	; 0x20
    19d4:	e59b2004 	ldr	r2, [fp, #4]
    19d8:	e28b3008 	add	r3, fp, #8	; 0x8
    19dc:	ebffff48 	bl	1704 <jvprintf>
    19e0:	e51b0018 	ldr	r0, [fp, #-24]
    19e4:	e0600004 	rsb	r0, r0, r4
    19e8:	e24bd014 	sub	sp, fp, #20	; 0x14
    19ec:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
    19f0:	000016a8 	andeq	r1, r0, r8, lsr #13

000019f4 <isascii>:
	return islower(c) || isupper(c);
}

int isascii(int c)
{
    19f4:	e2400001 	sub	r0, r0, #1	; 0x1
	return c > 0 && c < 127;
}
    19f8:	e350007d 	cmp	r0, #125	; 0x7d
    19fc:	83a00000 	movhi	r0, #0	; 0x0
    1a00:	93a00001 	movls	r0, #1	; 0x1
    1a04:	e12fff1e 	bx	lr

00001a08 <isblank>:

int isblank(int c)
{
	return c < 32;
}
    1a08:	e350001f 	cmp	r0, #31	; 0x1f
    1a0c:	c3a00000 	movgt	r0, #0	; 0x0
    1a10:	d3a00001 	movle	r0, #1	; 0x1
    1a14:	e12fff1e 	bx	lr

00001a18 <iscntrl>:

int iscntrl(int c)
{
	return 0;
}
    1a18:	e3a00000 	mov	r0, #0	; 0x0
    1a1c:	e12fff1e 	bx	lr

00001a20 <isdigit>:

int isdigit(int c)
{
    1a20:	e2400030 	sub	r0, r0, #48	; 0x30
	return c >= '0' && c <= '9';
}
    1a24:	e3500009 	cmp	r0, #9	; 0x9
    1a28:	83a00000 	movhi	r0, #0	; 0x0
    1a2c:	93a00001 	movls	r0, #1	; 0x1
    1a30:	e12fff1e 	bx	lr

00001a34 <isgraph>:

int isgraph(int c)
{
	return 0;
}
    1a34:	e3a00000 	mov	r0, #0	; 0x0
    1a38:	e12fff1e 	bx	lr

00001a3c <islower>:

int islower(int c)
{
    1a3c:	e2400061 	sub	r0, r0, #97	; 0x61
	return c >= 'a' && c <= 'z';
}
    1a40:	e3500019 	cmp	r0, #25	; 0x19
    1a44:	83a00000 	movhi	r0, #0	; 0x0
    1a48:	93a00001 	movls	r0, #1	; 0x1
    1a4c:	e12fff1e 	bx	lr

00001a50 <isprint>:

int isprint(int c)
{
    1a50:	e2400020 	sub	r0, r0, #32	; 0x20
	return c >= 32 && c < 127;
}
    1a54:	e350005e 	cmp	r0, #94	; 0x5e
    1a58:	83a00000 	movhi	r0, #0	; 0x0
    1a5c:	93a00001 	movls	r0, #1	; 0x1
    1a60:	e12fff1e 	bx	lr

00001a64 <ispunct>:

int ispunct(int c)
{
	return 0;
}
    1a64:	e3a00000 	mov	r0, #0	; 0x0
    1a68:	e12fff1e 	bx	lr

00001a6c <isspace>:

int isspace(int c)
{
	return c == ' ' || c == '\t';
}
    1a6c:	e3500009 	cmp	r0, #9	; 0x9
    1a70:	13500020 	cmpne	r0, #32	; 0x20
    1a74:	13a00000 	movne	r0, #0	; 0x0
    1a78:	03a00001 	moveq	r0, #1	; 0x1
    1a7c:	e12fff1e 	bx	lr

00001a80 <isupper>:

int isupper(int c)
{
    1a80:	e2400041 	sub	r0, r0, #65	; 0x41
	return c >= 'A' && c <= 'Z';
}
    1a84:	e3500019 	cmp	r0, #25	; 0x19
    1a88:	83a00000 	movhi	r0, #0	; 0x0
    1a8c:	93a00001 	movls	r0, #1	; 0x1
    1a90:	e12fff1e 	bx	lr

00001a94 <isalpha>:
    1a94:	e1a0c00d 	mov	ip, sp
    1a98:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
    1a9c:	e24cb004 	sub	fp, ip, #4	; 0x4
    1aa0:	e1a04000 	mov	r4, r0
    1aa4:	ebffffe4 	bl	1a3c <islower>
    1aa8:	e3500000 	cmp	r0, #0	; 0x0
    1aac:	0a000001 	beq	1ab8 <isalpha+0x24>
    1ab0:	e3a00001 	mov	r0, #1	; 0x1
    1ab4:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
    1ab8:	e1a00004 	mov	r0, r4
    1abc:	ebffffef 	bl	1a80 <isupper>
    1ac0:	e2500000 	subs	r0, r0, #0	; 0x0
    1ac4:	13a00001 	movne	r0, #1	; 0x1
    1ac8:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}

00001acc <isalnum>:
    1acc:	e1a0c00d 	mov	ip, sp
    1ad0:	e92dd830 	stmdb	sp!, {r4, r5, fp, ip, lr, pc}
    1ad4:	e24cb004 	sub	fp, ip, #4	; 0x4
    1ad8:	e1a04000 	mov	r4, r0
    1adc:	ebffffec 	bl	1a94 <isalpha>
    1ae0:	e3500000 	cmp	r0, #0	; 0x0
    1ae4:	0a000001 	beq	1af0 <isalnum+0x24>
    1ae8:	e3a00001 	mov	r0, #1	; 0x1
    1aec:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}
    1af0:	e2443030 	sub	r3, r4, #48	; 0x30
    1af4:	e3530009 	cmp	r3, #9	; 0x9
    1af8:	83a00000 	movhi	r0, #0	; 0x0
    1afc:	93a00001 	movls	r0, #1	; 0x1
    1b00:	e89da830 	ldmia	sp, {r4, r5, fp, sp, pc}

00001b04 <isxdigit>:

int isxdigit(int c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    1b04:	e2402030 	sub	r2, r0, #48	; 0x30
    1b08:	e2403061 	sub	r3, r0, #97	; 0x61
    1b0c:	e3530005 	cmp	r3, #5	; 0x5
    1b10:	83520009 	cmphi	r2, #9	; 0x9
    1b14:	93a00001 	movls	r0, #1	; 0x1
    1b18:	912fff1e 	bxls	lr
    1b1c:	e2403041 	sub	r3, r0, #65	; 0x41
    1b20:	e3530005 	cmp	r3, #5	; 0x5
    1b24:	83a00000 	movhi	r0, #0	; 0x0
    1b28:	93a00001 	movls	r0, #1	; 0x1
}
    1b2c:	e12fff1e 	bx	lr
