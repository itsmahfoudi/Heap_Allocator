#include "heap.h"

void* array[10] = {0};

int main(void)
{
  for (int i = 0; i < 10; i++) {
    array[i] = heap_alloc(i);
    //printf("ptr = %p\n", array[i]);
    heap_free(array[i]);
  }
  heap_alloc(10);
  chunk_list_dump(&allocated_chunks);
  chunk_list_dump(&freed_chunks);
  return EXIT_SUCCESS;
}
