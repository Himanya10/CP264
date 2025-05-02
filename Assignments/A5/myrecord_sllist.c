/**
 * -------------------------------------
 * @file  myrecord_sllist.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-02-13
 *
 * -------------------------------------
 */

#include "myrecord_sllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


NODE *sll_search(SLL *sllp, char *name){
    
    NODE *r = NULL;
    NODE *np = sllp->start;

    while(np != NULL){
        if(strcmp(np->data.name, name) == 0){
            r = np;
            break;
        } else{
            np = np->next;
        }
    }

    return r;
}

void sll_insert(SLL *sllp, char *name, float score){

    if (sllp == NULL) {
        return;
    }

    NODE *np = (NODE *)malloc(sizeof(NODE));
    if (np == NULL) {
        return;
    }
    strncpy(np->data.name, name, sizeof(np->data.name) - 1);
    np->data.score = score;
    np->next = NULL;

    if (sllp->start == NULL) {
        sllp->start = np;
    } else {

        NODE *prev = NULL;
        NODE *current = sllp->start;


        while (current != NULL && strcmp(current->data.name, name) < 0) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            np->next = sllp->start;
            sllp->start = np;
        } else {
            np->next = current;
            prev->next = np;
        }
    }

    sllp->length++;
    
}

int sll_delete(SLL *sllp,  char *name){

    if(sllp == NULL || sllp->start == NULL){
        return 0;
    }

    NODE *prev = NULL;
    NODE *current = sllp->start;

    while(current != NULL){
        if(strcmp(current->data.name, name) == 0){

            if(prev == NULL){
                sllp->start = current->next;
            } else{

                prev->next = current->next;
            }

            free(current);
            sllp->length--;
            return 1;
        }

        prev = current;
        current = current->next;
    }

    return 0;

}

void sll_clean(SLL *sllp){

    if(sllp == NULL || sllp->start == NULL){
        return;
    }

    NODE *temp, *ptr = sllp->start;

    while(ptr != NULL){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    sllp->start = NULL;
    sllp->length = 0;

}