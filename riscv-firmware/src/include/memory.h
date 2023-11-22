#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#define ALIGNMENT 8 // must be a power of 2
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define SIZE_T_SIZE (ALIGN(sizeof(size_t))) // header size

struct Block {
    size_t size;
    struct Block *next;
};

char *_sbrk(int numbytes);


static char *heap_ptr = NULL;
static struct Block *free_list = NULL;

void *kmalloc(size_t size);
void kfree(void* ptr);




#endif


