CC        = arm-linux-gcc
ASSEMBLER = arm-linux-as
LINKER    = arm-linux-ld -Map jos.map
CONVERT   = arm-linux-strip -O binary -o
CFLAGS    = $(INCLUDES) -mapcs -fomit-frame-pointer -O1 -g -c 
ASFLAGS   = 
INCLUDES  =-I$(srcdir)/kernel/arch/arm7 -I$(srcdir)/kernel -I$(srcdir)/libc \
	-I$(srcdir)/common -I$(top_srcdir)/common -DJOS

OBJS = start.o arm7.o $(C_OBJS)
include c.mk

all: $(OBJS)
	$(LINKER) -o jos.elf $(srcdir)/ld.s
	$(CONVERT)   jos.bin -s jos.elf

start.o: kernel/arch/arm7/start.s
	$(ASSEMBLER) $(ASFLAGS) -o $@ $<

arm7.o: libc/arch/arm7/arm7.s
	$(ASSEMBLER) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(builddir)/*.o $(builddir)/*.elf $(builddir)/*.bin $(builddir)/*.map

SUBDIRS=app kernel common libc
EXTRA_DIST=ld.s
