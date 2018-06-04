#include <quimera/sis.h>
#include <quimera/procs.h>
#include <quimera/memoria.h>

#include <ensambl/sistema.h>

extern inline void trampas_inic(void);

extern int sis_llamada(void);

int sis_salir(int coderr)
{
    return sis_matar(tarea_act->id);
}

int sis_matar(long idp)
{
    int i;

    for(i=0;i<TAREA_NUM;++i)
        if(idp==tarea[i]->id) break;
    if(i==TAREA_NUM) return -1;
    while(tarea[i]->subproc)
        {
            sis_matar(tarea[i]->subproc->id);
            tarea[i]->subproc=tarea[i]->subproc->sig;
        }
    tarea[i]=NULO;
    proceso();
    return -1;
}

inline void sis_inic(void)
{
    trampas_inic();
    insp_sistema(0x30,&sis_llamada);
}
