/*
--------------------------------------------------
Project: a2q1
File:    fibonacci.c
Author:  Himanya Verma
Version: 2025-01-21
--------------------------------------------------
*/
#include "fibonacci.h"

int iterative_fibonacci(int n){
    if(n <= 1){
        return n;
    }
    int a = 0;
    int b = 1;
    int temp;
    for (int i = 2; i <= n; i++){
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int recursive_fibonacci(int n){
    if(n <= 1){
        return n;
    }
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n-2);
}

int dpbu_fibonacci(int *f, int n){
if (n <= 1 ){
    return n;
}
f[0] = 0;
f[1] = 1;
for(int i = 2; i <= n; i++){
    f[i] = f[i-1] + f[i -2];
}
return f[n];
}

int dptd_fibonacci(int *f, int n){
    if(n <= 1){
        return n;
    }
    if(f[n] != -1){
        return f[n];
    }
    f[n] = dptd_fibonacci(f, n-1) + dpbu_fibonacci(f, n-2);
    return f[n];
}