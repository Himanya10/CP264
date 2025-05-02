/*
--------------------------------------------------
Project: a1q3
File:    quadratic.c
Author:  Himanya Verma
Version: 2025-01-14
--------------------------------------------------
*/
#include "quadratic.h"
#include <math.h>

int solution_type(float a, float b, float c){
    if (a == 0){
        return 0;
    }

    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0){
        return 2;
    } else if(discriminant == 0){
        return 1;
    } else{
        return 3;
    }
}

float real_root_big(float a, float b, float c){
    if(solution_type(a,b,c) == 1){
        float root = -b / (2 * a);
        return root;
    }else if(solution_type(a,b,c) == 2){
        float sqrt_equation = sqrt(b * b - 4 * a * c);
        float x1 = (-b + sqrt_equation) / (2 * a);
        float x2 = (-b - sqrt_equation) / (2 * a);

        return (x1 > x2) ? x1 : x2;
    } else {
        return 0;
    }
}
float real_root_small(float a, float b, float c){
    if(solution_type(a,b,c) == 1){
        float root = -b / (2 * a);
        return root;
    }else if(solution_type(a,b,c) == 2){
        float sqrt_equation = sqrt(b * b - 4 * a * c);
        float x1 = (-b + sqrt_equation) / (2 * a);
        float x2 = (-b- sqrt_equation) / (2 * a);

        return (x1 < x2) ? x1 : x2;
    } else {
        return 0;
    }
}