/* Intreruperi hardware */

#include <kernel/system.h>
#include <driver/ps2kbd.h>
#include <string.h>


#define PIC1		  0x20		/* Portul IO pentru master PIC */
#define PIC2		  0xA0		/* Portul IO pentru slave PIC */
#define PIC1_COMMAND  PIC1  
#define PIC1_DATA	  (PIC1+1)
#define PIC2_COMMAND  PIC2
#define PIC2_DATA	  (PIC2+1)

/* Offset-ul portilor de intrerupere in tabelul IDT pentru IRQ-urile
 * tratate de master PIC, respectiv slave PIC.
 */
#define IDT_OFFSET_PIC1 32
#define IDT_OFFSET_PIC2 40

/* Vector de pointeri catre functiile care se ocupa de
 * tratarea intreruperilor hardware.
 */
void (*handlers[16]) (void); 

void irq_ack(int int_no)
{
    if (int_no > 7)
        outb(PIC2, 0x20); /* Daca intreruperea a provenit de la linia 7 sau mai mult, atentioneaza si slave PIC-ul */  
    outb(PIC1, 0x20);
}

void init_pic(void)
{
    
    outb(PIC1_COMMAND, 0x11); /* Initializeaza master PIC */
    outb(PIC2_COMMAND, 0x11); /* Initializeaza slave PIC */
    outb(PIC1_DATA, IDT_OFFSET_PIC1); /* master PIC offset */
    outb(PIC2_DATA, IDT_OFFSET_PIC2); /* slave PIC offset */
    outb(PIC1_DATA, 4); /* Atentioneaza master PIC-ul de sclavul de la IRQ2 */
    outb(PIC2_DATA, 2); /* Spune-i sclavului ca-i sclav */
    outb(PIC1_DATA, 0x01);
    outb(PIC1_DATA, 0x01);
    outb(PIC1_DATA, 0xFD); /* Ignora toate intreruperile mai putin cele de la tastatura(IRQ1)*/
    outb(PIC2_DATA, 0xFF);
}

void init_irq(void)
{
    /* Initializeaza functiile ce vor fi apelate la generarea intreruperilor */
    
    memset(handlers, NULL, sizeof(handlers));
    
    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();
    
    idt_setup_gate_irq(0, (uintptr_t) irq0);
    idt_setup_gate_irq(1, (uintptr_t) irq1);
	idt_setup_gate_irq(2, (uintptr_t) irq2);
    idt_setup_gate_irq(3, (uintptr_t) irq3);
    idt_setup_gate_irq(4, (uintptr_t) irq4);
    idt_setup_gate_irq(5, (uintptr_t) irq5);
    idt_setup_gate_irq(6, (uintptr_t) irq6);
    idt_setup_gate_irq(7, (uintptr_t) irq7);
    idt_setup_gate_irq(8, (uintptr_t) irq8);
    idt_setup_gate_irq(9, (uintptr_t) irq9);
    idt_setup_gate_irq(10, (uintptr_t) irq10);
    idt_setup_gate_irq(11, (uintptr_t) irq11);
    idt_setup_gate_irq(12, (uintptr_t) irq12);
    idt_setup_gate_irq(13, (uintptr_t) irq13);
    idt_setup_gate_irq(14, (uintptr_t) irq14);
    idt_setup_gate_irq(15, (uintptr_t) irq15);
    
    handlers[1] = kbd_handler;
}



void irq_handler(struct regs* r)
{
    /* Apeleaza handler-ul corespunzator intreruperii generate. */
    
    if (handlers[r->int_no])
       handlers[r->int_no] ();
   
    irq_ack(r->int_no); /* Atentioneaza PIC-ul ca intreruperea a fost tratata. */
}
