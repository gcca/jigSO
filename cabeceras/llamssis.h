#ifndef _LLAMSSIS_H
#define _LLAMSSIS_H

extern int errn;

#define __LLS_bifurcar  0
#define __LLS_salir     1
#define __LLS_matar     2
#define __LLS_crearsubp 3
#define __LLS_escribir  4
#define __LLS_leer      5

#define __lls0params(t,v)                       \
    t v(void)                                   \
    {                                           \
        t r;                                    \
        __asm__ volatile("int $0x30"            \
                         :"=a"(r)               \
                         :"0"(__LLS_##v));      \
        if(r>=0) return r;                      \
        errn=-r;                                \
        return -1;                              \
    }

#define __lls1param(t,v,t1,v1)                          \
    t v(t1 v1)                                          \
    {                                                   \
        t r;                                            \
        __asm__ volatile("int $0x30"                    \
                         :"=a"(r)                       \
                         :"0"(__LLS_##v),"b"(v1));      \
        if(r>=0) return r;                              \
        errn=-r;                                        \
        return -1;                                      \
    }

#define __lls2params(t,v,t1,v1,t2,v2)                           \
    t v(t1 v1,t2 v2)                                            \
    {                                                           \
        t r;                                                    \
        __asm__ volatile("int $0x30"                            \
                         :"=a"(r)                               \
                         :"0"(__LLS_##v),"b"(v1),"c"(v2));      \
        if(r>=0) return r;                                      \
        errn=-r;                                                \
        return -1;                                              \
    }

#define __lls3params(t,v,t1,v1,t2,v2,t3,v3)                             \
    t v(t1 v1,t2 v2)                                                    \
    {                                                                   \
        t r;                                                            \
        __asm__ volatile("int $0x30"                                    \
                         :"=a"(r)                                       \
                         :"0"(__LLS_##v),"b"(v1),"c"(v2),"d"(v3));      \
        if(r>=0) return r;                                              \
        errn=-r;                                                        \
        return -1;                                                      \
    }

int salir(int estado);

#endif
