#ifndef _DEFEST_H
#define _DEFEST_H

#ifndef NO_T_LON
#define NO_T_LON
typedef unsigned long t_lon;
#endif

#ifndef NO_T_FUNC
#define NO_T_FUNC
typedef void *t_func;
#endif

#undef NULO
#define NULO ((void*)0)
#undef CERO
#define CERO ((void*)0)
typedef unsigned char um;
typedef unsigned short pal;
typedef unsigned int paldbl;
#ifndef NO_T_MULBIN
#define NO_T_MULBIN
typedef unsigned char __t_8bin;
typedef unsigned short __t_16bin;
typedef unsigned int __t_32bin;
#if defined(__GNUC__)
typedef unsigned long long __t_64bin;
#else
typedef double __t_64bin;
#endif
#endif
#ifndef NO_MEM
#define NO_MEM
#ifndef NO_T_MEM
typedef um *t_mem;
#endif
#endif

#endif
