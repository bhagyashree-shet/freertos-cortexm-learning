ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 4M
    RAM  (rwx) : ORIGIN = 0x21000000, LENGTH = 16M
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    _la_data = LOADADDR(.data);
    .data :
    {
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    .bss :
    {
        _sbss = .;
        __bss_start__ = .;  /* Added for C Library compatibility */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = .;    /* Added for C Library compatibility */
  } > RAM

    /* The 'end' symbol is required by _sbrk (used by malloc) */
    . = ALIGN(4);
    end = .;
    __end__ = .;

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}
