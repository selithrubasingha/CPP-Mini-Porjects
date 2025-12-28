#include <unistd.h>  // Required for sbrk
#include <stddef.h>  // Required for size_t (or use <stdlib.h>)

struct header_t {
    size_t size;
    unsigned is_free;
};
void *malloc(size_t size){
    void* block;

    //sbrk-> set pointer break ... increase heap size by "size" amount 
    block = sbrk(size);

    //void* is for type casting -1 into a void pointer
    if (block== (void*)-1) return NULL;

    return block ;
}