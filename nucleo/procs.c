#include <defest.h>

#include <quimera/procs.h>

#include <ensambl/es.h>
#include <ensambl/sistema.h>

extern t_mem _fbss;
#define ML_TINI (t_mem)&_fbss

extern void cron_interrupcion(void);

struct tarea_estructura inic=
{
    0,0,0,ML_TINI,0,
    {{0,0},{0x0000FFFF,0x00C09A00},{0x0000FFFF,0x00C09200}},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x14,0xC,0x14,0x14,0x14,0x14,TDL(0),0}
};

struct tarea_estructura *tarea[TAREA_NUM]={&inic,};
struct tarea_estructura *tarea_act=&inic;
um tarea_i __attribute__((packed))=0;

void proceso(void)
{
    do
        {
            if(++tarea_i==TAREA_NUM) tarea_i=0;
            if(!tarea[tarea_i]) continue;
        }
    while(tarea[tarea_i]->estado!=TAREA_ACTIVA);
    {
        struct {long a,b;} set;
        __asm__("cmpl   tarea_act,%0\n\t"
                "je     1f\n\t"
                "movl   %0,tarea_act\n\t"
                "movw   %w1,%w3\n\t"
                "ljmp   *%2\n\t"
                "1:"
                ::"a"(tarea[tarea_i]),"d"SET(tarea_i),
                 "m"(*&set.a),"m"(*&set.b)
                );
    }
}

inline void proc_inic(void)
{
    /*
    int i;
    for(i=0;i<TAREA_NUM;++i)
        {
            n_impr("#1:1x,, ",tarea[i]);
        }
    for(;;);
*/
    register int i;
    struct descr_estructura *d;
    fij_tdl(TDL(0),&tarea_act->tdl);
    fij_set(SET(0),&tarea_act->set);
    *(t_lon*)ML_TINI=0;
    *(t_lon*)(ML_TINI+4)=0;
    d=tdg+2+PTDL;
    for(i=1;i<TAREA_NUM;++i)
        {
            tarea[i]=NULO;
            d->a=d->b=0;
            ++d;
            d->a=d->b=0;
            ++d;
        }
    __asm__("lldt %w0"::"a"TDL(0));
    __asm__("ltr %w0"::"a"SET(0));
    salb(0x36,0x43);
    salb(0x9B,0x40);
    salb(0x2E9B>>8,0x40);
    insp_interrupcion(0x20,&cron_interrupcion);
    salb(entb(0x21)&~1,0x21);
}
