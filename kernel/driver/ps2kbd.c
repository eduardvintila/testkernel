/* Driver pentru tastatura PS/2. */

#include <kernel/system.h>

/* Portul IO DATA al controllerului PS/2 */
#define PS2_DATA 0x60

void kbd_handler(void) 
{
    uint8_t in = inb(PS2_DATA); /* Citeste scan code-ul */
    printf("In: %u\n", in);
}

