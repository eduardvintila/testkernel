/* Segmentarea memoriei */

#include <kernel/system.h>

#define GDT_CODE_KER 0x9A
#define GDT_DATA_KER 0x92
#define GDT_CODE_USER 0xFA
#define GDT_DATA_USER 0xF2


struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
    
}__attribute__((packed));

/* Structura pentru registrul GDTR */
struct gdt_ptr
{
  uint16_t limit;
  struct gdt_entry* base; 
}__attribute__ ((packed));


static struct gdt_entry gdt[3]; /* 3 segmente */

static struct gdt_entry create_descriptor(uint32_t base, uint32_t limit, uint8_t access_flag)
{
    struct gdt_entry descriptor;
    
    descriptor.limit_low = limit & 0xFFFF;
    descriptor.base_low  = base  & 0xFFFF;
    descriptor.base_mid  = (base >> 16)  & 0xFF;
    descriptor.access = access_flag;
    descriptor.granularity = ((limit >> 16) & 0xF) | 0xC0;
    descriptor.base_high = (base >> 24)  & 0xFF;
    
    return descriptor;
    
}

void init_gdt(void)
{
    /* Creeaza segmentari ale memoriei */
    
    struct gdt_ptr gp;
    extern void load_gdt(struct gdt_ptr* gp);
    
    gdt[0] = create_descriptor(0, 0, 0); /* Descriptor nul(necesar) */
    gdt[1] = create_descriptor(0x0, 0xFFFFFFFF, GDT_CODE_KER); /* Segmentul de cod kernel */
    gdt[2] = create_descriptor(0x0, 0xFFFFFFFF, GDT_DATA_KER); /* Segmentul de kernel data */
    
    gp.limit = sizeof(struct gdt_entry) * 3 - 1;
    gp.base = gdt;
    
    load_gdt(&gp);
}
