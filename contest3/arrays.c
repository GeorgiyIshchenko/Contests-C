#include "stdio.h"

void print_arr(int a[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}