// #include <string.h>
#include "include/memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern char _heap_base[];
extern char _stack[];

char *_sbrk(int numbytes){
  
  char *base;

  if (heap_ptr == NULL) {
    heap_ptr = (char *)&_heap_base;
  }

  if((heap_ptr + numbytes) <=_stack) {
    base = heap_ptr;
    heap_ptr += numbytes;
    return (base);
  }
  else {
    //errno = ENOMEM;
    return NULL;
  }

}

// super-naive allocator
void *kmalloc(size_t size) {
    // 遍历空闲链表，找到第一个足够大的块
    struct Block *curr = free_list;
    struct Block *prev = NULL;

    while (curr != NULL && curr->size < size) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        // 没有足够大的块，使用 _sbrk 来分配更多的内存
        char *base = _sbrk(size);
        if (base == NULL) {
            // 内存分配失败
            return NULL;
        }

        // 创建一个新块并添加到空闲链表
        struct Block *new_block = (struct Block *)base;
        new_block->size = size;
        new_block->next = NULL;

        if (prev != NULL) {
            prev->next = new_block;
        } else {
            // 空闲链表为空，更新头节点
            free_list = new_block;
        }

        return (void *)(base + sizeof(struct Block));
    } else {
        // 找到足够大的块，从空闲链表中移除
        if (prev != NULL) {
            prev->next = curr->next;
        } else {
            // 更新头节点
            free_list = curr->next;
        }

        return (void *)curr + sizeof(struct Block);
    }
}

void kfree(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // 将块添加到空闲链表
    struct Block *block = (struct Block *)(ptr - sizeof(struct Block));
    block->next = free_list;
    free_list = block;
}



