#include <quimera/nucleo.h>
#include <quimera/procs.h>

#include <ensambl/es.h>
#include <ensambl/sistema.h>

#define NERR    (valreg[8])
#define EAX     (valreg[7])
#define EBX     (valreg[4])
#define ECX     (valreg[6])
#define EDX     (valreg[5])
#define ESI     (valreg[1])
#define EDI     (*valreg)
#define ESP     ((unsigned)valreg+48)
#define EBP     (valreg[2])
#define EIP     (valreg[9])
#define INDS    (valreg[11])
#define CSI     (valreg[10])

extern void errdiv(void);
extern void excepdep(void);
extern void intnenm(void);
extern void ptorup(void);
extern void desb(void);
extern void chlim(void);
extern void codnval(void);
extern void coprocndisp(void);
extern void fallodbl(void);
extern void reserv4coproc3(void);
extern void setnval(void);
extern void segmndisp(void);
extern void exceppila(void);
extern void proteccgen(void);
extern void fallopag(void);
extern void errupf(void);
extern void chalin(void);
extern void reservado(void);

void morir(char *vcs,unsigned long *valreg)
{
    n_impr("\n#v: #:1X\nEIP:  #0:4X:#p\nINDS: #:0b\nESP:  #0:4X:#p\n"
          "EAX: #0:8X  EBX: #0:8X  ECX: #0:8X  EDX: #0:8X\n"
          "ESI: #0:8X  EDI: #0:8X  EBP: #0:8X\n",
          vcs,NERR,CSI,EIP,INDS,CSI,ESP,EAX,EBX,ECX,EDX,ESI,EDI,EBP);
}

void fr_errdiv(unsigned long *esp)
{
    morir("error de divisi\242n",esp);
}

void fr_excepdep(unsigned long *esp)
{
    morir("Excepci\242n de depuraci\242n",esp);
}

void fr_intnenm(unsigned long *esp)
{
    morir("Interrupci\242 no enmascarable",esp);
}

void fr_ptorup(unsigned long *esp)
{
    morir("Punto de ruptura de interrupci\242n",esp);
}

void fr_desb(unsigned long *esp)
{
    morir("Desbordamiento",esp);
}

void fr_chlim(unsigned long *esp)
{
    morir("Chequeo de l\241mites",esp);
}

void fr_codnval(unsigned long *esp)
{
    morir("C\242digo de instrucci\242n no v\240lido",esp);
}

void fr_coprocndisp(unsigned long *esp)
{
    morir("Coprocesador no disponible",esp);
}

void fr_fallodbl(unsigned long *esp)
{
    morir("Fallo doble",esp);
}

void fr_reserv4coproc3(unsigned long *esp)
{
    morir("80486: Reservado | 80386 Sobre ejecuci\242n del segemento del "
	  "Coprocesador",esp);
}

void fr_setnval(unsigned long *esp)
{
    morir("Segemento de Estado de Tarea(SET) no v\240lido",esp);
}

void fr_segmndisp(unsigned long *esp)
{
    morir("Segemento no disponible",esp);
}

void fr_exceppila(unsigned long *esp)
{
    morir("Excepci\242n de pila",esp);
}

void fr_proteccgen(unsigned long *esp)
{
    morir("Protecci\242n general",esp);
}

void fr_fallopag(unsigned long *esp)
{
    morir("Fallo de p\240gina",esp);
}

void fr_errupf(unsigned long *esp)
{
    morir("Error de la Unidad de Punto Flotante(UPF)",esp);
}

void fr_chalin(unsigned long *esp)
{
    morir("Chequeo de alineaci\242n",esp);
}

void fr_reservado(unsigned long *esp)
{
    morir("Reservado 15,18-47",esp);
}

inline void trampas_inic(void)
{
    register int i;
    insp_trampa(0,&errdiv);
    insp_trampa(1,&excepdep);
    insp_trampa(2,&intnenm);
    insp_sistema(3,&ptorup);
    insp_sistema(4,&desb);
    insp_sistema(5,&chlim);
    insp_trampa(6,&codnval);
    insp_trampa(7,&coprocndisp);
    insp_trampa(8,&fallodbl);
    insp_trampa(9,&reserv4coproc3);
    insp_trampa(10,&setnval);
    insp_trampa(11,&segmndisp);
    insp_trampa(12,&exceppila);
    insp_trampa(13,&proteccgen);
    insp_trampa(14,&fallopag);
    insp_trampa(15,&reservado);
    insp_trampa(16,&errupf);
    insp_trampa(17,&chalin);
    for(i=17;i<32;++i)
	insp_trampa(i,&reservado);
}
