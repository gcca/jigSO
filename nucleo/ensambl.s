        .globl  errdiv,excepdep,intnenm,ptorup,desb,chlim,codnval,coprocndisp
        .globl  fallodbl,reserv4coproc3,setnval,segmndisp,exceppila,proteccgen
        .globl  fallopag,errupf,chalin,reservado

errdiv:
	pushl   $fr_errdiv
	jmp     no_err
excepdep:
	pushl   $fr_excepdep
	jmp     no_err
intnenm:
	pushl   $fr_intnenm
	jmp     no_err
ptorup:
	pushl   $fr_ptorup
	jmp     no_err
desb:
	pushl   $fr_desb
	jmp     no_err
chlim:
	pushl   $fr_chlim
	jmp     no_err
codnval:
	pushl   $fr_codnval
	jmp     no_err
coprocndisp:
	pushl   $fr_coprocndisp
	jmp     no_err
fallodbl:
	pushl   $fr_fallodbl
	jmp     no_err
reserv4coproc3:
	pushl   $fr_reserv4coproc3
	jmp     no_err
setnval:
	pushl   $fr_setnval
	jmp     no_err
segmndisp:
	pushl   $fr_segmndisp
	jmp     no_err
exceppila:
	pushl   $fr_exceppila
	jmp     no_err
proteccgen:
	pushl   $fr_proteccgen
no_err:
	pushal
	xorl    %eax,%eax
	xchgl   %eax,32(%esp)
	pushl   %esp
	call    *%eax
	addl    $4,%esp
	popal
	addl    $4,%esp
        testl   $0100,8(%esp)
        jz      1f
        addl    $4,(%esp)
1:      iret

fallopag:
	pushl   $fr_fallopag
	jmp     no_err
errupf:
	pushl   $fr_errupf
	jmp     no_err
chalin:
	pushl   $fr_chalin
	jmp     no_err
reservado:
	pushl   $fr_reservado
	jmp     no_err
