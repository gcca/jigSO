#ifndef _PROCS_H
#define _PROCS_H

#define TAREA_NUM       64

#define TAREA_1         tarea[0]
#define TAREA_ULT       tarea[TAREA_NUM-1]

#define TAREA_ACTIVA    0
#define TAREA_BLOQUEADA 1
#define TAREA_DETENIDA  2
#define TAREA_ZOMBI     3

#include <quimera/cabeza.h>
#include <quimera/memoria.h>
#include <quimera/subprocs.h>

#define PTDL    4
#define PSET    5
#define TDL(a)  ((((t_lon)(a))<<4)+(PTDL<<3))
#define SET(a)  ((((t_lon)(a))<<4)+(PSET<<3))

#ifdef __GNUC__
struct set_estructura __attribute__((packed));
struct tarea_estructura __attribute__((packed));
#endif

struct set_estructura
{
    unsigned enlace_prev;
    unsigned esp0;
    unsigned ss0;
    unsigned esp1;
    unsigned ss1;
    unsigned esp2;
    unsigned ss2;
    unsigned cr3;
    unsigned eip;
    unsigned einds;
    unsigned eax,ecx,edx,ebx;
    unsigned esp;
    unsigned ebp;
    unsigned esi;
    unsigned edi;
    long es;
    long cs;
    long ss;
    long ds;
    long fs;
    long gs;
    long selectdl;
    long dbmapaes;
};

struct tarea_estructura
{
    t_lon id;
    um estado;
    t_lon padre;
    t_mem cabeza;
    struct subproc_nodo *subproc;
    struct descr_estructura tdl[3];
    struct set_estructura set;
};

extern struct tarea_estructura *tarea[TAREA_NUM];
extern um tarea_i;
extern struct tarea_estructura *tarea_act;

extern void proceso(void);

#ifdef __GNUC__
inline void proc_inic(void) __attribute__((always_inline));
#else
inline void proc_inic(void);
#endif

#endif
