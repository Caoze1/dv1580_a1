#include "memory_manager.h"


struct memory_block{
    void* ptr;
    size_t size;
    int free;

    struct memory_block* next; // point to next block
};


static char* memory_pool = NULL; // will point to memory_pool later
static struct memory_block* first_block = NULL; // will point to


struct memory_block* make_block(void* ptr, size_t size, int free, struct memory_block* next){ // makes a new block and room for its header
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

    while (current != NULL) {
        if (current->free && current->size >= size) {
            
            current->free = 0;
            
            struct memory_block* new_block = make_block((char*)current->ptr + size, current->size - size, 1, current->next);
            
            current->size = size;
            current->next = new_block;

            return current->ptr; // return pointer to the data part
        }
        current = current->next;
    }
    return NULL;
}


void mem_free(void* block){
    if (block == NULL){
        return;
    };

    struct memory_block* current = first_block;
    
    while (current != NULL){
        if (current->ptr == block){
            if (current->next != NULL && current->next->free == 1){
                struct memory_block* next = current->next;
                current->next = next->next;
                current->size += next->size;
            }
            current->free = 1;
            return;
        }
        current = current->next;
    }
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
