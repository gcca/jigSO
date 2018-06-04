#define reg(a)                                                          \
    ({register unsigned _r; __asm__("mov %%"a",%0":"=r"(_r));_r;})
