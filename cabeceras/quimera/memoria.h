#ifndef _MEMORIA_H
#define _MEMORIA_H

#include <defest.h>

#define MEM_INF 0x100000
#define PAG_LON (1<<12)

enum t_pag {PAGT1=1,PAGT2,PAGT4=4};

#define obt_pag()      mem_obtpagt(1)
#define lib_pag(dir)   mem_libpagt((dir),1)

#ifdef __GNUC__
t_mem asigml(t_lon lon);
void libml(t_mem mem) __attribute__((nonnull));

t_mem md_asignar(t_lon lon);
void md_liberar(t_mem mem) __attribute__((nonnull));

t_mem mem_obtpagt(enum t_pag tipo);
void mem_libpagt(unsigned long dir,enum t_pag tipo);

inline void mem_inic(void) __attribute__((always_inline));
#else
t_mem asigml(t_lon lon);
void libml(t_mem mem);

t_mem md_asignar(t_lon lon);
void md_liberar(t_mem mem);

t_mem mem_obtpagt(enum t_pag tipo);
void mem_libpagt(unsigned long dir,enum t_pag tipo);

inline void mem_inic(void);
#endif

#endif
