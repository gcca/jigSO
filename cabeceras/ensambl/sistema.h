#include <quimera/cabeza.h>

#define li()   __asm__("cli"::)
#define pi()   __asm__("sti"::)

#define ins_puerta(dirp,dir,acc,con)                            \
    __asm__("movw       %w1,%w0\n\t"                            \
	    "movw       %4,%w1\n\t"                             \
	    "movl       %1,%3\n\t"                              \
	    "movl       %0,%2\n\t"                              \
	    ::"a"(0x80000),"d"(dir),                            \
	     "o"(*(char*)(dirp)),"o"(*(4+(char*)(dirp))),       \
	     "i"((short)(((acc)<<12)+((con)<<8))))

#define insp_interrupcion(n,dir)        ins_puerta(&tdi[n],(dir),8,14)
#define insp_trampa(n,dir)              ins_puerta(&tdi[n],(dir),8,15)
#define insp_sistema(n,dir)             ins_puerta(&tdi[n],(dir),14,15)

#define modo_usuario()                          \
    __asm__(""                                  \
            ::)
