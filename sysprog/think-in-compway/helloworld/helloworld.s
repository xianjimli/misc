
helloworld:     file format elf32-i386


Disassembly of section .init:

08048290 <_init>:
 8048290:	55                   	push   %ebp
 8048291:	89 e5                	mov    %esp,%ebp
 8048293:	53                   	push   %ebx
 8048294:	83 ec 04             	sub    $0x4,%esp
 8048297:	e8 00 00 00 00       	call   804829c <_init+0xc>
 804829c:	5b                   	pop    %ebx
 804829d:	81 c3 6c 13 00 00    	add    $0x136c,%ebx
 80482a3:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 80482a9:	85 d2                	test   %edx,%edx
 80482ab:	74 05                	je     80482b2 <_init+0x22>
 80482ad:	e8 1e 00 00 00       	call   80482d0 <__gmon_start__@plt>
 80482b2:	e8 d9 00 00 00       	call   8048390 <frame_dummy>
 80482b7:	e8 94 01 00 00       	call   8048450 <__do_global_ctors_aux>
 80482bc:	58                   	pop    %eax
 80482bd:	5b                   	pop    %ebx
 80482be:	c9                   	leave  
 80482bf:	c3                   	ret    

Disassembly of section .plt:

080482c0 <__gmon_start__@plt-0x10>:
 80482c0:	ff 35 0c 96 04 08    	pushl  0x804960c
 80482c6:	ff 25 10 96 04 08    	jmp    *0x8049610
 80482cc:	00 00                	add    %al,(%eax)
	...

080482d0 <__gmon_start__@plt>:
 80482d0:	ff 25 14 96 04 08    	jmp    *0x8049614
 80482d6:	68 00 00 00 00       	push   $0x0
 80482db:	e9 e0 ff ff ff       	jmp    80482c0 <_init+0x30>

080482e0 <__libc_start_main@plt>:
 80482e0:	ff 25 18 96 04 08    	jmp    *0x8049618
 80482e6:	68 08 00 00 00       	push   $0x8
 80482eb:	e9 d0 ff ff ff       	jmp    80482c0 <_init+0x30>

080482f0 <puts@plt>:
 80482f0:	ff 25 1c 96 04 08    	jmp    *0x804961c
 80482f6:	68 10 00 00 00       	push   $0x10
 80482fb:	e9 c0 ff ff ff       	jmp    80482c0 <_init+0x30>

Disassembly of section .text:

08048300 <_start>:
 8048300:	31 ed                	xor    %ebp,%ebp
 8048302:	5e                   	pop    %esi
 8048303:	89 e1                	mov    %esp,%ecx
 8048305:	83 e4 f0             	and    $0xfffffff0,%esp
 8048308:	50                   	push   %eax
 8048309:	54                   	push   %esp
 804830a:	52                   	push   %edx
 804830b:	68 e0 83 04 08       	push   $0x80483e0
 8048310:	68 f0 83 04 08       	push   $0x80483f0
 8048315:	51                   	push   %ecx
 8048316:	56                   	push   %esi
 8048317:	68 b4 83 04 08       	push   $0x80483b4
 804831c:	e8 bf ff ff ff       	call   80482e0 <__libc_start_main@plt>
 8048321:	f4                   	hlt    
 8048322:	90                   	nop    
 8048323:	90                   	nop    
 8048324:	90                   	nop    
 8048325:	90                   	nop    
 8048326:	90                   	nop    
 8048327:	90                   	nop    
 8048328:	90                   	nop    
 8048329:	90                   	nop    
 804832a:	90                   	nop    
 804832b:	90                   	nop    
 804832c:	90                   	nop    
 804832d:	90                   	nop    
 804832e:	90                   	nop    
 804832f:	90                   	nop    

