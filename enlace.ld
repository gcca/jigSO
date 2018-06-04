OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)
ENTRY(nucleo)
SECTIONS
{
    .text 0x00000000 :
        {
            *(.text)
        }
    .rdata . :
        {
            *(.rdata)
        }
    .rodata . :
        {
            *(.rodata)
        }
    .data . :
        {
            *(.data)
        }
    .sbss . :
        {
            *(.sbss)
            *(.scommon)
        }
    .bss . :
        {
            _ibss = .;
            *(.bss)
            *(COMMON)
            _fbss = .;
        }
}
