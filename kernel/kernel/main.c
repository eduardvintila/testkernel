#include <kernel/system.h>
#include <kernel/tty.h>
#include <boot/multiboot.h>


void get_mmap(multiboot_info_t* mbd)
{
    /* Verifica daca bitul 6 este setat pentru a obtine o mapare a memoriei */
    if (mbd->flags & (1<<6))
    {
        struct multiboot_mmap_entry* p;
        size_t i = 1;
        
        p = (struct multiboot_mmap_entry*) mbd->mmap_addr;
        
        
        while ((unsigned long) p < mbd->mmap_addr + mbd->mmap_length)
        {
            printf("Zona %u de memorie.\nAdresa inceput: %l.\nLungime: %u.\nTip: %u\n",
                    i, 
                    (unsigned long long) p->addr, 
                    (unsigned) p->len,
                    (unsigned) p->type);
            
            //printf("\n\n\n");
            i++;
            p = (struct multiboot_mmap_entry*) ((unsigned long) p + p->size + sizeof(p->size));
        }
    }
} 


void kernel_main(multiboot_info_t* mbd, unsigned int magic) 
{
    
    init_gdt();
    
    init_terminal();
    
    init_idt();
    
    init_pic();
    
    init_irq();
    
    
    while(1)
    {
        /* Kernelul doarme. */
    }
    
    //__asm__  ("div %0" :: "r"(0));
    //get_mmap(mbd);
    
}
