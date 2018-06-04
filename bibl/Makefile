AR	=	ar
AS	=	as
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

libbibl.a:	errn.o salir.o tipoc.o vcs.o
	$(AR) rcs $@ $^

limpiar:
	rm *.o *.a
