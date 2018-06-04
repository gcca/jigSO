#ifndef _TTI_H
#define _TTI_H

#include <termles.h>
#include <defest.h>

#include <quimera/cabeza.h>

#define TTI_BUF_LON     512

struct tti_cola
{
    unsigned cabeza;
    unsigned cola;
    char buf[TTI_BUF_LON];
};

#define INC(n)          ((n)=((n)+1)&(TTI_BUF_LON-1))
#define DEC(n)          ((n)=((n)-1)&(TTI_BUF_LON-1))
#define OBTC(a,c)       (void)({(c)=(a).buf[(a).cola];INC((a).cola);})
#define PONC(c,a)       (void)({(a).buf[(a).cabeza]=(c);INC((a).cabeza);})
#define VACIA(a)        ((a).cabeza==(a).cola)
#define NUMC(a)         (((a).cabeza-(a).cola)&(TTI_BUF_LON-1))
#define ULT(a)          ((a).buf[((a).cabeza-1)&(TTI_BUF_LON-1)])

struct tti_estructura
{
    unsigned char detenido;
    struct termles termles;
    void (*impr)(struct tti_estructura *tti);
    struct tti_cola c_entrada;
    struct tti_cola c_salida;
    struct tti_cola c_auxiliar;
};

#define VC_C_CC "\003\034\177\025\004\0\1\0\021\023\031\0\022\017\027\026\0"

extern struct tti_estructura tti_tabla[];

void con_impr(struct tti_estructura *tti);

int tti_escrib(unsigned canal,char *buf,int num);
int tti_leer(unsigned canal,char *buf,int num);

inline void tti_inic(void)
#ifdef __GNUC__
        __attribute__((always_inline))
#endif
        ;
inline void con_inic(void)
#ifdef __GNUC__
        __attribute__((always_inline))
#endif
        ;

#endif