08048330 <__do_global_dtors_aux>:
 8048330:	55                   	push   %ebp
 8048331:	89 e5                	mov    %esp,%ebp
 8048333:	53                   	push   %ebx
 8048334:	83 ec 04             	sub    $0x4,%esp
 8048337:	80 3d 24 96 04 08 00 	cmpb   $0x0,0x8049624
 804833e:	75 40                	jne    8048380 <__do_global_dtors_aux+0x50>
 8048340:	8b 15 28 96 04 08    	mov    0x8049628,%edx
 8048346:	b8 34 95 04 08       	mov    $0x8049534,%eax
 804834b:	2d 30 95 04 08       	sub    $0x8049530,%eax
 8048350:	c1 f8 02             	sar    $0x2,%eax
 8048353:	8d 58 ff             	lea    -0x1(%eax),%ebx
 8048356:	39 da                	cmp    %ebx,%edx
 8048358:	73 1f                	jae    8048379 <__do_global_dtors_aux+0x49>
 804835a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048360:	8d 42 01             	lea    0x1(%edx),%eax
 8048363:	a3 28 96 04 08       	mov    %eax,0x8049628
 8048368:	ff 14 85 30 95 04 08 	call   *0x8049530(,%eax,4)
 804836f:	8b 15 28 96 04 08    	mov    0x8049628,%edx
 8048375:	39 da                	cmp    %ebx,%edx
 8048377:	72 e7                	jb     8048360 <__do_global_dtors_aux+0x30>
 8048379:	c6 05 24 96 04 08 01 	movb   $0x1,0x8049624
 8048380:	83 c4 04             	add    $0x4,%esp
 8048383:	5b                   	pop    %ebx
 8048384:	5d                   	pop    %ebp
 8048385:	c3                   	ret    
 8048386:	8d 76 00             	lea    0x0(%esi),%esi
 8048389:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048390 <frame_dummy>:
 8048390:	55                   	push   %ebp
 8048391:	89 e5                	mov    %esp,%ebp
 8048393:	83 ec 08             	sub    $0x8,%esp
 8048396:	a1 38 95 04 08       	mov    0x8049538,%eax
 804839b:	85 c0                	test   %eax,%eax
 804839d:	74 12                	je     80483b1 <frame_dummy+0x21>
 804839f:	b8 00 00 00 00       	mov    $0x0,%eax
 80483a4:	85 c0                	test   %eax,%eax
 80483a6:	74 09                	je     80483b1 <frame_dummy+0x21>
 80483a8:	c7 04 24 38 95 04 08 	movl   $0x8049538,(%esp)
 80483af:	ff d0                	call   *%eax
 80483b1:	c9                   	leave  
 80483b2:	c3                   	ret    
 80483b3:	90                   	nop    

080483b4 <main>:
#include <stdio.h>

int main(int argc, char* argv[])
{
 80483b4:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 80483b8:	83 e4 f0             	and    $0xfffffff0,%esp
 80483bb:	ff 71 fc             	pushl  -0x4(%ecx)
 80483be:	55                   	push   %ebp
 80483bf:	89 e5                	mov    %esp,%ebp
 80483c1:	51                   	push   %ecx
 80483c2:	83 ec 04             	sub    $0x4,%esp
	printf("Hello World!\n");
 80483c5:	c7 04 24 a4 84 04 08 	movl   $0x80484a4,(%esp)
 80483cc:	e8 1f ff ff ff       	call   80482f0 <puts@plt>

	return 0;
 80483d1:	b8 00 00 00 00       	mov    $0x0,%eax
}
 80483d6:	83 c4 04             	add    $0x4,%esp
 80483d9:	59                   	pop    %ecx
 80483da:	5d                   	pop    %ebp
 80483db:	8d 61 fc             	lea    -0x4(%ecx),%esp
 80483de:	c3                   	ret    
 80483df:	90                   	nop    

