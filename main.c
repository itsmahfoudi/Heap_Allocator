#include "heap.h"

int main(void)
{
  void* ptr = heap_alloc(12);
  heap_free(ptr);
  return EXIT_SUCCESS;
}
