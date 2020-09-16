#include <stdint.h>
#include <stdio.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);


void init_gdt(void);

struct regs 
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

void init_idt(void);
void init_irq(void);
void idt_setup_gate_irq(int no, uintptr_t addr);
void idt_setup_gate_isr(int no, uintptr_t addr);
