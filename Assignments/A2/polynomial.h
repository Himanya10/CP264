/*
--------------------------------------------------
Project: a2q2
File:    polynomial.h
Author:  Himanya Verma
Version: 2025-01-21
--------------------------------------------------
*/

#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <stdbool.h>

float horner(float *p, int n, float x);
void derivative(float *p, float *d, int n);
float newton(float *p, int n, float x0);

#endif 