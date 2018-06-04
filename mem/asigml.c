#include <ensambl/reg.h>

#include <quimera/memoria.h>
#include <quimera/procs.h>

struct ml_nodo
{
    struct ml_nodo *sig;
    t_lon lon;
}
#ifdef __GNUC__
        __attribute__((packed));
#endif
;

t_mem asigml(t_lon l)
{
    register struct ml_nodo *nodo=(struct ml_nodo*)tarea_act->cabeza;
    register t_lon lon=l+sizeof(struct ml_nodo);

    register struct ml_nodo *n;

    while(nodo)
        {
            if(!nodo->sig) nodo->lon=reg("esp")-(t_lon)(nodo+1);
            if(nodo->lon>=lon)
                {
                    n=(struct ml_nodo*)((t_lon)nodo+lon);
                    n->lon=nodo->lon-lon;
                    n->sig=nodo->sig;
                    nodo->lon=0;
                    nodo->sig=n;
                    return (t_mem)(nodo+1);
                }
            nodo=nodo->sig;
        }
    return NULO;
}

/*
void libml(t_mem m)
{
    register struct ml_nodo *nodo=m-sizeof(struct ml_nodo);

    nodo->lon=nodo->sig->lon+(unsigned)nodo->sig-(unsigned)m+
            sizeof(struct ml_nodo);
    nodo->sig=nodo->sig->sig;
}
*/
