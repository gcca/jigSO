AS	=	as
LD	=	ld
ARGLD	=	--oformat binary -Tdata 0x200 -Ttext 0 -A i386

.s.o:
	$(AS) -o $*.o $<

OBJS	=	arranque.o

all:	$(OBJS)
	$(LD) $(ARGLD) -e arranque -o arranque.bin $(OBJS)

limpiar:
	rm *.o *.bin
