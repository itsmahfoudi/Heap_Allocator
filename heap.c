#include "heap.h"
#include <assert.h>
#include <stdio.h>

char heap[HEAP_CAPACITY] = {0};
size_t heap_size = 0;

Chunk_List allocated_chunks = {0};
Chunk_List freed_chunks = {
  .count = 1,
  .chunks = {
    [0] = {.start = heap, .size = sizeof(heap)}
  },
};
Chunk_List tmp_chunks = {0};

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

void chunk_list_remove(Chunk_List *list, size_t index) {
  assert(index <= list->count);
  for (size_t i = index; i < list->count - 1; ++i) {
    list->chunks[i] = list->chunks[i+1];
  }
  list->count -= 1;
}

void chunk_list_merge(Chunk_List *dst, const Chunk_List* src) {
  dst->count = 0;
  for (size_t i = 0; i < src->count; ++i) {
    const Chunk chunk = src->chunks[i];
    
    if (dst->count > 0) {
      Chunk *top_chunk = &dst->chunks[dst->count - 1];

      if (top_chunk->start + top_chunk->size == chunk.start) {
        top_chunk->size += chunk.size;
      } else {
        chunk_list_insert(dst, chunk.start, chunk.size);
      }
    } else {
      chunk_list_insert(dst, chunk.start, chunk.size);
    }
  }
}

void* heap_alloc(size_t size) {
  if(size > 0) {
    chunk_list_merge(&tmp_chunks, &freed_chunks);
    freed_chunks = tmp_chunks;

    for (size_t i = 0; i < freed_chunks.count; ++i) {
      const Chunk chunk = freed_chunks.chunks[i];
      if (chunk.size >= size) {
        chunk_list_remove(&freed_chunks, i);

        chunk_list_insert(&allocated_chunks, chunk.start, size);
        const size_t remaing_bytes = chunk.size - size;

        if (remaing_bytes > 0) {
          chunk_list_insert(&freed_chunks, chunk.start + size, remaing_bytes);
        }
      
        return chunk.start;
      }
    } 
  }
  return NULL;
}

void heap_free(void *ptr) {
  if (ptr != NULL) {
    const int index = chunk_list_find(&allocated_chunks, ptr);
    assert(index >= 0);
    chunk_list_insert(&freed_chunks, 
                    allocated_chunks.chunks[index].start, 
                    allocated_chunks.chunks[index].size);
    chunk_list_remove(&allocated_chunks, (size_t)index); 
  } else {

  }
}
