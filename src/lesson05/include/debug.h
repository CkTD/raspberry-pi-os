#ifndef __DEBUG_H_
#define __DEBUG_H_


void debug(unsigned long msg, unsigned long lr, unsigned long sp);

#define DEBUG(msg) \
    do {  \
    register unsigned long __lr asm("x30");  \
    register unsigned long __sp asm("sp"); \
    debug((unsigned long)msg, __lr, __sp);   \
    } while(0)

#endif
