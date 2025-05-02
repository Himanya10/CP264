/**
 * -------------------------------------
 * @file  heap.h
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, verm1154@mylaurier.ca
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b)
{
    int r = 0;
    if (a < b)
        r = -1;
    else if (a > b)
        r = 1;
    return r;
}

HEAP *new_heap(int capacity)
{
    HEAP *hp = (HEAP *)malloc(sizeof(HEAP));
    if (hp == NULL)
        return NULL;
    hp->hda = (HEAPDATA *)malloc(sizeof(HEAPDATA) * capacity);
    if (hp->hda == NULL)
    {
        free(hp);
        return NULL;
    };
    hp->capacity = capacity;
    hp->size = 0;
    return hp;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index)
{
    // your code
    if (index == 0)
    {
        return index;
    }

    // calculate the parent index
    int parent = (index - 1) / 2;

    // compare the parent and child
    if (cmp(hda[parent].key, hda[index].key) > 0)
    {
        HEAPDATA temp = hda[parent];
        hda[parent] = hda[index];
        hda[index] = temp;
        return heapify_up(hda, parent);
    }

    return index;
}

// you may add this function to be used other functions.
int heapify_down(HEAPDATA *hda, int n, int index)
{
    // your code
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && cmp(hda[left].key, hda[smallest].key) < 0)
    {
        smallest = left;
    }

    if (right < n && cmp(hda[right].key, hda[smallest].key) < 0)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        // swap
        HEAPDATA temp = hda[index];
        hda[index] = hda[smallest];
        hda[smallest] = temp;
        return heapify_down(hda, n, smallest);
    }

    return index;
}

void heap_insert(HEAP *heap, HEAPDATA new_node)
{
    // your code
    if (heap->size == heap->capacity)
    {
        // expand data array by doubling its length
        int new_capacity = heap->capacity * 2;
        HEAPDATA *new_hda = (HEAPDATA *)realloc(heap->hda, sizeof(HEAPDATA) * new_capacity);

        if (new_hda == NULL)
        {
            return;
        }

        heap->hda = new_hda;
        heap->capacity = new_capacity;
    }

    heap->hda[heap->size] = new_node;
    heap->size++;
    heapify_up(heap->hda, heap->size - 1);
}

HEAPDATA heap_find_min(HEAP *heap)
{
    // your code
    if (heap->size == 0)
    {
        return (HEAPDATA){0, 0};
    }

    return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap)
{
    // your code
    if (heap->size == 0)
    {
        return (HEAPDATA){0, 0};
    }

    HEAPDATA min = heap->hda[0];
    heap->hda[0] = heap->hda[heap->size - 1];
    heap->size--;

    heapify_down(heap->hda, heap->size, 0);

    if (heap->size <= heap->capacity / 4 && heap->capacity > 4)
    {
        int new_capacity = heap->capacity / 2;
        HEAPDATA *new_hda = (HEAPDATA *)realloc(heap->hda, sizeof(HEAPDATA) * new_capacity);

        if (new_hda == NULL)
        {
            return min;
        }
        heap->hda = new_hda;
        heap->capacity = new_capacity;
    }

    return min;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key)
{
    // your code
    if (index < 0 || index >= heap->size)
    {
        return -1;
    }

    // change the key
    KEYTYPE old_key = heap->hda[index].key;
    heap->hda[index].key = new_key;

    if (cmp(new_key, old_key) < 0)
    {
        return heapify_up(heap->hda, index);
    }
    else if (cmp(new_key, old_key) > 0)
    {
        return heapify_down(heap->hda, heap->size, index);
    }

    return index;
}

int heap_search_value(HEAP *heap, VALUETYPE data)
{
    // your code
    // easy traversal
    for (int i = 0; i < heap->size; i++)
    {
        if (heap->hda[i].value == data)
        {
            return i;
        }
    }

    return -1;
}

void heap_sort(HEAPDATA *arr, int n)
{
    // your code
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify_down(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        // mov root to the end
        HEAPDATA temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify_down(arr, i, 0);
    }
}

void heap_clean(HEAP **heapp)
{
    if (heapp)
    {
        HEAP *heap = *heapp;
        if (heap->capacity > 0)
        {
            heap->capacity = 0;
            heap->size = 0;
            free(heap->hda);
            free(heap);
        }
        *heapp = NULL;
    }
}