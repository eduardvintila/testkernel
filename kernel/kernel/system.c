#include <kernel/system.h>

void outb(uint16_t port, uint8_t val)
{
    /* Scrie un byte intr-un port IO */
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port)
{
    /* Citeste un byte dintr-un port IO */
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
} 
