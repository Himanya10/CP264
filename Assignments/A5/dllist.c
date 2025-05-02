/**
 * -------------------------------------
 * @file  dllist.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-02-13
 *
 * -------------------------------------
 */
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>


NODE *dll_node(char value){

    NODE *np = (NODE *)malloc(sizeof(NODE));

    if(np == NULL){
        return NULL;
    }

    np->data = value;
    np->next = NULL;
    np->prev = NULL;

    return np;
}

void dll_insert_start(DLL *dllp, NODE *np){

    if (dllp == NULL || np == NULL) {
        return;
    }

    if(dllp->start == NULL){

        np->prev = NULL;
        np->next = NULL;
        dllp->start = np;
        dllp->end = np;

    } else{

        np->next = dllp->start;
        dllp->start->prev = np;
        dllp->start = np;
    }

    dllp->length++;
}

void dll_insert_end(DLL *dllp, NODE *np){
    
    if (dllp == NULL || np == NULL) {
        return;
    }

    if(dllp->end == NULL){

        dllp->start = np;
        dllp->end = np;
    } else{

        np->prev = dllp->end;
        dllp->end->next = np;
        dllp->end = np;

    }

    dllp->length++;
}

void dll_delete_start(DLL *dllp){

    if(dllp == NULL || dllp->start == NULL){
        return;
    }

    NODE *temp = dllp->start;

    if(dllp->start == dllp->end){

        dllp->start = NULL;
        dllp->end = NULL;

    } else{
        
        dllp->start = dllp->start->next;
        dllp->start->prev = NULL;
    }

    free(temp);
    dllp->length--;
}

void dll_delete_end(DLL *dllp){

    if(dllp == NULL || dllp->end == NULL){
        return;
    }

    NODE *temp = dllp->end;

    if(dllp->end == dllp->start){
        dllp->end = NULL;
        dllp->start = NULL;
    } else{
        dllp->end = dllp->end->prev;
        dllp->end->next = NULL;
    }

    free(temp);
    dllp->length--;
}

void dll_clean(DLL *dllp){

    if(dllp == NULL){
        return;
    }

    NODE *current = dllp->start;
    NODE *temp;

    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }

    dllp->start = NULL;
    dllp->end = NULL;
    dllp->length = 0;
}