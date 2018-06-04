#include <quimera/memoria.h>
#include <quimera/procs.h>
#include <defest.h>
#include <ensambl/sistema.h>
#include <quimera/tti.h>
#include <quimera/cabeza.h>

extern int psal;
extern int salir(int cd);

void ta_p2(void)
{
    char *p=(char*)0xB8038;
    *(p+1)=0x3e;
    char c=59;
    int i=0;
    while(1)
	{
	    int ii=0x5FFFF;
	    for(;ii;--ii);
	    *p=c+i++;
	    if(i==10) i=0;
	}
}



void ta_p3(void)
{
    // char *p=(char*)0xBA880;
    char *p=(char*)0xB8080;
    *(p+1)=0x70;
    char c=65;
    int i=0;
    while(1)
	{
	    int ii=0x23FF;
	    for(;ii;--ii);
	    *p=c+i++;
	    if(i==10) i=0;
	}
}
int mico=0;
int muka=0;
void ta_p4(void)
{
    //char *p=(char*)0xBAEEA;
    char *p=(char*)0xB80EA;
    *(p+1)=0x8D;
    char c=48;
    int i=0;
    while(1)
	{
	    int ii=0xFFF;
	    for(;ii;--ii);
	    *p=c+i++;
	    if(i==10) i=0;
            if(muka)
                {
                    muka=0;
                }
            if(mico==2)
                {
                    //n_impr("#1:1s\n",tarea_act->padre);
                    mico=0;subproc_crear(ta_p3);
                }
	}
}

void ta_p5(void)
{
    //    char *p=(char*)0xBBE90;
    char *p=(char*)0xB80E8;
    *(p+1)=0x3E;
    char c=48;
    int i=0;
    while(1)
	{
	    int ii=0x1FFFF;
	    for(;ii;--ii);
	    *p=c+i++;
	    if(i==10) i=0;
	}
}
void ta_p1(void)
{
    int i=0;
    char *p=(char*)0xBA000-7080;

    while(1)
	{
	    *(p+1)=0x1F;
	    char c=48;
	    int ii=0x23FFFF;
	    for(;ii;--ii);
	    *p=c+i++;
	    if(i==10) i=0;
            if(psal==45)
                asm("int $0x30"::"a"(1));
            if(mico==1)
                {
                    mico=0;subproc_crear(ta_p4);
                    subproc_crear(ta_p2);
                }
            /*            if(mico==2)
                {//n_impr("#1:1s\n",tarea_act->id);
                    mico=0;//if(tarea_act->id==0) p=0xB8004;
                    }*/

	}
}
extern void interpr(void);
/*
struct tarea_estructura ta=
{
    4556,0,0,0x200,0,
    {{0,0},{0x000000FF,0x00CF9A00},{0x000000FF,0x00CF9200}},
    {0,0,0,0,0,0,0,0x0,(unsigned)ta_p5,0x202,0,0,0,0,0x200000-0x10,
     0x200000-0x10,0,0,0x14,0xC,0x14,0x14,0x14,0x14,TDL(1),0x00000000}
};
*/
void inicio(void)
{
//	n_impr("HOLA");
for(;;);
    tti_inic();
    sis_inic();
    mem_inic();

    proc_inic();
    /*
            fij_set(SET(1),&ta.set);
            fij_tdl(TDL(1),&tarea[0]->tdl);
        tarea[1]=&ta;
    */


    //("\nQuimera v[10^(-17)]\n"
    //  "]GCCA[ Gonzales Castillo, Cristhian Alberto - Febrero 2009\n\n")
    /*    fij_base(&ta2.tdl[2],0xABCD1234);
    fij_limite(&ta2.tdl[2],0x54321);
    n_impr("#1:2X  ---   #1:1X#1:1X\n\n",obt_base(&ta2.tdl[2]),
    ta2.tdl[2].b,ta2.tdl[2].a);*/
    n_impr("\nQuimera v[10^(-17)]\t]GCCA[ - Febrero 2009\n\n");


//    interpr();
    /*    int nl=0;
          unsigned char *mm=(unsigned char*)gdt+15+8*4;
          for(;nl<8;++nl)
          {
          impr("#2:2X",*mm);
          mm--;
          }*/
    for(;;);
}
