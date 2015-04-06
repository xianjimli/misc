soft_irq.o:./kernel/soft_irq.c
	$(CC) $(CFLAGS) -o $@ $<
irq.o:./kernel/irq.c
	$(CC) $(CFLAGS) -o $@ $<
trace.o:./kernel/trace.c
	$(CC) $(CFLAGS) -o $@ $<
memory.o:./kernel/memory.c
	$(CC) $(CFLAGS) -o $@ $<
os_init.o:./kernel/os_init.c
	$(CC) $(CFLAGS) -o $@ $<
shell:./app/shell/shell.c
	$(CC) $(CFLAGS) -o $@ $<
syscall.o:./libc/syscall.c
	$(CC) $(CFLAGS) -o $@ $<
stdlib.o:./libc/stdlib.c
	$(CC) $(CFLAGS) -o $@ $<
string.o:./libc/string.c
	$(CC) $(CFLAGS) -o $@ $<
test.o:./libc/test.c
	$(CC) $(CFLAGS) -o $@ $<
stdio.o:./libc/stdio.c
	$(CC) $(CFLAGS) -o $@ $<
ctype.o:./libc/ctype.c
	$(CC) $(CFLAGS) -o $@ $<

C_OBJS=soft_irq.o irq.o trace.o memory.o os_init.o shell syscall.o stdlib.o string.o test.o stdio.o ctype.o 
