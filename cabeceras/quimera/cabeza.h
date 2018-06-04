#ifndef _CABEZA_H
#define _CABEZA_H

#include <defest.h>

typedef struct descr_estructura
{
    unsigned a,b;
}descriptores[64];

extern descriptores tdg,tdi;

#define TDG_NULO        0
#define TDG_CODIGO      1
#define TDG_DATOS       2
#define TDG_TEMP        3

#define TDL_NULO        0
#define TDL_CODIGO      1
#define TDL_DATOS       2

#define fij_descrsis(descr,dir,tipo)            \
    __asm__("movw       $103,(%1)\n\t"          \
            "movw       %w0,2(%1)\n\t"          \
            "rorl       $16,%0\n\t"             \
            "movb       %b0,4(%1)\n\t"          \
            "movb       $"tipo",5(%1)\n\t"      \
            "movb       $0,6(%1)\n\t"           \
            "movb       %h0,7(%1)\n\t"          \
            ::"a"(dir),"d"(descr))

#define fij_set(descr,dir) fij_descrsis((um*)tdg+(descr),(dir),"0x89")
#define fij_tdl(descr,dir) fij_descrsis((um*)tdg+(descr),(dir),"0x82")

#define fij_base(tdl,base)                      \
    __asm__("movw       %w0,2(%1)\n\t"          \
            "rorl       $16,%0\n\t"             \
            "movb       %b0,4(%1)\n\t"          \
            "movb       %h0,7(%1)"              \
            ::"a"(base),"d"(tdl))
#define fij_limite(tdl,limite)                  \
    __asm__("movw       %w0,(%1)\n\t"           \
            "rorl       $16,%0\n\t"             \
            "movb       6(%1),%h0\n\t"          \
            "andb       $0xF0,%h0\n\t"          \
            "orb        %b0,%h0\n\t"            \
            "movb       %h0,6(%1)"              \
            ::"a"(limite),"d"(tdl))

#define obt_base(dir)                           \
    ({                                          \
        register t_lon b;                       \
        __asm__("movb   7(%1),%h0\n\t"          \
                "movb   4(%1),%b0\n\t"          \
                "shll   $16,%0\n\t"             \
                "movw   2(%1),%w0"              \
                :"=a"(b):"d"(dir));b;})


#endif
