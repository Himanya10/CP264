/**
 * -------------------------------------
 * @file  strings_with_substring.c
 * Lab 4 Source Code File
 * -------------------------------------
 * @author Himanya Verma, 169951154, Verm1154@mylaurier.ca 
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"
#include <ctype.h> 

const char* stristr(const char *str, const char *substr) {
    if (*substr == '\0') {
        return str; 
    }

    for (; *str != '\0'; str++) {
        const char *s = str;
        const char *t = substr;

        while (tolower(*s) == tolower(*t) && *t != '\0') {
            s++;
            t++;
        }

        if (*t == '\0') {
            return str; 
        }
    }
    return NULL; 
}

void strings_with_substring(strings_array *data, char *substr) {
    for (int i = 0; i < data->lines; i++) {
        if (stristr(data->strings[i], substr) != NULL) {
            printf("%s\n", data->strings[i]);
        }
    }
}