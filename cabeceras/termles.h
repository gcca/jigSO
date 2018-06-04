/*
 * Archivo:             termles.h
 * Autor:       Gonzales Castillo, Cristhian Alberto.
 */

#ifndef _TERMLES_H
#define	_TERMLES_H

#define TTI_BUF_LON     512

#define NUMCC   17
struct termles
{
    unsigned long is_e;
    unsigned long is_s;
    unsigned long is_l;
    unsigned char c_cc[NUMCC];
};

#define CENT    0
#define CSAL    1
#define CBORR   2
#define CMAT    3
#define CFDF    4
#define CHORA   5
#define CMIN    6
#define CCONMUT 7
#define CEMP    8
#define CDET    9
#define CSUSP   10
#define CFDL    11
#define CREIMPR 12
#define COMITIR 13
#define CBORRP  14
#define CLINSIG 15
#define CFDL2   16

#define SENALE  0000001
#define REGLAE  0000002
#define CASOX   0000004
#define ECO     0000010
#define ECOE    0000020
#define ECOT    0000040
#define ECONL   0000100
#define NOLIMP  0000200
#define ADET    0000400
#define ECOCTRL 0001000
#define ECOPRT  0002000
#define ECOET   0004000
#define LIMPS   0010000
#define PLDIN   0020000
#define EEXTEN  0040000

#define SPOST   0000001
#define SCRAN   0000002
#define SCNAR   0000004
#define SCANR   0000010
#define SCAM    0000020

#endif
