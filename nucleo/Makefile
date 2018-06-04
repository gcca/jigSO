AS	=	as
LD	=	ld
CC	=	gcc
ARGC	=	-fstrength-reduce -fomit-frame-pointer \
	-finline-functions -fno-builtin  -nostdinc -I../cabeceras
CPP	=	gcc -E -nostdinc -I../cabeceras

.c.s:
	$(CC) $(ARGC) -S -o $*.s $<
.s.o:
	$(AS) -o $*.o $<
.c.o:
	$(CC) $(ARGC) -c -o $*.o $<

_nucleo:	nucleo.o cabeza.o

nucleo.o:	 bifurcar.o consola.o ensambl.o escribvp.o inicio.o interpr.o \
n_impr.o procs.o teclado.o trampas.o tti.o sis.o sis_llamada.o subprocs.o
	$(LD) -r -o $@ $^
cabeza.o:	cabeza.s

limpiar:
	rm *.o
