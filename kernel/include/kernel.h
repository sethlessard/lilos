#ifndef _KERNEL_KERNEL_H
#define _KERNEL_KERNEL_H

#include <multiboot.h>

#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define __is_libk

/**
 * Init.
 */
void kernel_init(multiboot_info_t* mbd, unsigned int magic);

/**
 * Main.
 */ 
void kernel_main(void);

#endif
