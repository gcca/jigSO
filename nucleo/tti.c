#include <tipoc.h>

#include <quimera/tti.h>

#define _L_IND(tti,i)   ((tti)->termles.is_l&i)
#define _S_IND(tti,i)   ((tti)->termles.is_s&i)

#define L_ECO(tti)      _L_IND((tti),ECO)

#define S_POST(tti)     _S_IND((tti),SPOST)
#define S_CRAN(tti)     _S_IND((tti),SCRAN)
#define S_CNAR(tti)     _S_IND((tti),SCNAR)
#define S_CANR(tti)     _S_IND((tti),SCANR)
#define S_CAM(tti)      _S_IND((tti),SCAM)

struct tti_estructura tti_tabla[]=
{
    {0,{0,SPOST|SCANR,ECO,VC_C_CC},con_impr,{0,0,""},{0,0,""},{0,0,""}}
};

struct tti_cola *cola_tabla[]=
{
    &tti_tabla[0].c_entrada,&tti_tabla[0].c_salida
};

int tti_escrib(unsigned canal,char *buf,int num)
{
    char c,*b=buf;
    struct tti_estructura *tti;
    static char nr_i=1;

    if(num<0||canal>1) return -1;
    tti=tti_tabla+canal;
    while(num)
	{
	    c=*b;
	    if(S_POST(tti))
		{
		    if(c=='\r'&&S_CRAN(tti))
			c='\n';
		    else if(c=='\n'&&S_CNAR(tti))
			c='\r';
		    if(nr_i&&c=='\n'&&S_CANR(tti))
			{
			    PONC(13,tti->c_salida);
			    nr_i=0;
			    continue;
			}
		    if(S_CAM(tti))
			c=amayus(c);
		}
	    nr_i=1;
	    PONC(c,tti->c_salida);
	    num--;b++;
	}
    tti->impr(tti);
    return b-buf;
}

int tti_leer(unsigned canal,char *buf,int num)
{
    char *b=buf;
    struct tti_estructura *tti;

    if(num<0||canal>1) return -1;
    tti=tti_tabla+canal;
    while(num--)
	{
	    OBTC(tti->c_entrada,*b);
	    b++;
	}
    return b-buf;
}

void tti_interrupcion(int n)
{
    struct tti_estructura *tti=tti_tabla+n;
    char c;

    OBTC(tti->c_entrada,c);
    if(L_ECO(tti))
	{
	    if(c==10)
		PONC(13,tti->c_salida);
	    PONC(c,tti->c_salida);
	    tti->impr(tti);
	}
    PONC(c,tti->c_auxiliar);
}

inline void tti_inic(void)
{
    con_inic();
}
