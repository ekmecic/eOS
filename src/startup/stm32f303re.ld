ENTRY(eos_startup)

MEMORY
{
  flash	(rx) : ORIGIN = 0x08000000, LENGTH = 512K
  sram (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

__stack_end = ORIGIN(sram) + LENGTH(sram);

SECTIONS {

  . = ORIGIN(flash);

  .stack_top :
  {
    KEEP(*(.stack_top))
  } > flash

  .vectors :
  {
    KEEP(*(.vectors))
    . = ALIGN(4);
    KEEP(*(.isr))
  } > flash

  .startup :
  {
    . = ALIGN(4);
    KEEP(*(.startup))
  } > flash

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
  }

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata.*)
  }

  .datai_begin :
  {
    . = ALIGN(4);
    __datai_begin = .;
  } > flash

  .data :
  {
    . = ALIGN(4);
    __data_begin = .;
    *(.data)
    *(.data.*)
    . = ALIGN(4);
    __data_end = .;
  } > sram AT > flash

  .datai_end :
  {
    . = ALIGN(4);
    __datai_end = .;
  } > flash

  .bss :
  {
     . = ALIGN(4);
     __bss_begin = .;
     *(.bss)
     *(.bss*)
     . = ALIGN(4);
     __bss_end = .;
  } > sram
}
