/*
--------------------------------------------------
Project: a2q2
File:    polynomial.c
Author:  Himanya Verma
Version: 2025-01-21
--------------------------------------------------
*/
#include "polynomial.h"
#include <math.h>

float horner(float *p, int n, float x){
    float result = 0.0;
    for(int i = 0; i < n; i++){
        result = result * x + p[i];
    }
    return result;
}

void derivative(float *p, float *d, int n){
    for(int i = 0; i < n - 1; i++){
        d[i] = (n - 1 - i) * p[i];
    }
}
float newton(float *p, int n, float x0){
    float tolerance = 1e-6;
    int max_iter = 100;
    float d[n - 1];
    derivative(p, d, n);

    for(int i = 0; i < max_iter; i++){
        float fx = horner(p,n,x0);
        float dfx = horner(d, n - 1, x0);

        if(fabs(dfx) < tolerance){
            return x0;
        }
        if(dfx == 0){
            return x0;
        }

        float x1 = x0 - (fx / dfx);

        if(fabs(x1 - x0) < tolerance){
            return x1;
        }
        x0 = x1;
    }
    return x0;

}