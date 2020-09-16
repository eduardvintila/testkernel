# Constate pentru header-ul multiboot.
.set ALIGN,    1<<0             # Aliniere la page boundry
.set MEMINFO,  1<<1             # Obtine o mapare a memoriei
.set FLAGS,    ALIGN | MEMINFO  # Multiboot flag
.set MAGIC,    0x1BADB002       # Numarul magic pentru multiboot
.set CHECKSUM, -(MAGIC + FLAGS) # checksum pentru multiboot

# Declara header-ul conform standardului multiboot.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Zoona pentru stiva.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# Punctul de intrare al kernelului.
.section .text
.global _start
.type _start, @function
_start:
	# Seteaza pointer-ul catre stiva.
	movl $stack_top, %esp
	
	# Adauga pe stiva numarul magic si pointer-ul catre structura de informatii multiboot
    push %eax
    push %ebx
    
	# Apeleaza constructorii globali.
	call _init
	
	# Transfera controlul catre kernel-ul principal.
	call kernel_main

	# Stagneaza daca ne intoarcem din kernel.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
