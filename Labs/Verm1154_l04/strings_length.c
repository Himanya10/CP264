/**
 * -------------------------------------
 * @file  strings_length.c
 * Lab 4 Source Code File
 * -------------------------------------
 * @author Himanya Verma, 169951154, Verm1154@mylaurier.ca 
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_length(strings_array *data, FILE *fp_short, FILE *fp_long, int length) {
    if (data == NULL || fp_short == NULL || fp_long == NULL) {
        return; // Ensure valid inputs
    }

    for (int i = 0; i < data->lines; i++) {
        if (data->strings[i] == NULL) {
            continue; // Skip NULL strings
        }

        if (strlen(data->strings[i]) < length) {
            fprintf(fp_short, "%s\n", data->strings[i]);
        } else {
            fprintf(fp_long, "%s\n", data->strings[i]);
        }
    }

}