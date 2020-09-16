.global load_idt

load_idt:
    movl 4(%esp), %eax # incarca adresa IDT-ului in eax
    lidt (%eax)
    sti
    ret 
