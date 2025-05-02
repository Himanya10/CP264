/**
 * -------------------------------------
 * @file  set_avl.h
 * file description
 * -------------------------------------
 * @author Himanya Verma, 1690511154, verm1154@mylaurier
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#ifndef SET_AVL_H
#define SET_AVL_H

#include "avl.h"

typedef struct
{
    int size;
    AVLNODE *root;
} SET;

/**
 * returns the number of elements in the set
 */
int set_size(SET *s);

/**
 * Returns 1 it set s contains element e; otherwise 0.
 */
int set_contain(SET *s, char *e);

/**
 * Add element e into set s.
 */
void set_add(SET *s, char *e);

/**
 * Remove  element e into set s
 */
void set_remove(SET *s, char *e);

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(SET *s);

#endif