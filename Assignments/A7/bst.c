/**
 * -------------------------------------
 * @file  myrecord_bst.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 169051154, Verm1154@mylaurier.ca
 *
 * @version 2025-03-04
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

BSTNODE *bst_node(RECORD data);
BSTNODE *extract_smallest_node(BSTNODE **rootp);

BSTNODE *bst_search(BSTNODE *root, char *key)
{
    // your code
    while (root)
    {
        // compare the key with the current node's key
        int cmp = strcmp(key, root->data.name);

        if (cmp == 0)
        {
            return root;
        }
        else if (cmp < 0)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    return NULL;
}

void bst_insert(BSTNODE **rootp, RECORD data)
{
    // your code
    BSTNODE *new_node = bst_node(data);

    if (!new_node)
    {
        return;
    }

    BSTNODE **curr = rootp;

    // CHeck if the data already exists
    while (*curr)
    {
        int cmp = strcmp(data.name, (*curr)->data.name);
        if (cmp < 0)
        {
            curr = &(*curr)->left;
        }
        else if (cmp > 0)
        {
            curr = &(*curr)->right;
        }
        else
        {
            return;
        }
    }
    *curr = new_node;
}

void bst_delete(BSTNODE **rootp, char *key)
{
    // your code
    BSTNODE *root = *rootp;

    if (!root)
    {
        return;
    }

    int cmp = strcmp(key, root->data.name);

    // Search for the key
    if (cmp < 0)
    {
        bst_delete(&root->left, key);
    }
    else if (cmp > 0)
    {
        bst_delete(&root->right, key);
    }
    else
    {
        // If the node has two children
        if (root->left && root->right)
        {
            BSTNODE *smallest = extract_smallest_node(&root->right);
            memcpy(&root->data, &smallest->data, sizeof(BSTNODE)); // copy the data
            free(smallest);
        }
        // Single child
        else
        {
            BSTNODE *temp = root;
            *rootp = root->left ? root->left : root->right;
            free(temp);
        }
    }
}

BSTNODE *bst_node(RECORD data)
{
    BSTNODE *np = (BSTNODE *)malloc(sizeof(BSTNODE));
    if (np)
    {
        memcpy(np, &data, sizeof(BSTNODE));
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void bst_clean(BSTNODE **rootp)
{
    BSTNODE *root = *rootp;
    if (root)
    {
        if (root->left)
            bst_clean(&root->left);
        if (root->right)
            bst_clean(&root->right);
        free(root);
    }
    *rootp = NULL;
}

BSTNODE *extract_smallest_node(BSTNODE **rootp)
{
    BSTNODE *p = *rootp, *parent = NULL;
    if (p)
    {
        while (p->left)
        {
            parent = p;
            p = p->left;
        }

        if (parent == NULL)
            *rootp = p->right;
        else
            parent->left = p->right;

        p->left = NULL;
        p->right = NULL;
    }

    return p;
}