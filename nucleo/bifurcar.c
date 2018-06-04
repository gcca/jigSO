#include <errn.h>

#include <quimera/procs.h>

t_lon idp=0;

int hallar_idpn(void)
{
    register int i;

 hallar:
    ++idp;
    for(i=1;i<TAREA_NUM;++i)
        if(!tarea[i]&&tarea[i]->id==idp) goto hallar;
    for(i=1;i<TAREA_NUM;++i)
        if(!tarea[i])
            return i;
    return -EREP;
}
/*
int copproc(long ebp,long esp,long edi,long esi,long ss,long gs,long pret1,
            long ebx,long ecx,long edx,long fs,long es,long ds,long eip,
            long cs,long einds)
{
    //n_impr("#1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X  #1:1X\n",ebp,esp,edi,esi,ss,gs,pret1,ebx,ecx,edx,fs,es,ds,eip,cs,einds,tn,idp);
    //return 23;
    int n;

    struct tarea_estructura *p;
    t_mem pag;

    n=hallar_idpn();

    p=(struct tarea_estructura*)md_asignar(sizeof(struct tarea_estructura));
    *p=*tarea_act;
    p->id=idp;
    p->estado=TAREA_ACTIVA;
    p->set.enlace_prev=0;
    p->set.eax=0;
    p->set.ebx=ebx;
    p->set.ecx=ecx;
    p->set.edx=edx;
    p->set.esi=esi;
    p->set.edi=edi;
    p->set.esp=esp;
    p->set.ebp=ebp;
    p->set.eip=eip;
    p->set.einds=einds;
    p->set.cs=cs;
    p->set.ds=ds;
    p->set.es=es;
    p->set.fs=fs;
    p->set.gs=gs;
    p->set.selectdl=TDL(n);

    pag=mem_obtpagt(PAGT4);
    mem_coppagt(0,pag,4);

    //fij_base(&p->tdl[1],pag);
    //fij_base(&p->tdl[2],pag);

    fij_set(SET(n),&p->set);
    fij_tdl(TDL(n),&p->tdl);
    n_impr("\n#1:1X#1:1X\n    #1:1X",p->tdl[2].b,p->tdl[2].a,pag);
    tarea[n]=p;
    return idp;
}*/
