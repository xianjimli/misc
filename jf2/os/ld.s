/* a list of files to be linked */

INPUT(start.o arm7.o soft_irq.o irq.o trace.o memory.o os_init.o shell syscall.o stdlib.o string.o test.o stdio.o ctype.o)

OUTPUT("jos.elf")


ENTRY(_start)

MEMORY
{
  SRAM   : o = 0, l = 0x800000
}


SECTIONS
{
  .start :
  {
    __start_start = .;
    *(.start);
    __start_end = .;
  } > SRAM

  .text :
  {
     __text_start = .;
     *(.text)
     *(strings)
     __text_end = .;
  } > SRAM

  .bss :
  {
     __bss_start = .;
     *(.text)
     *(strings)
     __bss_end = .;
  } > SRAM

  .rodata :
  {
     __rodata_start = .;
     *(.rodata)
     __rodata_end = .;
  } > SRAM

  .data :
  {
     __data_start = .;
     *(.data)
     __data_end = .;
  } > SRAM
}
