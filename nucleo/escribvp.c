#include <argest.h>
#include <tipoc.h>
#include <vcs.h>

#define IZQ     1
#define CEROS   2
#define SIGNO   4
#define MINUS   8
#define OXNUM   16
#define CRUZ    32
#define ESPACIO 64

#define _div(n,base)                            \
    ({                                          \
        long __ret;                             \
        __asm__("divl %4":"=a"(n),"=d"(__ret)   \
                :"0"(n),"1"(0),"r"(base));      \
        __ret;                                  \
    })

static char *numero(char *vcs,int n,int base,int lon,int precision,char opcs)
{
    const char *digitos="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char c,signo,temp[36];
    register int i;

    if(base<2||base>36) return 0;
    if(opcs&MINUS) digitos="0123456789abcdefghijklmnopqrstuvwxyz";
    if(opcs&IZQ) opcs&=~CEROS;
    c=(opcs&CEROS)?'0':' ';
    if(opcs&SIGNO)
        {
            --lon;
            if(n<0)
                {
                    n=-n;
                    signo='-';
                }
            else signo=(opcs&CRUZ)?'+':((opcs&ESPACIO)?' ':0);
        }
    else signo=0;
    if(opcs&OXNUM)
        {
            if(base==16) lon-=2;
            else if(base==8) --lon;
        }
    i=0;
    while(n) temp[i++]=digitos[_div(n,base)];
    if(i>precision) precision=i;
    lon-=precision;
    if(!(opcs&(IZQ+CEROS)))
        while(lon-->0) *vcs++=' ';
    if(signo) *vcs++=signo;
    if(opcs&OXNUM)
        if(base==16)
            {
                *vcs++='0';
                *vcs++='x';
            }
        else if(base==8) *vcs++='0';
    if(!(opcs&IZQ))
        while(lon-->0) *vcs++=c;
    while(i<precision--) *vcs++='0';
    while(i--) *vcs++=temp[i];
    while(lon-->0) *vcs++=' ';
    return vcs;
}

static int vcs_ent(const unsigned char **vcs)
{
    register int i=0;

    while(esdigito((unsigned)**vcs))
        i=i*10+*((*vcs)++)-'0';
    return i;
}

int escribvp(char *buf,const unsigned char *plantilla,va_lista arg)
{
    char *vcs,opcs;
    int lon=0,precision=0;

    char *cs;
    register int l,i;

    for(vcs=buf;*plantilla;++plantilla)
        {
            if(*plantilla!='#')
		{
                    *vcs++=*plantilla;
                    continue;
                }
            opcs=0;
        rep:
            switch(*++plantilla)
                {
                case 'I': opcs|=IZQ;
                    goto rep;
                case '+': opcs|=CRUZ;
                    goto rep;
                case '*': opcs|=OXNUM;
                    goto rep;
                case '0': opcs|=CEROS;
                    goto rep;
                case ' ': opcs|=ESPACIO;
                    goto rep;
                }
            lon=0;
            if(esdigito(*plantilla))
                lon=vcs_ent(&plantilla);
            else if(*plantilla=='@')
                lon=va_arg(arg,int);
            precision=0;
            if(*plantilla==':')
                {
                    ++plantilla;
                    if(esdigito((unsigned)*plantilla))
                        precision=vcs_ent(&plantilla);
                    else if(*plantilla=='@')
                        precision=va_arg(arg,int);
                }
            switch(*plantilla)
                {
                case 'e':
                    opcs|=SIGNO;
                case 's':
                    vcs=numero(vcs,va_arg(arg,int),10,lon,precision,opcs);
                    break;
                case 'c':
                    if(!(opcs&IZQ))
                        while(--lon>0) *vcs++=' ';
                    *vcs++=(unsigned char)va_arg(arg,int);
                    while(--lon>0) *vcs++=' ';
                    break;
                case 'x':
                    opcs|=MINUS;
                case 'X':
                    vcs=numero(vcs,va_arg(arg,int),16,lon,precision,opcs);
                    break;
                case 'o':
                    vcs=numero(vcs,va_arg(arg,int),8,lon,precision,opcs);
                    break;
                case 'b':
                    vcs=numero(vcs,va_arg(arg,int),2,lon,precision,opcs);
                    break;
                case 'v':
                    cs=va_arg(arg,char*);
                    l=vcs_lon(cs);
                    if(!precision) precision=l;
                    else if(l>precision) l=precision;
                    if(!(opcs&IZQ))
                        while(l<lon--) *vcs++=' ';
                    for(i=0;i<l;++i)
                        *vcs++=*cs++;
                    while(l<lon--) *vcs++=' ';
                    break;
                case 'p':
                    if(!lon)
                        {
                            lon=8;
                            opcs|=CEROS;
                        }
                    vcs=numero(vcs,(int)va_arg(arg,void*),16,lon,precision,
                               opcs);
                    break;
                case 'n':
                    cs=va_arg(arg,char*);
                    *((int*)cs)=(vcs-buf);
                }
        }
    *vcs='\0';
    return vcs-buf;
}
