#include "sorting.h"
#include <stdio.h>
#include <stdbool.h>



void swap(Value *xp,Value *yp){
  Value temp = *xp;
  *xp = *yp;
  *yp = temp;
}
void bubble_sort(Value *arr,int n, swp_fn swp){
  int i,j;
  bool swapped;
  for(i = 0; i < n - 1;i++){
    swapped = false;
    for (j = 0; j < n - i - 1; j++){
      if (arr[j] > arr[j + 1]){
        swp(&arr[j],&arr[j+1]);
        swapped = true;
      }
    }
    if (!swapped){
      break;
    }
  }
}

