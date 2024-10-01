#ifndef HEAP_H
#define HEAP_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

/* Defines*/
#define HEAP_CAPACITY_BYTES   524288 //The Heap capacity in bytes 512kb

/**
 * @brief Allocates a block of memory from the heap.
 * 
 * This function allocates a block of memory of the specified size from the heap.
 * The allocated memory is not initialized and must be cast to the appropriate
 * type by the caller.
 * 
 * @param size Size in bytes of the memory block to be allocated.
 * 
 * @return A pointer to the allocated memory block. Returns `NULL` if the allocation
 *         fails (e.g., if there is not enough memory available in the heap). 
 */
void* heap_alloc(size_t size);

/**
 * @brief Frees a previously allocated block of memory.
 * 
 * This function frees a block of memory that was previously allocated using
 * `heap_alloc()`. The memory block is returned to the heap and can be reused
 * for future allocations.
 * 
 * @param ptr Pointer to the memory block to be freed. If `ptr` is `NULL`, no action is taken. 
 */
void heap_free(void* ptr);
#endif //HEAP_H!
