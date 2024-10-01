#ifndef HEAP_H
#define HEAP_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

/* Defines*/
#define HEAP_CAPACITY   524288 //The Heap capacity in bytes 512kb
#define CHUNK_LIST_CAP  8096

/**
 * @brief represents a memory chunk in the heap 
 */
typedef struct {
  void* start; //Start address of the memory block.
  size_t size; //Size of the memory block in bytes.
}Chunk;


/**
 * @brief Manages a list of memory chunks in the heap. 
 */
typedef struct {
  size_t count; // Number of chunks currently tracked
  Chunk chunks[CHUNK_LIST_CAP]; // Array of memory chunks
}Chunk_List;



/**
 * @brief Allocates a block of memory from the heap.
 * @param size Size in bytes of the memory block to be allocated.
 * 
 * @return A pointer to the allocated memory block. Returns `NULL` if the allocation
 *         fails (e.g., if there is not enough memory available in the heap). 
 */
void* heap_alloc(size_t size);

/**
 * @brief Frees a previously allocated block of memory. 
 * @param ptr Pointer to the memory block to be freed. If `ptr` is `NULL`, no action is taken. 
 */
void heap_free(void* ptr);

extern Chunk_List allocated_chunks;
extern Chunk_List freed_chunks;

int chunk_list_find(const Chunk_List* List, void* ptr);
void chunk_list_remove(Chunk_List* list, size_t index);
void chunk_list_insert(Chunk_List* list, void* start, size_t size);
void chunk_list_dump(const Chunk_List* list);
#endif //HEAP_H!
