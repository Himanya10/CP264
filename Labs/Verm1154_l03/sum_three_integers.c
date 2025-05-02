/**
 * -------------------------------------
 * @file  functions.c
 * Lab 2 Functions Source Code File
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
#include <string.h>

int sum_three_integers(void) {
    int a, b, c;
    char input[100];

    while (1) {
        printf("Enter three comma-separated integers: ");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("The integers were not properly entered.\n");
            continue;
        }

        // Validate input format
        if (sscanf(input, "%d,%d,%d", &a, &b, &c) == 3) {
            return a + b + c;
        } else {
            printf("The integers were not properly entered.\n");
        }
    }
}
