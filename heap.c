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

int chunk_list_find(const Chunk_List *list, void *ptr)
{
  int left = 0, right = list->count;
  int mid = left + (right - 1) / 2;
  while(mid >= left && mid <= right) {
    if (list->chunks[mid].start > ptr) {
      right = mid - 1;
    } else if (list->chunks[mid].start < ptr) {
      left = mid + 1;
    } 
    else {
      return mid;
    }
    mid = left + (right - 1) / 2;
  }
  return -1;
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
  const int index = chunk_list_find(&allocated_chunks, ptr);
  assert(index >= 0);
  chunk_list_insert(&freed_chunks, 
                    allocated_chunks.chunks[index].start, 
                    allocated_chunks.chunks[index].size);
  chunk_list_remove(&allocated_chunks, (size_t)index);
} 
