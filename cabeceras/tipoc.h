#ifndef _TIPOC_H
#define _TIPOC_H

#define _A      0x01
#define _I      0x02
#define _S      0x04
#define _C      0x08
#define _D      0x10
#define _E      0x20
#define _H      0x40
#define _SE     0x80

extern unsigned char _tipoc[];

#define esalfanum(c)    ((_tipoc)[c]&(_A|_I|_D))
#define esalfa(c)       ((_tipoc)[c]&(_A|_I))
#define esdigito(c)     ((_tipoc)[c]&(_D))
#define escntrl(c)      ((_tipoc)[c]&(_C))
#define esminus(c)      ((_tipoc)[c]&(_I))
#define esmayus(c)      ((_tipoc)[c]&(_A))
#define essimb(c)       ((_tipoc)[c]&(_S))
#define esespac(c)      ((_tipoc)[c]&(_E))
#define esgrafc(c)      ((_tipoc)[c]&(_S|_A|_I|_D))
#define esimprbl(c)     ((_tipoc)[c]&(_S|_A|_I|_D|_SE))
#define eshexa(c)       ((_tipoc)[c]&(_D|_H))

#define esascii(c)      (((unsigned)c)<=0x7F)
#define aascii(c)       (((unsigned)c)&0x7F)

#define amayus(c)       (esminus(c)?c+('A'-'a'):c)
#define aminus(c)       (esmayus(c)?c+('A'+'a'):c)

#endif
