cabeza  =       0
cola    =       4
buf     =       8

lon     =       512

.globl  tecl_interrupcion
tecl_interrupcion:
        pushl   %eax
        pushl   %ebx
        pushl   %ecx
        xorl    %eax,%eax
        inb     $0x60,%al
        testb   $0x80,%al
        jne     1f
        movl    cola_tabla,%ebx
        movl    cabeza(%ebx),%ecx
        movl    $tecl_mapa,%esi
        addl    %eax,%esi
        lodsb
        movb    %al,buf(%ebx,%ecx)
        incl    %ecx
        andl    $lon-1,%ecx
        cmpl    cola(%ebx),%ecx
        je      1f
        movl    %ecx,cabeza(%ebx)
        pushl   $0
        call    tti_interrupcion
        addl    $4,%esp
1:      movb    $0x20,%al
        outb    %al,$0x20
        popl    %ecx
        popl    %ebx
        popl    %eax
        iret

tecl_mapa:
        .byte   0,27
        .ascii  "1234567890-="
        .byte   127,9
        .ascii  "qwertyuiop[]"
        .byte   10,0
        .ascii  "asdfghjkl;'"
        .byte   0,0,'\''
        .ascii  "zxcvbnm,./"
        .byte   0,0,0,' '

/*
pusha
movw    $24,%ax
movw    %ax,%fs
movl    $8,%edi
movb    $0xE2,%fs:1(%edi)
movb    $0xE2,%fs:-1(%edi)
movb    $0xE2,%fs:-3(%edi)
xorb    %ah,%ah
inb     $0x60,%al
movl    $0xA,%edx
divb    %dl
addb    $48,%ah
movb    %ah,%fs:(%edi)
xorb    %ah,%ah
divb    %dl
addb    $48,%ah
movb    %ah,%fs:-2(%edi)
xorb    %ah,%ah
divb    %dl
addb    $48,%ah
movb    %ah,%fs:-4(%edi)
popa
*/
