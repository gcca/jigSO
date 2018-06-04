#include <quimera/memoria.h>

static t_lon numpags;
static unsigned char *mapa;

extern inline void memdin_inic(void);

t_mem mem_obtpagt(enum t_pag t)
{
    register t_lon r __asm__("ax");
    __asm__("std\n\t"
            "testl      $1,%3\n\t"
            "je         1f\n\t"
            "repne      scasb\n\t"
            "jne        4f\n\t"
            "movb       %b1,1(%4)\n\t"
            "shll       $12,%2\n\t"
            "jmp        3f\n\t"
            "1:\ttestl  $2,%3\n\t"
            "je         2f\n\t"
            "repne      scasw\n\t"
            "jne        4f\n\t"
            "movw       %w1,2(%4)\n\t"
            "shll       $13,%2\n\t"
            "jmp        3f\n\t"
            "2:\trepne  scasl\n\t"
            "jne        4f\n\t"
            "movl       %1,4(%4)\n\t"
            "shll       $14,%2\n\t"
            "3:\tmovl   %2,%0\n\t"
            "addl       %6,%0\n\t"
            "4:\tcld"
            :"=a"(r):"b"(16843009),"c"(numpags/t),"d"(t),
             "D"((t_lon)mapa+numpags-t),"0"(0),"i"(MEM_INF)
            );
    return (t_mem)r;
}

void mem_libpagt(unsigned long dir,enum t_pag t)
{
    dir-=MEM_INF;
    switch(t)
        {
        case 1:
            dir>>=12;
            mapa[dir]=0;
            break;
        case 2:
            dir>>=13;
            ((unsigned short*)mapa)[dir]=0;
            break;
        default:
            dir>>=14;
            ((unsigned*)mapa)[dir]=0;
        }
}

void mem_coppagt(t_mem de,t_mem a,enum t_pag t)
{
    register int i;
    register int l=t==1?1024:t==2?2048:4096;

    for(i=0;i<l;++i)
        ((t_lon*)a)[i]=((t_lon*)de)[i];
}

t_lon calcmem(void)
{
    um *lon=(um*)MEM_INF,*val;
    unsigned despl=0x100000;

    while(1)
        {
            *lon=0x40;
            if(*lon!=0x40)
                {
                    if(despl==1)
                        break;
                    else
                        lon=val;
                    despl/=0x400;
                }
            else
                {
                    val=lon;
                    lon+=despl;
                }
        }
    return (t_lon)lon;
}

inline void mem_inic(void)
{
    register unsigned char *mt;

    md_inic();
    numpags=(calcmem()-MEM_INF)>>12;
    mapa=(unsigned char*)md_asignar(numpags);
    *(unsigned*)mapa=16843009;
    n_impr("N\243m de p\240ginas: #1:1s\nMem inferior: #1:1s\n"
          "Lon de mem: #1:1s MiB\n",numpags,MEM_INF,
          ((numpags<<12)+MEM_INF)/MEM_INF);
    /*
    unsigned long mlml=mem_obtpagt(2);
    unsigned long ml=mem_obtpagt(1);
    unsigned long m=mem_obtpagt(4);

    //mem_obtpag(1);
    //n_impr("\n#p    #p     #p\n", mem_obtpag(2),mem_obtpag(1),mem_obtpag(4));


    register unsigned int i;
    register unsigned char *ms=mapa;
    for(i=0;i<numpags;++i)
        n_impr("#1:1s",ms[i]);
    n_impr("\n");


    mem_libpagt(m,PAGT4);
    mem_libpagt(ml,PAGT1);
    mem_libpagt(mlml,PAGT2);
    for(i=0;i<numpags;++i)
        n_impr("#1:1s",ms[i]);
    n_impr("\n");
    for(;;);*/
}
