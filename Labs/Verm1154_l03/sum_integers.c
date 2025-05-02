/**
 * -------------------------------------
 * @file  sum_integers.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm115@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_integers(void) {

    int sum = 0, num;

    printf("Enter integers, one per line:\n");
    while(scanf("%d", &num) == 1){
        sum += num;
    }
    return sum;
}