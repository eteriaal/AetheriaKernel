OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS
{
    . = 0x100000;

    .multiboot :
    {
        KEEP(*(.multiboot))
    }

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        . = ALIGN(4);
        *(.bss)
        stack_bottom = .;
        . += 8192;
        stack_top = .;
    }
    PROVIDE(stack_space = stack_top);
}
