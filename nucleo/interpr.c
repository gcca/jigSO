#include <argest.h>
#include <vcs.h>

#include <quimera/nucleo.h>
#include <quimera/tti.h>

#include <ensambl/es.h>
#include <ensambl/sistema.h>
#include <ensambl/reg.h>

#include <quimera/procs.h>
#include <quimera/cabeza.h>

#include <llamssis.h>

extern unsigned calcmem();
extern int _fbss;
struct tti_cola *temp=&tti_tabla[0].c_auxiliar;

extern void con_limpiar(void);
extern void con_selec(int n);
extern void ta_p4(void);

int psal=0;
char *mkmk="#1:1X\n";

static struct ml_nodo
{
    struct ml_nodo *sig;
    t_lon lon;
};


//__lls0param(int,bifurcar)
int bifurcar(void)
{
    int r;
    __asm__ volatile("int $0x30"
                     :"=a"(r)
                     :"0"(0));
    if(r>=0) return r;
    errn=-r;
    return -1;
}


void interpr(void)
{
    n_impr("cEr0 | ");
    while(1)
	{
	    char a;
	    if(a==127)
		{
		    if(!VACIA(*temp)) DEC(temp->cabeza);
		    continue;
		}
	    if(ULT(*temp)=='\n')
		{
		    temp->buf[temp->cabeza-1]='\0';

		    if(!vcs_comp(temp->buf+temp->cola,"limpiar"))
			con_limpiar();
		    if(!vcs_comp(temp->buf+temp->cola,"salir"))
			__asm__("outb %b0,%w1"::"a"(0xFE),"d"(0x64));
		    if(!vcs_comp(temp->buf+temp->cola,"mem"))
                        n_impr("#s\n",calcmem()/(1024*1024));
		    if(!vcs_comp(temp->buf+temp->cola,"fin"))
			n_impr("#*X\n",&_fbss);
		    if(!vcs_comp(temp->buf+temp->cola,"hola"))
			n_impr("\255QUIMERA DICE HOLA!\n");
		    if(!vcs_comp(temp->buf+temp->cola,"ho"))
                     asm("movw $0x14,%ax;movw %ax,%ds;movw %ax,%es");
		    if(!vcs_comp(temp->buf+temp->cola,"ver"))
                        {/*
                            asm("pushfl\n\t"
                                "pushl  $0xC\n\t"
                                "pushl  $1f\n\t"
                                "iret\n\t"
                                "1:\tmovl       $0x14,%%eax\n\t"
                                "movw   %%ax,%%ds\n\t"
                                "movw   %%ax,%%es\n\t"
                                "movw   %%ax,%%fs\n\t"
                                "movw   %%ax,%%gs\n\t"
                                "movw   %%ax,%%ss;movl $0xFAFA,%%edi"
                                :::"ax");*/
#define GH 0
                            n_impr("#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X;;#1:1X",tarea[GH]->set.enlace_prev,tarea[GH]->set.esp0,tarea[GH]->set.ss0,tarea[GH]->set.esp1,tarea[GH]->set.ss1,tarea[GH]->set.esp2,tarea[GH]->set.ss2,tarea[GH]->set.cr3,tarea[GH]->set.eip,tarea[GH]->set.einds,tarea[GH]->set.eax,tarea[GH]->set.ecx,tarea[GH]->set.edx,tarea[GH]->set.ebx,tarea[GH]->set.esp,tarea[GH]->set.ebp,tarea[GH]->set.esi,tarea[GH]->set.edi,tarea[GH]->set.es,tarea[GH]->set.cs,tarea[GH]->set.ss,tarea[GH]->set.ds,tarea[GH]->set.fs,tarea[GH]->set.gs,tarea[GH]->set.selectdl,tarea[GH]->set.dbmapaes);
                        }
		    if(!vcs_comp(temp->buf+temp->cola,"hac"))
                        {
                            //*(unsigned*)4=0;
                            //n_impr("----#X\n",*(unsigned*)4);
                            /*                            extern void *ta;
                            //    tarea[7]=&ta;
                            extern void subproc_crear(t_mem s);
                            subproc_crear((t_mem)ta_p1);*/
                            extern void ta_p1();
                            register int id_ asm("ax");
                            asm("int $0x30":"=a"(id_):"0"(3),
                                "b"((t_lon)ta_p1));
                            n_impr("#1:1s\n",id_);


                        }
		    if(!vcs_comp(temp->buf+temp->cola,"spe"))
                        {
                            extern int mico;
                            mico=1;
                        }
		    if(!vcs_comp(temp->buf+temp->cola,"spe2"))
                        {
                            extern int mico;
                            mico=2;
                        }
		    if(!vcs_comp(temp->buf+temp->cola,"sps"))
                        {
                            extern int muka;
                            muka=1;
                        }
		    if(!vcs_comp(temp->buf+temp->cola,"mat"))
                        asm("int $0x30"::"a"(2),"b"(tarea[1]->id));
		    if(!vcs_comp(temp->buf+temp->cola,"bas"))
                        {/*
                           extern struct tarea_estructura ta4;
                           fijar_base(&ta4.tdl[2],0xAAAAAAAA);
                           fijar_limite(&ta4.tdl[2],0xBBBBB);
                           n_impr("#8:8X#8:8X\n",ta4.tdl[2].b,ta4.tdl[2].a);*/
                           asm("pushw $0x14;popw %ds");
                            asm("pushw $0x14;popw %es");
                            asm("pushw $0x14;popw %ss");
                            n_impr("   ----#1:1s\n",sizeof(tarea_i));
//n_impr("\n#s\n",({register int m=0;asm("movl  %%esp,%0":"=a"(m));m;}));
//n_impr("\n\n#1:1X    #1:1X\n\n",*(t_lon*)0x100,*(t_lon*)0x104);
//                            struct ml_nodo *ee=(struct ml_nodo*)0x100;
/*                            t_mem ml=(t_mem)asigml(909);
                            n_impr("  ---- #p  #X\n",ml,reg("esp"));*/
                        }
                    if(!vcs_comp(temp->buf+temp->cola,"bif"))
                        {
                            register int jl asm("ax");
                            asm("int $0x30":"=a"(jl):"0"(0));

                            n_impr("   ----#1:1s\n",reg("esp"));
                            /*                            if(jl)
                            //if(bifurcar())
                                {
                                    n_impr("padre  #1:1X\n",tarea_act->id);
                                }
                            else
                                {
                                    n_impr("hijo   #1:1X\n",tarea_act->id);
                                    for(;;);
                                    }*/
                            //asm("movl $0xFF,%ebx");
                        }
		    if(temp->buf[temp->cola]=='t')
			{
			    if(((unsigned)temp->buf[1]-48)<8)
				{
				    con_selec((unsigned)temp->buf[1]-48);
				    n_impr("tti#c\n",temp->buf[1]);
				}
			}
                    if(!vcs_comp(temp->buf+temp->cola,"psal"))
                        psal=45;
                    if(!vcs_comp(temp->buf+temp->cola,"sel"))
                        {
                            asm("pushl %ds;pushl mkmk;"
                                "call n_impr;addl $8,%esp");
                            asm("pushl $0x14;popl %ds");
                        }
                    /*		    if(temp->buf[temp->cola]=='i')
			{
			    switch(temp->buf[1]-48)
				{
				case 0: asm("int $0"); break;
				case 1: asm("int $1"); break;
				case 2: asm("int $2"); break;
				case 3: asm("int $3"); break;
				case 4: asm("int $4"); break;
				case 5: asm("int $5"); break;
				case 6: asm("int $6"); break;
				case 7: asm("int $7"); break;
				case 8: asm("int $8"); break;
				case 9: asm("int $9"); break;
				case 10: asm("int $10"); break;
				case 11: asm("int $11"); break;
				case 12: asm("int $12"); break;
				case 13: asm("int $13"); break;
				case 14: asm("int $14"); break;
				case 15: asm("int $15"); break;
				case 16: asm("int $16"); break;
				case 17: asm("int $17"); break;
				case 18: asm("int $18"); break;
				case 19: asm("int $19"); break;
                                }
                                }*/
		    n_impr("cEr0 | ");
		    tti_tabla[0].c_auxiliar.cola=
			    tti_tabla[0].c_auxiliar.cabeza=0;
		}
	    //else PONC(a,*temp);
	}
}
