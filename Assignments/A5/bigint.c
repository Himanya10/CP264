/**
 * -------------------------------------
 * @file  bigint.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-02-13
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

BIGINT bigint(char *digitstr){

    BIGINT bn = {0};
    if (digitstr == NULL) {
        return bn;
    } else if (!(*digitstr >= '0' && *digitstr <= '9')) { // not begin with digits
        return bn;
    } else if (*digitstr == '0' && *(digitstr + 1) == '\0') { // just "0"
        dll_insert_end(&bn, dll_node(*digitstr - '0'));
        return bn;
    } else {
        while (*digitstr) {
            if (*digitstr >= '0' && *digitstr <= '9') {
                dll_insert_end(&bn, dll_node(*digitstr - '0'));
            } else {
                dll_clean(&bn);
                break;
            }
            digitstr++;
        }
        return bn;
    }
}

BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2){

    BIGINT result = {0};
    NODE *p1 = oprand1.end;
    NODE *p2 = oprand2.end;
    int carry = 0;

    while(p1 != NULL || p2 != NULL || carry != 0){
        int sum = carry;

        if(p1 != NULL){
            sum += p1->data;
            p1 = p1->prev;
        }

        if(p2 != NULL){
            sum += p2->data;
            p2 = p2->prev;
        }

        dll_insert_start(&result, dll_node(sum % 10));
        carry = sum / 10;
    }

    return result;
}

BIGINT bigint_fibonacci(int n){
    
    BIGINT f1 = bigint("0");
    BIGINT f2 = bigint("1");
    BIGINT temp = bigint(NULL);

    if(n == 0) return f1;
    else if(n == 1) return f2;
    else{
        for(int i = 2; i <= n; i++){
            temp = bigint_add(f1, f2);
            f1 = f2;
            f2 = temp;
        }

        dll_clean(&f1);
        return temp;
    }
}