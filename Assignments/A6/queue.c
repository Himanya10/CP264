/**
 * -------------------------------------
 * @file  queue.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#include <stdio.h>
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np)
{
    if (!qp || !np)
        return;

    np->next = NULL;

    if (qp->rear)
    {
        qp->rear->next = np;
    }
    else
    {
        qp->front = np;
    }

    qp->rear = np;
    qp->length++;
}

NODE *dequeue(QUEUE *qp)
{
    if (!qp || !qp->front)
        return NULL;

    NODE *removed = qp->front;
    qp->front = qp->front->next;

    if (!qp->front)
    {
        qp->rear = NULL;
    }

    removed->next = NULL;
    qp->length--;

    return removed;
}

void clean_queue(QUEUE *qp)
{
    clean(&(qp->front));
    qp->front = NULL;
    qp->rear = NULL;
    qp->length = 0;
}
