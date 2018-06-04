        .text
        .code32
        .globl  nucleo,tdg,tdi
nucleo:
        movw    $0x10,%ax
        movw    %ax,%ds
        movw    %ax,%es
        movw    %ax,%fs
        movw    %ax,%gs
        movw    %ax,%ss
        movl    $tdg_descr,%ebp
        movl    $tdg_descr,%esp
/*        call    _tdg
        movw    $0x10,%ax
        movw    %ax,%ds
        movw    %ax,%es
        movw    %ax,%fs
        movw    %ax,%gs
        movw    %ax,%ss*/
        lidt    %ds:tdi_descr
        lgdt    %ds:tdg_descr
        movb    $0x11,%al
        outb    %al,$0x20
        outb    %al,$0xA0
        movb    $0x20,%al
        outb    %al,$0x21
        movb    $0x28,%al
        outb    %al,$0xA1
        movb    $0x04,%al
        outb    %al,$0x21
        movb    $0x02,%al
        outb    %al,$0xA1
        movb    $0x01,%al
        outb    %al,$0x21
        outb    %al,$0xA1
        movb    $0xFF,%al
        outb    %al,$0x21
        movb    $0xFF,%al
        outb    %al,$0xA1
/*      	xorl    %eax,%eax
1:      incl    %eax
        movl    %eax,0x000000
        cmpl    %eax,0x100000
        je      1b
        movl    %cr0,%eax
        andl    $0x00010011,%eax
        orl     $2,%eax
        testl   $16,%eax
        jne     1f
        xorl    $6,%eax
1:      movl    %eax,%cr0
        pushfl
        popl    %eax
        orl     $0x4000,%eax
        pushl   %eax
        popfl*/
        cld
        sti
        jmp     inicio
/*_tdg:
        lgdt    %ds:tdg_descr
        ret*/
        .org    0x300
tdg_descr:
        .word   132*8
        .long   tdg
        .word   0
        .align  2
tdi_descr:
        .word   0x31*8
        .long   tdi
        .word   0
        .align  2
tdg:    .quad   0
        .quad   0x00CF9A000000FFFF
        .quad   0x00CF92000000FFFF
        .quad   0
        .fill   128,8,0
        .align  8
tdi:    .fill   0x31,8,0
