/**
 * -------------------------------------
 * @file  graph.c
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
#include "queue_stack.h"
#include "graph.h"

GRAPH *new_graph(int order)
{
    GRAPH *gp = malloc(sizeof(GRAPH));
    gp->nodes = malloc(order * sizeof(GNODE *));

    int i;
    for (i = 0; i < order; i++)
    {
        gp->nodes[i] = malloc(sizeof(GNODE));
        gp->nodes[i]->nid = i;
        strcpy(gp->nodes[i]->name, "null");
        gp->nodes[i]->neighbor = NULL;
    }

    gp->order = order;
    gp->size = 0;

    return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight)
{
    // your code
    // Check if the from and to nodes are within the graph
    if (from < 0 || from >= g->order || to < 0 || to >= g->order)
    {
        return;
    }

    ADJNODE *current = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    // Check if the edge already exists
    while (current != NULL)
    {
        if (current->nid == to)
        {
            current->weight = weight;
            return;
        }

        prev = current;
        current = current->next;
    }

    // if the edge is not exist then create a new edge
    ADJNODE *new_edge = (ADJNODE *)malloc(sizeof(ADJNODE));
    new_edge->nid = to;
    new_edge->weight = weight;
    new_edge->next = NULL;

    if (prev == NULL)
    {
        g->nodes[from]->neighbor = new_edge;
    }
    else
    {
        prev->next = new_edge;
    }

    g->size++;
}

void delete_edge_graph(GRAPH *g, int from, int to)
{
    // your code
    if (from < 0 || from >= g->order || to < 0 || to >= g->order)
    {
        return;
    }

    ADJNODE *current = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    while (current != NULL)
    {
        if (current->nid == to)
        {
            if (prev == NULL)
            {
                g->nodes[from]->neighbor = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            free(current);
            g->size--;
            return;
        }

        prev = current;
        current = current->next;
    }
}

int get_edge_weight(GRAPH *g, int from, int to)
{
    // your code
    if (from < 0 || from >= g->order || to < 0 || to >= g->order)
    {
        return INFINITY;
    }

    ADJNODE *current = g->nodes[from]->neighbor;

    while (current != NULL)
    {
        if (current->nid == to)
        {
            return current->weight;
        }
        current = current->next;
    }

    return INFINITY;
}

void traverse_bforder(GRAPH *g, int nid)
{
    // your code
    if (g == NULL)
    {
        return;
    }

    if (nid < 0 || nid >= g->order || g->nodes[nid] == NULL)
    {
        return;
    }

    int n = g->order, visited[n], i;

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    QUEUE queue = {0};
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;

    enqueue(&queue, g->nodes[nid]);
    visited[nid] = 1;
    while (queue.front != NULL)
    {
        gnp = (GNODE *)dequeue(&queue);
        printf("(%d %s) ", gnp->nid, gnp->name);

        // Traversal of adjacent nodes
        anp = gnp->neighbor;
        while (anp != NULL)
        {
            int neighbor_id = anp->nid;

            // If the node is not visited, then enqueue it
            if (!visited[neighbor_id])
            {
                visited[neighbor_id] = 1;
                enqueue(&queue, g->nodes[neighbor_id]);
            }
            anp = anp->next;
        }
    }
    clean_queue(&queue);
}

// Use auxiliary stack data structure for the algorithm
void traverse_dforder(GRAPH *g, int nid)
{
    // your code
    if (g == NULL)
    {
        return;
    }

    int visited[g->order];
    for (int i = 0; i < g->order; i++)
    {
        visited[i] = 0;
    }
    // A701
    STACK stack = {0};
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;
    push(&stack, g->nodes[nid]);
    visited[nid] = 1;

    while (stack.top != NULL)
    {
        gnp = (GNODE *)pop(&stack);
        printf("(%d %s) ", gnp->nid, gnp->name);

        // make sure all the nodes are reversed
        STACK temp_stack = {0};
        anp = gnp->neighbor;
        while (anp != NULL)
        {
            int neighbor_id = anp->nid;
            if (!visited[neighbor_id])
            {
                visited[neighbor_id] = 1;
                push(&temp_stack, g->nodes[neighbor_id]);
            }
            anp = anp->next;
        }

        // put back the temp nodes to the stack
        while (temp_stack.top != NULL)
        {
            GNODE *temp_node = (GNODE *)pop(&temp_stack);
            push(&stack, temp_node); // C - B - A
        }
    }

    clean_stack(&stack);
}

void clean_graph(GRAPH **gp)
{
    int i;
    GRAPH *g = *gp;
    ADJNODE *temp, *ptr;
    for (i = 0; i < g->order; i++)
    {
        ptr = g->nodes[i]->neighbor;
        while (ptr != NULL)
        {
            temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
        free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
    *gp = NULL;
}

void display_graph(GRAPH *g)
{
    if (g)
    {
        printf("order %d ", g->order);
        printf("size %d ", g->size);
        printf("(from to weight) ");
        int i;
        ADJNODE *ptr;
        for (i = 0; i < g->order; i++)
        {
            // printf("\n%d:", g->nodes[i]->nid);
            ptr = g->nodes[i]->neighbor;
            while (ptr != NULL)
            {
                printf("(%d %d %d) ", i, ptr->nid, ptr->weight);
                ptr = ptr->next;
            }
        }
    }
}