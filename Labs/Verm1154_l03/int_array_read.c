/**
 * -------------------------------------
 * @file  int_array_read.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm115@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

void int_array_read(int *array, int size) {

    int i = 0, num;
    char extra;

    printf("Enter %d values for an array of int.\n", size);
    while(i < size){
        printf("Value for index %d: ", i);
        if (scanf("%d%c", &num, &extra) == 2 && (extra == '\n' || extra == ' ')){
            array[i++] = num;
        } else{
            printf("Not a valid integer\n");
            while(getchar() != '\n' );
        }
            
        }
    }
