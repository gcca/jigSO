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

mem.o:	asigml.o memdin.o memoria.o
	$(LD) -r -o $@ $^

limpiar:
	rm *.o
