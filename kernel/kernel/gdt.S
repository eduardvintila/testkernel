.global load_gdt

load_gdt:
	cli
	movl 4(%esp), %eax
	lgdt (%eax) # incarca adresa GDT-ului in registrul GDTR
	
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	jmp $0x08, $.long_jump
	
.long_jump:
	ret
	 
