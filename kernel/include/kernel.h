#ifndef _KERNEL_KERNEL_H
#define _KERNEL_KERNEL_H

#include <multiboot.h>

#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define __is_libk

/**
 * Main
 */
void kernelMain(multiboot_info_t* mbd, unsigned int magic);

#endif
