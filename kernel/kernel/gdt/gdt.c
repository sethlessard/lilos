#include <gdt.h>

#include <klibc/kstdint.h>

struct gdt_entry
{  
    uint16_t limitLow;      // lower 16 bits of limit
    uint16_t baseLow;       // lower 16 bits of the base
    uint8_t baseMiddle;     // the next 8 bits of the base
    uint8_t access;         // access flags, determine what ring this segment can be used in.
    uint8_t granularity;    
    uint8_t baseHigh;       // the upper 8 bits of the base
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr
{
    uint16_t limit;         // the upper 16 bits of all selector limits
    uint32_t base;          // the address of the first gdt_entry.
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

extern void GDT_flush(uint32_t gdt);
void _setGDTEntry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

gdt_entry_t gdt[5];
gdt_ptr_t gdtPtr;

/**
 * Initialize the GDT.
 */
void GDT_init(void) {
    // setup the GDT pointer
    gdtPtr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdtPtr.base = (uint32_t)&gdt;

    // add the null segment
    _setGDTEntry(0, 0, 0, 0, 0);

    // kernel code segment
    _setGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // kernel data segment
    _setGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // user code segment
    _setGDTEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // user data segment
    _setGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // flush the gdt pointer.
    GDT_flush((uint32_t)&gdtPtr);
}

/**
 * 
 */ 
void _setGDTEntry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
   gdt[num].baseLow    = (base & 0xFFFF);
   gdt[num].baseMiddle = (base >> 16) & 0xFF;
   gdt[num].baseHigh   = (base >> 24) & 0xFF;

   gdt[num].limitLow   = (limit & 0xFFFF);
   gdt[num].granularity = (limit >> 16) & 0x0F;

   gdt[num].granularity |= granularity & 0xF0;
   gdt[num].access      = access;
}
