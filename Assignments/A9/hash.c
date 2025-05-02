/**
 * -------------------------------------
 * @file  hash.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HNODE *hashtable_search(HASHTABLE *ht, char *name)
{
    
    if (!ht || !name)
    {
        return NULL;
    }

    int index = hash(name, ht->size);
    HNODE *current = ht->hna[index];

    while (current)
    {
        if (strcmp(current->data.name, name) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

int hashtable_insert(HASHTABLE *ht, DATA data)
{
    if (!ht)
    {
        return 0;
    }

    int index = hash(data.name, ht->size);
    HNODE *current = ht->hna[index];

    while (current)
    {
        if (strcmp(current->data.name, data.name) == 0)
        {
            current->data.value = data.value;
            return 0;
        }

        current = current->next;
    }

    HNODE *new_node = (HNODE *)malloc(sizeof(HNODE));
    new_node->data = data;
    new_node->next = ht->hna[index];
    ht->hna[index] = new_node;

    ht->count++;
    return 1;
}

int hashtable_delete(HASHTABLE *ht, char *name)
{
    if (!ht || !name)
    {
        return 0;
    }

    int index = hash(name, ht->size);
    HNODE *current = ht->hna[index];
    HNODE *prev = NULL;

    while (current)
    {
        if (strcmp(current->data.name, name) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                ht->hna[index] = current->next;
            }

            free(current);
            ht->count--;
            return 1;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}

int hash(char *key, int size)
{
    unsigned int hash = 0;
    while (*key)
    {
        hash += *key++;
    }
    return hash % size;
}

HASHTABLE *new_hashtable(int size)
{
    HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    ht->hna = (HNODE **)malloc(sizeof(HNODE **) * size);
    int i;
    for (i = 0; i < size; i++)
        *(ht->hna + i) = NULL;

    ht->size = size;
    ht->count = 0;
    return ht;
}

void hashtable_clean(HASHTABLE **htp)
{
    if (*htp == NULL)
        return;
    HASHTABLE *ht = *htp;
    HNODE *p, *temp;
    int i;
    for (i = 0; i < ht->size; i++)
    {
        p = ht->hna[i];
        while (p)
        {
            temp = p;
            p = p->next;
            free(temp);
        }
        ht->hna[i] = NULL;
    }
    free(ht->hna);
    ht->hna = NULL;
    *htp = NULL;
}