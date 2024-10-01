#include "heap.h"
#include <assert.h>
#include <stdio.h>

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

Chunk_List allocated_chunks = {0};
Chunk_List freed_chunks = {0};

void chunk_list_dump(const Chunk_List *list) {
  printf("Chunks (%zu):\n", list->count);
  for (size_t i = 0; i < list->count; ++i) {
    printf("chunk's start address: %p, size : %zu\n",
           list->chunks[i].start,
           list->chunks[i].size);
  }
}

void chunk_list_insert(Chunk_List *list, void *start, size_t size)
{
  assert(list->count < CHUNK_LIST_CAP);
  list->chunks[list->count].start = start;
  list->chunks[list->count].size = size;

  for (size_t i = list->count; i>0 && list->chunks[i].start < list->chunks[i-1].start; --i)
  {
    const Chunk t = list->chunks[i];
    list->chunks[i] = list->chunks[i-1];
    list->chunks[i-1] = t;
  }  
  list->count +=1;
}

void* heap_alloc(size_t size) {
  if (size > 0) {
    assert(heap_size + size <= HEAP_CAPACITY);
    void* ptr = heap + heap_size;
    heap_size += size;
    chunk_list_insert(&allocated_chunks, ptr, size);
    return ptr;
  }
  else {
    return NULL;
  }
}

void heap_free(void *ptr) {
  
} 
