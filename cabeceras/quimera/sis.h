#include <defest.h>

int sis_bifurcar(void);
int sis_salir(int coderr);
int sis_matar(long idp);
int subproc_crear(t_func func);

inline void sis_inic(void);

t_func sis_tabla[]={sis_bifurcar,sis_salir,sis_matar,subproc_crear};
