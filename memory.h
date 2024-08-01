#ifndef algo_memory_h
#define algo_memory_h

#include <stdlib.h>

#define GROW_CAPACITY(capacity)\
((capacity) < 8 ? 8 : (capacity) * 2)

void* reallocate(void* pointer,size_t old_size,size_t new_size);


#endif
