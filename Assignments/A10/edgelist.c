/**
 * -------------------------------------
 * @file  edgelist.c
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
#include "edgelist.h"

EDGELIST *new_edgelist()
{
    EDGELIST *tp = malloc(sizeof(EDGELIST));
    tp->size = 0;
    tp->start = NULL;
    tp->end = NULL;
    return tp;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight)
{
    // your code

    // Allocate a new node
    EDGENODE *new_node = malloc(sizeof(EDGENODE));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = NULL;

    // If the list is empty, set the start and end nodes to the new node
    if (g->start == NULL)
    {
        g->start = new_node;
        g->end = new_node;
    }
    // otherwise extend the new node to the end of the list
    else
    {
        g->end->next = new_node;
        g->end = new_node;
    }

    g->size++;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight)
{
    // your code;
    EDGENODE *new_node = malloc(sizeof(EDGENODE));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    // set the next node to the front node
    new_node->next = g->start;

    if (g->start == NULL)
    {
        g->end = new_node;
    }

    g->start = new_node;
    g->size++;
}

void delete_edge(EDGELIST *g, int from, int to)
{
    // your code

    // traversel the list
    EDGENODE *current = g->start;
    EDGENODE *prev = NULL;

    while (current != NULL)
    {
        // if the edge is found
        if (current->from == from && current->to == to)
        {
            if (prev == NULL)
            {
                g->start = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            if (current == g->end)
            {
                g->end = prev;
            }

            free(current);
            g->size--;
            return;
        }

        prev = current;
        current = current->next;
    }
}

int weight_edgelist(EDGELIST *g)
{
    // your code
    int total_weight = 0;
    EDGENODE *current = g->start;

    // loop through the edgelist and add it up
    while (current != NULL)
    {
        total_weight += current->weight;
        current = current->next;
    }

    return total_weight;
}

void clean_edgelist(EDGELIST **gp)
{
    EDGELIST *g = *gp;
    EDGENODE *temp, *p = g->start;
    while (p)
    {
        temp = p;
        p = p->next;
        free(temp);
    }
    free(g);
    *gp = NULL;
}

void display_edgelist(EDGELIST *g)
{
    if (g == NULL)
        return;
    printf("size %d ", g->size);
    printf("(from to weight) ");
    EDGENODE *p = g->start;
    while (p)
    {
        printf("(%d %d %d) ", p->from, p->to, p->weight);
        p = p->next;
    }
}