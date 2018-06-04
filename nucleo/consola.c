#include <defest.h>
#include <vcs.h>

#include <quimera/cabeza.h>
#include <quimera/tti.h>

#include <ensambl/es.h>
#include <ensambl/sistema.h>

extern void tecl_interrupcion(void);

#define PANTALLA_INIC   0xb8000
#define PANTALLA_FIN    0xc0000
#define LINEAS      25
#define COLUMNAS    80

#ifdef __GNUC__
inline void con_inic(void) __attribute__((always_inline));
void con_impr(struct tti_estructura *tti) __attribute__((nonnull));
#endif

static long origen=PANTALLA_INIC;
static long pos=PANTALLA_INIC;
static long x=-1,y=-1;
static long lins=LINEAS,cols=COLUMNAS;
static __t_8bin atrib=0x07;
static long cabeza=0,fondo=LINEAS;

#define pantalla_frente(c)  atrib=((atrib&0xF0)|(c))
#define pantalla_fondo(c)   atrib=((atrib&0x0F)|(c<<4))

#define NUMCONS 9

static unsigned ncon=0;
static struct con_datos
{
    long origen;
    long pos;
    long x,y;
    long lins,cols;
    __t_8bin atrib;
}con[]=
{
    {0},
    {0xB8FA0,0xB8FA0,0,0,25,80,0x8B},
    {0xB9F40,0xB9F40,0,0,25,80,0x70},
    {0xBAEE0,0xBAEE0,0,0,25,80,0x1B},
    {0xBBE80,0xBBE80,0,0,25,80,0x8E},
    {0xBCE20,0xBCE20,0,0,25,80,0x5F},
    {0xBDDC0,0xBDDC0,0,0,25,80,0x49},
    {0xBED60,0xBED60,0,0,25,80,0x3A}
};

void con_selec(unsigned n)
{
    if(n>NUMCONS-1) return;
    mem_cop(&origen,&con[ncon],25);
    ncon=n;
    mem_cop(&con[ncon],&origen,25);
    li();
    salb(12,0x3D4);
    salb((origen-PANTALLA_INIC)>>9,0x3D5);
    salb(13,0x3D4);
    salb((origen-PANTALLA_INIC)>>1,0x3D5);
    pi();
}

void con_limpiar(void)
{
    register short *memvideo=(short*)origen;

    register int i=lins*cols;
    while(i--)
	*memvideo++=atrib<<8;
}

static inline void fijarxy(unsigned int x_,unsigned int y_)
{
    if(x_>=cols||y_>=lins)
	return;
    x=x_;
    y=y_;
    pos=origen+((y*cols+x)<<1);
}

static inline void fijarcursor(void)
{
    li();
    salb(14,0x3D4);
    salb((pos-PANTALLA_INIC)>>9,0x3D5);
    salb(15,0x3D4);
    salb((pos-PANTALLA_INIC)>>1,0x3D5);
    pi();
}

void con_desplaz(void)
{
    __asm__("std\n\t"
	    "rep\n\t"
	    "movsl\n\t"
	    "addl $2,%2\n\t"
	    "movl $80,%1\n\t"
	    "rep\n\t"
	    "stosw"
	    ::"a"(0x0720),"c"((fondo-cabeza-1)*COLUMNAS>>1),
	     "D"(PANTALLA_INIC+(COLUMNAS<<1)*fondo-4),
	     "S"(PANTALLA_INIC+(COLUMNAS<<1)*(fondo-1)-4)
	    );


}

static inline void fijarcur_origen(void)
{
    li();
    salb(12,0x3d4);
    salb(0,0x3d5);
    salb(13,0x3d4);
    salb(0,0x3d5);
    pi();
}

void con_desplarr(void) {/*
			   __asm__("cld\n\t"
			   "rep\n\t"
			   "movsb\n\t"
			   ::"c"((lins-1)*cols),"D"(PANTALLA_INIC),
			   "S"(PANTALLA_INIC+(cols<<1)));*/ }

unsigned long _x,_y;

inline void guard_cur()
{
    _x=x;
    _y=y;
}
/*
void con_ingresccs(__8tbin c)
{
    switch(c)
	{
	case '\n':
	    fijarxy(0,y+1);
	    goto fret;
	case 127:
	    if(x)
		{
		    fijarxy(x-1,y);
		    con_ingresc(' ');
		    fijarxy(x-1,y);
		}
	    goto fret;
	case '\t':
	    pos+=16;
	    x+=7;
	    break;
	default:
	    __asm__("stosw"::"a"(c|atrib<<8),"D"(pos));
	    pos+=2;
	}
    if(++x>cols)
	{
	    x=0;
	    if((y+=1)==24)
		{
		    //   con_desplarr();
		    fijarxy(x,24);
		}
	}
 fret:
    fijarcursor();
}
*/
void con_impr(struct tti_estructura *tti)
{
    char c;
    int num;

    num=NUMC(tti->c_salida);
    while(num--)
	{
	    OBTC(tti->c_salida,c);
	    switch(c)
		{
		case '\n':
		    fijarxy(x,y+1);
		    ///goto fret;
		    x-=1;
		    pos-=2;
		    break;
		case '\r':
		    fijarxy(0,y);
		    ///goto fret;
		    break;
		case 127:
		    if(x)
			{
			    fijarxy(x-1,y);

			    __asm__("movb atrib,%%ah\n\t"
				    "movw %%ax,%1\n\t"
				    ::"a"(' '),"m"(*(short*)pos));

			    //fijarxy(x-1,y);
			}
		    //      goto fret;
		    break;
		case '\t':
		    pos+=16;
		    x+=7;
		    break;
		default:
		    __asm__("movb atrib,%h0\n\t"
			    "movw %w0,%1\n\t"
			    ::"a"(c),"m"(*(short*)pos));
		    pos+=2;
		}
	    if(++x>80)
                {
                    ++y;
                    x=0;
                }
	    //fret:

	    //pos+=2;
	}
    fijarcursor();
}

inline void con_inic(void)
{
    fijarxy(0,8);
    fijarcursor();
    pantalla_frente(14);
    pantalla_fondo(8);
    char *i=(char*)PANTALLA_INIC+1;
    while(i<=(char*)PANTALLA_FIN)
	{
	    *i=atrib;
	    i+=2;
	}
    insp_interrupcion(0x21,&tecl_interrupcion);
    salb(entb(0x21)&~2,0x21);
}
