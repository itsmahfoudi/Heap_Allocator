#include "heap.h"

void* array[10] = {0};

int main(void)
{ 
  chunk_list_dump(&allocated_chunks);
  chunk_list_dump(&freed_chunks);
  return EXIT_SUCCESS;
}
