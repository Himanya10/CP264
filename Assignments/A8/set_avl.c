/**
 * -------------------------------------
 * @file  set_avl.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 1690511154, verm1154@mylaurier
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#include "string.h"
#include "avl.h"
#include "set_avl.h"

int set_size(SET *s)
{
    // your code
    if (s == NULL)
    {
        return 0;
    }

    return s->size;
}

int set_contain(SET *s, char *e)
{
    // your code
    if (s == NULL || e == NULL)
    {
        return 0;
    }

    RECORD data;
    strncpy(data.name, e, 20);
    // adjust the score
    data.score = 0.0;

    AVLNODE *node = avl_search(s->root, data.name);

    return (node != NULL);
}

void set_add(SET *s, char *e)
{
    // your code
    if (s == NULL || e == NULL)
    {
        return;
    }

    RECORD data;
    strncpy(data.name, e, 20);

    data.score = 0.0;

    if (!set_contain(s, e))
    {
        avl_insert(&s->root, data);
        s->size++;
    }
}

void set_remove(SET *s, char *e)
{
    // your code
    if (s == NULL || e == NULL)
    {
        return;
    }

    RECORD data;
    strncpy(data.name, e, sizeof(data.name));
    data.score = 0.0;

    if (set_contain(s, e))
    {
        avl_delete(&s->root, data.name);
        s->size--;
    }
}

void set_clean(SET *s)
{
    // your code
    if (s == NULL)
    {
        return;
    }

    avl_clean(&s->root);
    s->size = 0;
}