080483e0 <__libc_csu_fini>:
 80483e0:	55                   	push   %ebp
 80483e1:	89 e5                	mov    %esp,%ebp
 80483e3:	5d                   	pop    %ebp
 80483e4:	c3                   	ret    
 80483e5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 80483e9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080483f0 <__libc_csu_init>:
 80483f0:	55                   	push   %ebp
 80483f1:	89 e5                	mov    %esp,%ebp
 80483f3:	57                   	push   %edi
 80483f4:	56                   	push   %esi
 80483f5:	53                   	push   %ebx
 80483f6:	e8 4f 00 00 00       	call   804844a <__i686.get_pc_thunk.bx>
 80483fb:	81 c3 0d 12 00 00    	add    $0x120d,%ebx
 8048401:	83 ec 0c             	sub    $0xc,%esp
 8048404:	e8 87 fe ff ff       	call   8048290 <_init>
 8048409:	8d bb 20 ff ff ff    	lea    -0xe0(%ebx),%edi
 804840f:	8d 83 20 ff ff ff    	lea    -0xe0(%ebx),%eax
 8048415:	29 c7                	sub    %eax,%edi
 8048417:	c1 ff 02             	sar    $0x2,%edi
 804841a:	85 ff                	test   %edi,%edi
 804841c:	74 24                	je     8048442 <__libc_csu_init+0x52>
 804841e:	31 f6                	xor    %esi,%esi
 8048420:	8b 45 10             	mov    0x10(%ebp),%eax
 8048423:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048427:	8b 45 0c             	mov    0xc(%ebp),%eax
 804842a:	89 44 24 04          	mov    %eax,0x4(%esp)
 804842e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048431:	89 04 24             	mov    %eax,(%esp)
 8048434:	ff 94 b3 20 ff ff ff 	call   *-0xe0(%ebx,%esi,4)
 804843b:	83 c6 01             	add    $0x1,%esi
 804843e:	39 fe                	cmp    %edi,%esi
 8048440:	72 de                	jb     8048420 <__libc_csu_init+0x30>
 8048442:	83 c4 0c             	add    $0xc,%esp
 8048445:	5b                   	pop    %ebx
 8048446:	5e                   	pop    %esi
 8048447:	5f                   	pop    %edi
 8048448:	5d                   	pop    %ebp
 8048449:	c3                   	ret    

0804844a <__i686.get_pc_thunk.bx>:
 804844a:	8b 1c 24             	mov    (%esp),%ebx
 804844d:	c3                   	ret    
 804844e:	90                   	nop    
 804844f:	90                   	nop    

08048450 <__do_global_ctors_aux>:
 8048450:	55                   	push   %ebp
 8048451:	89 e5                	mov    %esp,%ebp
 8048453:	53                   	push   %ebx
 8048454:	83 ec 04             	sub    $0x4,%esp
 8048457:	a1 28 95 04 08       	mov    0x8049528,%eax
 804845c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804845f:	74 13                	je     8048474 <__do_global_ctors_aux+0x24>
 8048461:	bb 28 95 04 08       	mov    $0x8049528,%ebx
 8048466:	66 90                	xchg   %ax,%ax
 8048468:	83 eb 04             	sub    $0x4,%ebx
 804846b:	ff d0                	call   *%eax
 804846d:	8b 03                	mov    (%ebx),%eax
 804846f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048472:	75 f4                	jne    8048468 <__do_global_ctors_aux+0x18>
 8048474:	83 c4 04             	add    $0x4,%esp
 8048477:	5b                   	pop    %ebx
 8048478:	5d                   	pop    %ebp
 8048479:	c3                   	ret    
 804847a:	90                   	nop    
 804847b:	90                   	nop    

Disassembly of section .fini:

0804847c <_fini>:
 804847c:	55                   	push   %ebp
 804847d:	89 e5                	mov    %esp,%ebp
 804847f:	53                   	push   %ebx
 8048480:	83 ec 04             	sub    $0x4,%esp
 8048483:	e8 00 00 00 00       	call   8048488 <_fini+0xc>
 8048488:	5b                   	pop    %ebx
 8048489:	81 c3 80 11 00 00    	add    $0x1180,%ebx
 804848f:	e8 9c fe ff ff       	call   8048330 <__do_global_dtors_aux>
 8048494:	59                   	pop    %ecx
 8048495:	5b                   	pop    %ebx
 8048496:	c9                   	leave  
 8048497:	c3                   	ret    
