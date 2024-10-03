#include "memory_manager.h"


struct memory_block{
    void* ptr;
    size_t size;
    int free;

    struct memory_block* next; // point to next block
};


static char* memory_pool = NULL; // will point to memory_pool later
static struct memory_block* first_block = NULL; // will point to



struct memory_block* make_block(void* ptr, size_t size, int free, struct memory_block* next){
    struct memory_block* new_block = (struct memory_block*)malloc(sizeof(struct memory_block));
    *new_block = (struct memory_block){ptr, size, free, next};

    return new_block;
};


void mem_init(size_t size){
    memory_pool = malloc(size); // allocate memory pool

    first_block = make_block(memory_pool, size, 1, NULL); // make header for first block pointing to the pool
};


void* mem_alloc(size_t size) {
    struct memory_block* current = first_block;
    // printf("new alloc\n");
    // printf("%zu\n", size);
    // Traverse through the list to find a suitable free block
    while (current != NULL) {
        // // printf("%zu\n", current->size);
        if (current->free && current->size >= size) {
            
            // Allocate the block by marking it as not free
            current->free = 0;
            
            struct memory_block* new_block = make_block((char*)current->ptr + size, current->size - size, 1, current->next);
            
            current->size = size;
            current->next = new_block;
            // // printf("success!\n");
            return current->ptr; // Return pointer to the data part
        
        }
        current = current->next;
    }
    // // printf("fail\n");
    return NULL;
}



void mem_free(void* block){
    struct memory_block* current = block;
    current->free = 1;
    free(current);
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
    first_block = NULL;
}


int main(){
    // mem_init(1024); // initialize 1 kb
    // void *block1 = mem_alloc(512);
    
    // void *block2 = mem_alloc(512);
    
};
