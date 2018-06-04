num_llamadas = 4

        .globl  sis_llamada,sis_bifurcar

sis_llamada:
        cmpl    $num_llamadas-1,%eax
        ja      sis_llamada_err
        push    %ds
        push    %es
        push    %fs
        pushl   %edx
        pushl   %ecx
        pushl   %ebx
        movl    $0x10,%edx
        movw    %dx,%ds
        movw    %dx,%es
        movl    $0x14,%edx
        movw    %dx,%fs
        call    *sis_tabla(,%eax,4)
        popl    %ebx
        popl    %ecx
        popl    %edx
        pop     %fs
        pop     %es
        pop     %ds
        iret
sis_llamada_err:
        movl    $-1,%eax
        iret

        .globl cron_interrupcion
cron_interrupcion:
        pushal
        push    %ds
        push    %es
        movl    $0x10,%eax
        movw    %ax,%ds
        movw    %ax,%es
        movb    $0x20,%al
        outb    %al,$0x20
        call    proceso
        pop     %es
        pop     %ds
        popal
        iret

sis_bifurcar:/*
        movl    %esp,%eax
        addl    $40,%eax
        pushl   36(%esp)
        pushl   $ho
        call    n_impr
        addl    $8,%esp
        ret*/
        movl    %esp,%eax
        addl    $40,%eax
        pushl   %gs
        pushl   %ss
        pushl   %esi
        pushl   %edi
        pushl   %eax
        pushl   %ebp
        call    copproc
        addl    $24,%esp
        ret

/*ho:
        .string "BIF #p\n"*/
