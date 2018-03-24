#include <stdint.h>
#include <stddef.h>

#define CHUNK_USED 1
#define SIZE_MASK (~3)
#define ALIGN_UP(size) (((size) + 3) & SIZE_MASK)

struct chunk {
    uint32_t size;
    struct chunk *next;
};

struct chunk *free_list = NULL;

void init_malloc(void *area, uint32_t size){
    free_list = area;
    free_list->size = (size & SIZE_MASK);
    free_list->next = NULL;
}

void *malloc(size_t size){
    struct chunk *chunk = free_list;
    struct chunk **prev_ptr = &free_list;
    uint32_t rest_size;
    struct chunk *rest_chunk;
    void *result = NULL;

    size = ALIGN_UP(size) + sizeof(uint32_t);

    while(chunk){
        if(size <= chunk->size){
            rest_size = chunk->size - size;
            *prev_ptr = chunk->next;
            if(rest_size > sizeof(struct chunk)){
                chunk->size = size; 
                rest_chunk = (struct chunk *) &(((uint8_t *)&chunk)[size]);
                rest_chunk->size = rest_size;
                rest_chunk->next = chunk->next;
                *prev_ptr = rest_chunk;
            }
            chunk->size |= CHUNK_USED;
            result = &chunk->next;
            break;            
        }
        prev_ptr = &chunk->next;
        chunk = chunk->next;
    }

    return result;
}
