#ifndef algo_sorting_h
#define algo_sorting_h


#include "../data.h"


typedef void (*swp_fn)(Value*,Value*);

void bubble_sort(Value *arr,int n, swp_fn swp);

#endif
