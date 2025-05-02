/*
--------------------------------------------------
Project: a1q1
File:    mychar.c
Author:  Himanya Verma
Version: 2025-01-14
--------------------------------------------------
*/

#include "mychar.h"

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}


int mytype(char c) {
    if (is_digit(c)) {
        return 0; 
    } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 4; 
    } else if (c == '+' || c == '-') {
        return 1; 
    } else if (c == '(') {
        return 2; 
    } else if (c == ')') {
        return 3; 
    } else {
        return -1; 
    }
}

char case_flip(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); 
    } else if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A'); 
    }
    return c; 
}

int digit_to_int(char c) {
    if (is_digit(c)) {
        return c - '0';
    }
    return -1; 
}









