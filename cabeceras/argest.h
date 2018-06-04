/*
 *              argest.h
 *      Macros para el manejo de argumentos variables.
 *      Gonzales Castillo, Cristhian Alberto
 *
 */

#ifndef _ARGEST_H
#define _ARGEST_H

typedef char *va_lista;

#define _va_lon(t)      (((sizeof(t)+sizeof(int)-1)/sizeof(int))*sizeof(int))
#define va_inic(p,a)    ((void)(p=(va_lista)&a+_va_lon(a)))
#define va_arg(p,t)     (p+=_va_lon(t),*((t*)(p-_va_lon(t))))
#define va_fin(a)

#endif
