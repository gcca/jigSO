/*
 *		vcs.h
 *	Funciones para el manejo de caracteres.
 *	Gonzales Castillo, Cristhian Alberto
 */

#ifndef _VCS_H
#define _VCS_H

#ifndef CERO
#define CERO	((void*)0)
#endif

#ifndef NO_T_LON
#define NO_T_LON
typedef unsigned int t_lon;
#endif

extern inline t_lon vcs_lon(const char *c)
{
    register int _r __asm__("cx");
    __asm__("repne\n\t"
	    "scasb\n\t"
	    "notl %0\n\t"
	    "decl %0"
	    :"=c"(_r):"D"(c),"a"(0),"0"(-1));
    return _r;
}

extern inline char *vcs_cop(const char *orig,char *dest)
{
    __asm__("1:\tlodsb\n\t"
	    "stosb\n\t"
	    "testb %%al,%%al\n\t"
	    "jne 1b"
	    ::"S"(orig),"D"(dest));
    return dest;
}

extern inline int vcs_comp(const char *vcs1,const char *vcs2)
{
    register int _r __asm__("eax");
    __asm__("1:\tlodsb\n\t"
	    "scasb\n\t"
	    "jne 2f\n\t"
	    "testb %%al,%%al\n\t"
	    "jne 1b\n\t"
	    "2:\tmovb -1(%%edi),%%dl\n\t"
	    "subl %%edx,%%eax\n\t"
	    :"=a"(_r):"S"(vcs1),"D"(vcs2),"0"(0),"d"(0));
    return _r;
}

extern inline char *vcs_concat(char *vcs1,const char *vcs2)
{
    __asm__("repne\n\t"
	    "scasb\n\t"
	    "1:\tlodsb\n\t"
	    "stosb\n\t"
	    "testb %%al,%%al\n\t"
	    "jne 1b"
	    ::"S"(vcs1),"D"(vcs2),"a"(0),"c"(-1));
    return vcs1;
}

extern inline void *mem_cop(const void *orig,void *dest,t_lon n)
{
    __asm__("rep\n\t"
	    "movsb"
	    ::"c"(n),"S"(orig),"D"(dest));
    return dest;
}

extern inline void *mem_pon(void *m,char c,t_lon n)
{
    __asm__("rep\n\t"
	    "stosb"
	    ::"a"(c),"D"(m),"c"(n));
    return m;
}

extern inline int mem_comp(const void *m1,const void *m2,t_lon n)
{
    register int _r __asm__("ax");
    __asm__("repe\n\t"
	    "cmpsb\n\t"
	    "je 1f\n\t"
	    "movb -1(%%esi),%%al\n\t"
	    "movb -1(%%edi),%%dl\n\t"
	    "subl %%edx,%%eax\n\t"
	    "1:"
	    :"=a"(_r):"0"(0),"S"(m1),"D"(m2),"c"(n),"d"(0));
    return _r;
}

#endif
