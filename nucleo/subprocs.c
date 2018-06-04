#include <errn.h>

#include <quimera/procs.h>
#include <quimera/subprocs.h>
#include <quimera/memoria.h>

#define LPILA    384

extern t_lon idp;

int subproc_crear(t_lon func)
{
    int n=hallar_idpn();

    struct tarea_estructura *sp;
    struct subproc_nodo *nodo;

    sp=(struct tarea_estructura*)asigml(LPILA);
    //    *sp=*tarea_act;
    sp->id=idp;
    sp->estado=TAREA_ACTIVA;
    sp->padre=tarea_act->id;
    sp->cabeza=tarea_act->cabeza;
    sp->set=tarea_act->set;
    sp->set.eip=(t_lon)func;
    sp->set.einds=0x202;
    sp->set.esp=sp->set.ebp=(t_lon)sp+LPILA;
    nodo=(struct subproc_nodo*)asigml(8);
    nodo->id=idp;
    nodo->sig=tarea_act->subproc;
    tarea_act->subproc=nodo;
    fij_set(SET(n),&sp->set);
    tarea[n]=sp;
    return idp;
}

