#include "memory_manager.h"


struct memory_block{
    size_t size;
    int free;

    struct memory_block* next; // point to next block
};


static char* memory_pool = NULL; // will point to memory_pool later
static struct memory_block* block_list = NULL; // will point to


void mem_init(size_t size){
    memory_pool = (char*)malloc(size); // allocate memory pool

    block_list = (struct memory_block*)memory_pool; // point to beginning of memory pool, making one big memory block
    block_list->size = size - (sizeof(struct memory_block)); // set block size
    block_list->free = 1; // mark the block as free
    block_list->next = NULL; // next = NULL because there is no other block to point to yet
};


void* mem_alloc(size_t size){
    struct memory_block* current = block_list; // 
    
    while (current != NULL){
        if (current->free && current->size >= size + sizeof(struct memory_block)){ // if current block is free and big enough
            char* new_block_address = (char*)current + (sizeof(struct memory_block)); // calculate where the next free block should start
            struct memory_block* new_block = (struct block*)new_block_address; // point to new memory_block at end of last one

            new_block->size = current->size - size - sizeof(struct memory_block); // update new block stats
            new_block->free = 1;
            new_block->next = current->next;

            current->size = size; // update current block stats
            current->free = 0;
            current->next = new_block;

            return (void*)(current + 1); // returns address of current block + size of 1 memory_block struct
        }
        current = current->next; // moves the current pointer to the address of the next memory_block
    }
};


void mem_free(void* block){

    struct memory_block* current_block = (struct memory_block*)((char*)block - sizeof(struct memory_block)); // ptr to memory_block struct
    current_block->free = 1;
};


void* mem_resize(void* block, size_t size){
    if (block == NULL){
        return mem_alloc(size); // if no memory block, allocate new memory
    };

    struct memory_block* current_block = (struct memory_block*)((char*)block - sizeof(struct memory_block)); // ptr to memory_block struct

    if (current_block->size >= size){
        return block; // if current block is big enough, keep it
    };

    void* new_ptr = mem_alloc(size); // allocate new block with new size
    if (new_ptr != NULL){
        memcpy(new_ptr, block, current_block->size); // copy old block stats onto new one
        mem_free(block); // free old block
    }

    return new_ptr;
};


void mem_deinit(){ // free pool and maker pointers NULL
    free(memory_pool);
    memory_pool = NULL;
    block_list = NULL;
}


int main(){
    mem_init(1024); // initialize 1 kb
};
