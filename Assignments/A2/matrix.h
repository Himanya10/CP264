/*
--------------------------------------------------
Project: a2q3
File:    polynomial.h
Author:  Himanya Verma
Version: 2025-01-21
--------------------------------------------------
*/

#ifndef MATRIX
#define MATRIX

#include <stdbool.h>

float norm(float *v, int n);
float dot_product(float *v1, float *v2, int n);
void matrix_multiply_vector(float *m, float *v, float *vout, int n);
void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n);

#endif 