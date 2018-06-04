#include <quimera/memoria.h>

extern t_lon calcmem(void);

typedef struct _md_nodo md_nodo;
struct _md_nodo
{
    md_nodo *sig;
    t_lon lon;
}
#ifdef __GNUC__
        __attribute__((packed));
#endif
;

extern um _fbss;
extern t_mem nucleo;
static md_nodo *md_di=(md_nodo*)&_fbss;

t_mem md_asignar(t_lon l)
{
    md_nodo *nodo=(md_nodo*)md_di;
    register unsigned lreal=l+sizeof(md_nodo);

    register md_nodo *n;

    while(nodo)
        {
            if(nodo->lon>=lreal)
                {
                    n=(md_nodo*)((unsigned)nodo+lreal);
                    n->lon=nodo->lon-lreal;
                    n->sig=nodo->sig;
                    nodo->lon=0;
                    nodo->sig=n;
                    return (t_mem)(nodo+1);
                }
            nodo=nodo->sig;
        }
    return NULO;
}

void md_liberar(t_mem m)
{
    register md_nodo *nodo=(md_nodo*)((unsigned)m-sizeof(md_nodo));

    nodo->lon=nodo->sig->lon+(unsigned)nodo->sig-(unsigned)m+sizeof(md_nodo);
    nodo->sig=nodo->sig->sig;
}

inline void md_inic(void)
{
    md_di->lon=16384+(MEM_INF-(unsigned)&_fbss);
    md_di->sig=NULO;
    n_impr("Lon de memoria din\240mica: #1:1s MiB\n",md_di->lon);
}
