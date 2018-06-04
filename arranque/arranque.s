        .data
gdt_lon:
        .word   24
gdt_dir:
        .int    0x7908
        .align  2
        .word   0
        .align  8
tabla_gdt:
        .quad   0
        .quad   0x00CF9A000000FFFF
        .quad   0x00CF92000000FFFF
        .org    512
        .text
        .code16
        .globl  arranque
arranque:
        cli
        xorw    %ax,%ax
        movw    %ax,%ss
        movw    $0x7C00,%sp
        sti
        movw    $0x7C0,%ax
        movw    %ax,%ds
        movw    %ax,%es
        movw    $3,%ax
        int     $0x10
        movw    $mje_inicio,%si
        call    impr
        testb   %dl,%dl
        jz      dded
        cmpb    $0x80,%dl
        jz      ddedd
        jmp     ddena
dded:   movw    $0,de
        movw    $mje_cd,%si
        jmp     imprdde
ddedd:  movw    $0x80,de
        movw    $mje_cdd,%si
imprdde:call    impr
ddena:  movw    $mje_i386,%si
        call    impr
        pushfw
        testb   %ah,%ah
        pushw   %ax
        popf
        pushf
        popw    %ax
        andb    $0xF0,%ah
        cmpb    $0xF0,%ah
        je      noi386
        movb    $0xF0,%ah
        pushw   %ax
        popf
        pushf
        popw    %ax
        andb    $0xF0,%ah
        jz      noi386
        popf
        movw    $mje_ei386,%si
        call    impr
        movw    $mje_tablas,%si
        call    impr
lsect:  movb    de,%dl
        xorw    %ax,%ax
        int     $0x13
        jc      lsect
ltabls: movw    $0x790,%ax
        movw    %ax,%es
        xorw    %bx,%bx
        movb    $2,%ah
        movb    $1,%al
        movw    $2,%cx
        movw    de,%dx
        int     $0x13
        jc      ltabls
lnucl:  xorw    %ax,%ax
        movw    %ax,%es
        xorw    %bx,%bx
        movb    $2,%ah
        movb    $60,%al
        movw    $3,%cx
        movw    de,%dx
        int     $0x13
        jc      lnucl
apagd:  movl    $0x3F2,%edx
        movb    $0xC,%al
        outb    %al,%dx
a20:    cli
1:      inb     $0x64,%al
        andb    $2,%al
        jnz     1b
        movb    $0xD1,%al
        outb    %al,$0x64
1:      inb     $0x64,%al
        andb    $2,%al
        jnz     1b
        movb    $0xDF,%al
        outb    %al,$0x60
1:      inb     $0x64,%al
        andb    $2,%al
        jnz     1b
        movw    $0x790,%ax
        movw    %ax,%ds
        lgdt    %ds:0
        movl    %cr0,%eax
        orl     $1,%eax
        movl    %eax,%cr0
        .byte   0xEA
        .word   0,8
noi386: movw    $mje_noi386,%si
        call    impr
        xorb    %ah,%ah
        int     $0x16
        .byte   0xEA
        .word   0x0000
        .word   0xFFFF
de:
        .word   0
mje_inicio:
        .ascii  "Belerofonte - v0.01\n\r"
mje_autor:
        //.ascii  "(C) ]GCCA[ Gonzales Castillo, Cristhian Alberto - Marzo 2008"
        .ascii  "(C) ]GCCA[ - Agosto 2008"
mje_carga:
        .asciz  "\n\rDe "
mje_i386:
        .asciz  "\r\nEs i386+: "
mje_ei386:
        .byte   83,161,0
mje_noi386:
        .asciz  "NO"
mje_cd:
        .asciz  "disquetera"
mje_cdd:
        .asciz  "disco duro"
mje_tablas:
        .ascii  "\r\nCargando tablas y"
mje_nucleo:
        .byte   32,'n',163,'c','l','e','o'
mje_apad:
        .ascii  "\n\rApagando disquetera"
mje_a20:
        .asciz  "\n\rActivando A20"
impr:
        movb    $0x0E,%ah
        movw    $0x7,%bx
imprbucl:
        lodsb
        testb   %al,%al
        jz      imprf
        int     $0x10
        jmp     imprbucl
imprf:
        ret
        .org    510
        .word   0xAA55
