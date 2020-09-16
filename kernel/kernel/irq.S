.section .text

.macro irq nr
    .global irq\nr
    .type irq\nr, @function
    irq\nr:
        #cli
        push $0 /* cod de eroare */
        push $\nr /* numarul intreruperii */
        jmp irq_common
.endm
.extern irq_handler

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15


irq_common:
     /* Salveaza toti registrii de baza. */
    pusha

    /* Salveaza registrii segment. */
    push %ds
    push %es
    push %fs
    push %gs
    
    /* Incarca segment selectorii specifici kernelului. */
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld

    /* Apeleaza handlerul general pentru intreruperi */
    push %esp
    call irq_handler
    add $4, %esp

    /* Restaureaza registrii segment */
    pop %gs
    pop %fs
    pop %es
    pop %ds

    /* Restaureaza toti registrii de baza */
    popa
    /* Pop la numarul intreruperii si codul de eroare. */
    add $8, %esp
    /* Pop CS, EIP, EFLAGS, SS si ESP(au fost adaugati automat pe stiva de catre procesor la generarea intreruperii) */
    iret
