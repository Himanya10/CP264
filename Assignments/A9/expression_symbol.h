/**
 * -------------------------------------
 * @file  expression_symbol.h
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#ifndef EXPRESSION_SYMBOL_H
#define EXPRESSION_SYMBOL_H

#include "common_queue_stack.h"
#include "hash.h"

/* Convert symbolic infix expression string to postfix expression in QUEUE type
 * @param ht - pointer to a HASHTABLE
 * @param infixstr - pointer to string of infix expression
 * @return - postfix exprssion in QUEUE type
 */
QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr);

/* Evaluate symbolic infix expression string.
 * @param ht - pointer to a HASHTABLE
 * @param infixstr - pointer to string of infix expression
 * @return  - the value of the infix expression.
 */
int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr);

/* Evaluate postfix expression.
 * @param queue - postfix queue
 * @return  - the value of the postfix exprssion.
 */
int evaluate_postfix(QUEUE queue);

/* Evaluate statement like b = (a+3)*2;
 * @param ht - pointer to a HASHTABLE to resolve the value of symbols on the right side.
 * @return  - symbol on the left side and its value in DATA type.
 */
DATA evaluate_statement(HASHTABLE *ht, char *statement);

#endif