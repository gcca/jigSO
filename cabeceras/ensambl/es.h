#define salb(v,p)       __asm__("outb %b0,%w1"::"a"(v),"d"(p))
#define entb(p)                                                 \
    ({                                                          \
	register unsigned char _r;                              \
	__asm__ volatile("inb %w1,%b0":"=a"(_r):"d"(p));        \
	_r;                                                     \
    })
