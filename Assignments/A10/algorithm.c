/**
 * -------------------------------------
 * @file  algorithm.c
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
#include "heap.h"
#include "algorithm.h"

EDGELIST *mst_prim(GRAPH *g, int start)
{
    // your code
    if (g == NULL)
    {
        return NULL;
    }

    int n = g->order;
    int T[n];
    int parent[n];

    for (int i = 0; i < n; i++)
    {
        T[i] = 0;
        parent[i] = -1;
    }

    // initalize
    HEAP *h = new_heap(n);
    T[start] = 1;
    ADJNODE *temp = g->nodes[start]->neighbor;

    // gradually push all the nodes into the heap
    while (temp != NULL)
    {
        HEAPDATA hn;
        hn.key = temp->weight;
        hn.value = temp->nid;
        heap_insert(h, hn);
        parent[temp->nid] = start;
        temp = temp->next;
    }

    // reate mst by repeatedly extracting the minimum weight edge
    EDGELIST *mst = new_edgelist();
    while (h->size > 0)
    {
        HEAPDATA hn = heap_extract_min(h);
        int i = hn.value;

        if (T[i] == 1)
        {
            // if the node is already in the tree, skip it
            continue;
        }

        T[i] = 1;
        insert_edge_end(mst, parent[i], i, hn.key);

        temp = g->nodes[i]->neighbor;
        while (temp != NULL)
        {
            int neighbor_id = temp->nid;

            if (T[neighbor_id] == 0)
            {
                int heap_index = heap_search_value(h, neighbor_id);

                // if the node is already in the heap, and it smaller, update its key
                if (heap_index >= 0)
                {
                    if (temp->weight < h->hda[heap_index].key)
                    {
                        heap_change_key(h, heap_index, temp->weight);
                        parent[neighbor_id] = i;
                    }
                }
                else
                {
                    // if the node is not in the heap, insert it
                    HEAPDATA new_hn;
                    new_hn.key = temp->weight;
                    new_hn.value = neighbor_id;
                    heap_insert(h, new_hn);
                    parent[neighbor_id] = i;
                }
            }
            temp = temp->next;
        }
    }

    heap_clean(&h);
    return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start)
{
    // your code
    if (g == NULL)
    {
        return NULL;
    }

    int n = g->order;
    int T[n];
    int parent[n];
    int label[n];
    for (int i = 0; i < n; i++)
    {
        T[i] = 0;
        parent[i] = -1;
        label[i] = INFINITY;
    }

    // INitialize the heap
    HEAP *h = new_heap(n);
    label[start] = 0;
    T[start] = 1;
    ADJNODE *temp = g->nodes[start]->neighbor;

    while (temp != NULL)
    {
        HEAPDATA hn;
        hn.key = label[start] + temp->weight;
        hn.value = temp->nid;
        //
        heap_insert(h, hn);
        parent[temp->nid] = start;
        temp = temp->next;
    }

    EDGELIST *spt = new_edgelist();

    // Create Dijkstra loop
    while (h->size > 0)
    {
        HEAPDATA hn;
        hn = heap_extract_min(h);
        int u = hn.value;

        if (T[u] == 1)
        {
            continue;
        }

        T[u] = 1;
        label[u] = hn.key;
        insert_edge_end(spt, parent[u], u, label[u] - label[parent[u]]);

        temp = g->nodes[u]->neighbor;
        while (temp != NULL)
        {
            int v = temp->nid;
            if (T[v] == 0)
            {
                int new_dist = label[u] + temp->weight;
                int heapindex = heap_search_value(h, v);
                if (heapindex >= 0)
                {
                    if (new_dist < h->hda[heapindex].key)
                    {
                        heap_change_key(h, heapindex, new_dist);
                        parent[v] = u;
                    }
                }
                else
                {
                    HEAPDATA new_hn;
                    new_hn.key = new_dist;
                    new_hn.value = v;
                    heap_insert(h, new_hn);
                    parent[v] = u;
                }
            }
            temp = temp->next;
        }
    }

    heap_clean(&h);
    return spt;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end)
{
    // your code
    if (g == NULL || start < 0 || start >= g->order || end < 0 || end >= g->order)
    {
        return NULL;
    }

    int n = g->order;
    int T[n];
    int parent[n];
    int label[n];

    // Initialize arrays
    for (int i = 0; i < n; i++)
    {
        T[i] = 0;
        parent[i] = -1;
        label[i] = INFINITY;
    }

    HEAP *h = new_heap(n);
    label[start] = 0;
    T[start] = 1;
    ADJNODE *temp = g->nodes[start]->neighbor;

    // Insert neighbors of the start node into the heap
    while (temp != NULL)
    {
        HEAPDATA hn;
        hn.key = temp->weight;
        hn.value = temp->nid;
        heap_insert(h, hn);
        parent[temp->nid] = start;
        temp = temp->next;
    }

    // Stop when the destination node is reached
    while (h->size > 0)
    {
        HEAPDATA hn = heap_extract_min(h);
        int u = hn.value;

        // If the node is already in the tree, skip it
        if (T[u] == 1)
        {
            continue;
        }

        T[u] = 1;
        label[u] = hn.key;

        if (u == end)
        {
            break;
        }

        // Update distances for neighbors
        temp = g->nodes[u]->neighbor;
        while (temp != NULL)
        {
            int v = temp->nid;
            if (T[v] == 0) // If the neighbor is not visited
            {
                int new_dist = label[u] + temp->weight;
                int heap_index = heap_search_value(h, v);

                // If the node is already in the heap and the new distance is smaller, update its key
                if (heap_index >= 0)
                {
                    if (new_dist < h->hda[heap_index].key)
                    {
                        heap_change_key(h, heap_index, new_dist);
                        parent[v] = u;
                    }
                }
                else
                {
                    HEAPDATA new_hn;
                    new_hn.key = new_dist;
                    new_hn.value = v;
                    heap_insert(h, new_hn);
                    parent[v] = u;
                }
            }
            temp = temp->next;
        }
    }

    // Backtrack to construct the shortest path
    EDGELIST *sp = new_edgelist();
    int i = end;

    while (1)
    {
        if (i == start)
        {
            break;
        }

        insert_edge_start(sp, parent[i], i, label[i] - label[parent[i]]);
        i = parent[i];
    }

    heap_clean(&h);
    return sp;
}