#include <argest.h>
#include <defest.h>

static char buf[512];

extern int escribvp(char *buf,const char *plantilla,va_lista arg);

int n_impr(const char *plantilla,...)
{
    int i;
    va_lista args;
    va_inic(args,plantilla);
    i=escribvp(buf,plantilla,args);
    va_fin(args);
    __asm__("pushl      %0\n\t"
	    "pushl      $buf\n\t"
	    "pushl      $0\n\t"
	    "call       tti_escrib\n\t"
	    "addl       $8,%%esp\n\t"
	    "popl       %0"
	    ::"r"(i):"esp");
    return i;
}
