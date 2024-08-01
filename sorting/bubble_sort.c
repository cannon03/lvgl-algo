#include "../data.h"

#include <stdio.h>
#include <stdbool.h>

typedef void (*swp_fn)(Value*,Value*); 


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

int main(){
  Value data[] = {-2, 45, 0, 11, -9};

  int size = sizeof(data) / sizeof(data[0]);

  bubble_sort(data, size,swap);

  for (int i = 0 ;i < size;i++){
    printf("%.2f \n",data[i]);
  }
}
