/* Tabelul ce contine selectori pentru tratarea exceptiilor si 
 * a intreruperilor hardware si software. */

#include <kernel/system.h>

#define IDT_OFFSET_IRQ 32

struct idt_entry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
    
}__attribute__ ((packed));


/* Structura pentru registrul IDTR */
struct idt_ptr
{
    uint16_t limit;
    struct idt_entry* base;
}__attribute__ ((packed));



/* 0-31   - exceptii generate de procesor
 * 32-47  - intreruperi hardware
 * restul - intreruperi software
 */
struct idt_entry idt[48]; 


struct idt_entry create_gate(uintptr_t addr, uint16_t sel, uint8_t type)
{
    struct idt_entry gate;
    gate.offset_low = addr & 0xFFFF;
    gate.selector = sel;
    gate.zero = 0;
    gate.type_attr = type;
    gate.offset_high = (addr & 0xFFFF0000) >> 16;
    return gate;
}

void idt_setup_gate_irq(int no, uintptr_t addr)
{
    /* TODO: Verificari */
    idt[IDT_OFFSET_IRQ + no] = create_gate(addr, 0x08, 0x8E);
}

void idt_setup_gate_isr(int no, uintptr_t addr)
{
    /* TODO: Verificari */
    idt[no] = create_gate(addr, 0x08, 0x8E);
}


void init_idt(void)
{
    extern void load_idt(struct idt_ptr* ip);
    struct idt_ptr ip;
    
    ip.limit = 48 * sizeof(struct idt_entry) - 1;
    ip.base = idt;
    load_idt(&ip);
    
}

