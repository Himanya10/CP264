/**
 * -------------------------------------
 * @file  expression.h
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
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

QUEUE infix_to_postfix(char *infixstr)
{
    char *p = infixstr;
    QUEUE queue = {0};
    STACK stack = {0};
    int sign = 1, num = 0;

    while (*p)
    {
        if (*p == '-' && (p == infixstr || *(p - 1) == '('))
        {
            sign = -1;
        }
        else if (mytype(*p) == 0)
        {
            num = *p - '0';
            while ((*(p + 1) >= '0' && *(p + 1) <= '9'))
            {
                num = num * 10 + *(p + 1) - '0';
                p++;
            }
            enqueue(&queue, new_node(sign * num, 0));
            sign = 1;
        }
        else if (mytype(*p) == 1)
        {
            while (stack.top && priority(stack.top->data) >= priority(*p))
            {
                enqueue(&queue, pop(&stack));
            }
            push(&stack, new_node(*p, 1));
        }
        else if (mytype(*p) == 2)
        {
            push(&stack, new_node(*p, 2));
        }
        else if (mytype(*p) == 3)
        {
            while (stack.top && stack.top->data != '(')
            {
                enqueue(&queue, pop(&stack));
            }
            if (stack.top)
            { // pop '(' but don't enqueue it
                pop(&stack);
            }
        }
        p++; // move to next character
    }

    while (stack.top)
    {
        enqueue(&queue, pop(&stack));
    }

    return queue;
}

int evaluate_postfix(QUEUE queue)
{
    NODE *p = queue.front;
    STACK stack = {0};
    int type = 0;
    while (p)
    {
        type = p->type;
        if (type == 0)
        {
            push(&stack, new_node(p->data, 0));
        }
        else if (type == 1)
        {
            int operator= p->data;
            NODE *operand2 = pop(&stack);
            if (operator== '+')
                stack.top->data = stack.top->data + operand2->data;
            else if (operator== '-')
                stack.top->data = stack.top->data - operand2->data;
            else if (operator== '*')
                stack.top->data = stack.top->data * operand2->data;
            else if (operator== '/')
                stack.top->data = stack.top->data / operand2->data;
            free(operand2);
        }
        p = p->next;
    }
    int result = stack.top->data;
    clean_stack(&stack);
    return result;
}

int evaluate_infix(char *infixstr)
{
    QUEUE postfixQueue = infix_to_postfix(infixstr);
    return evaluate_postfix(postfixQueue);
}