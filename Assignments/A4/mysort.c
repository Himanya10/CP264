/*
 --------------------------------------------------
 Project: a4q1
 File:    mysort.c
 Author:  Himanya Verma, 169051154, Verm1154@mylaurier.ca
 Version: 2025-02-06
 --------------------------------------------------
 */
#include "mysort.h"
#include <stdio.h>
#include <stdlib.h>

void select_sort(void *a[], int left, int right){
    for(int i = left; i < right; i++){
        int min_idx = i;
        for(int j = i + 1; j <= right; j++){
            if( *(int*)a[j] < *(int*)a[min_idx]){
                min_idx = j;
            }
        }
        if(min_idx != i){
            void *temp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = temp;
        }
    }
}

void quick_sort(void *a[], int left, int right){
      if(left >= right){
        return;
    }
    void *pivot = a[right];
    int i = left -1;
    for(int j = left; j < right; j++){
        if(*(int*)a[j] < *(int*)pivot){
            i++;
            void *temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    i++;
    void *temp = a[i];
    a[i] = a[right];
    a[right] = temp;

    quick_sort(a, left, i-1);
    quick_sort(a, i + 1, right);


}

void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*) ){
    if(right - left < 10){
        select_sort(a, left, right);
    } else{
        quick_sort(a, left, right);
    }
    for(int i = left, j = right; i < j; i++, j--){
        void *temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}