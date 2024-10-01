#include "heap.h"

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

Chunk_List allocated_chunks = {0};
Chunk_List freed_chunks = {0};

void* heap_alloc(size_t size) {
  return NULL;
}

void heap_free(void *ptr) {
  
} 
