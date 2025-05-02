/*
--------------------------------------------------
Project: a1q2
File:    powersum.c
Author:  Himanya Verma
Version: 2025-01-14
--------------------------------------------------
*/
#include "powersum.h"

int power_overflow(int b, int n) {
    if (n == 0) return 0; 
    int result = 1;
    for (int i = 0; i < n; i++) {
        if (result > 0 && b > 0 && result > (2147483647 / b)) {
            return 1; 
        }
        result *= b;
    }
    return 0; 
}

int mypower(int b, int n) {
    if (n == 0) return 1; 
    if (n == 1) return b; 

    int result = 1;
    for (int i = 0; i < n; i++) {
        if (result > 0 && b > 0 && result > (2147483647 / b)) {
            return 0; 
        }
        result *= b;
    }
    return result;
}

int powersum(int b, int n){
    int sum = 0;

    for(int i = 0; i <= n; i++){
        int power = mypower(b, i);
        if(power == 0){
            return 0;
        }
        if(sum > (2147483647 - power)){
            return 0;
        }
        sum += power;
    }
    return sum;
}
