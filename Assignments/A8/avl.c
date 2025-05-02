/**
 * -------------------------------------
 * @file  avl.c
 * file description
 * -------------------------------------
 * @author Himanya Verma, 1690511154, verm1154@mylaurier
 *
 * @version 2025-02-28
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

AVLNODE *avl_node(RECORD data)
{
    AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
    if (np)
    {
        np->data = data;
        np->height = 1;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(AVLNODE *np)
{
    // your code
    if (np == NULL)
    {
        return 0;
    }

    return np->height;
}

int balance_factor(AVLNODE *np)
{
    // your code
    if (np == NULL)
    {
        return 0;
    }

    return height(np->left) - height(np->right);
}

AVLNODE *rotate_left(AVLNODE *np)
{
    // your code
    if (np == NULL || np->right == NULL)
    {
        return np;
    }

    // right rotation
    AVLNODE *current = np->right;
    np->right = current->left;
    current->left = np;

    // Update heights
    np->height = max(height(np->left), height(np->right)) + 1;
    current->height = max(height(current->left), height(current->right)) + 1;

    return current;
}

AVLNODE *rotate_right(AVLNODE *root)
{
    // your code
    if (root == NULL || root->left == NULL)
    {
        return root;
    }

    // Vice versa
    AVLNODE *current = root->left;
    root->left = current->right;
    current->right = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    current->height = max(height(current->left), height(current->right)) + 1;

    return current;
}

AVLNODE *extract_smallest_node(AVLNODE **rootp)
{
    AVLNODE *p = *rootp, *parent = NULL;
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

void avl_insert(AVLNODE **rootp, RECORD data)
{
    // 1. Perform the normal BST insertion
    if (*rootp == NULL)
    {
        AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
        if (np)
        {
            np->data = data;
            np->height = 1;
            np->left = NULL;
            np->right = NULL;
        }
        *rootp = np;
    }
    else
    {

        AVLNODE *root = *rootp;

        if (strcmp(data.name, root->data.name) == 0)
            return;
        else if (strcmp(data.name, root->data.name) < 0)
        {
            avl_insert(&root->left, data);
        }
        else
        {
            avl_insert(&root->right, data);
        }

        // 2. update height of this ancestor node
        root->height = max(height(root->left), height(root->right)) + 1;

        // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = balance_factor(root);

        // 4. rebalance if not balanced
        if (balance > 1)
        {
            if (balance_factor(root->left) >= 0)
            { // LL case
                *rootp = rotate_right(root);
            }
            else
            { // LR case
                root->left = rotate_left(root->left);
                *rootp = rotate_right(root);
            }
        }
        else if (balance < -1)
        {
            if (balance_factor(root->right) <= 0)
            { // RR case
                *rootp = rotate_left(root);
            }
            else
            { // RL case
                root->right = rotate_right(root->right);
                *rootp = rotate_left(root);
            }
        }
    }
}

void avl_delete(AVLNODE **rootp, char *name)
{
    AVLNODE *root = *rootp;
    AVLNODE *np;
    if (root == NULL)
        return;

    if (strcmp(name, root->data.name) == 0)
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            *rootp = NULL;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            np = root->left;
            free(root);
            *rootp = np;
        }
        else if (root->left == NULL && root->right != NULL)
        {
            np = root->right;
            free(root);
            *rootp = np;
        }
        else if (root->left != NULL && root->right != NULL)
        {
            np = extract_smallest_node(&root->right);
            np->left = root->left;
            np->right = root->right;
            free(root);
            *rootp = np;

            (*rootp)->height = max(height((*rootp)->left), height((*rootp)->right)) + 1;
        }
    }
    else
    {
        if (strcmp(name, root->data.name) < 0)
        {
            avl_delete(&root->left, name);
        }
        else
        {
            avl_delete(&root->right, name);
        }
    }

    // If the tree had only one node then return
    if (*rootp == NULL)
        return;
    root = *rootp;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE
    int balance = balance_factor(root);

    // STEP 4: rebalance if not balanced
    if (balance > 1)
    {
        if (balance_factor(root->left) >= 0)
        { // LL
            *rootp = rotate_right(root);
        }
        else
        { // LR
            root->left = rotate_left(root->left);
            *rootp = rotate_right(root);
        }
    }
    else if (balance < -1)
    {
        if (balance_factor(root->right) <= 0)
        { // RR
            *rootp = rotate_left(root);
        }
        else
        { // RL
            root->right = rotate_right(root->right);
            *rootp = rotate_left(root);
        }
    }
}

AVLNODE *avl_search(AVLNODE *root, char *name)
{
    // your code
    if (root == NULL)
    {
        return NULL;
    }

    // compare the value to see which direction to go
    int cmp = strcmp(name, root->data.name);

    if (cmp == 0)
    {
        // got it!
        return root;
    }
    else if (cmp < 0)
    {
        // recursive to the left until hit the base;
        return avl_search(root->left, name);
    }
    else
    {
        // to the right
        return avl_search(root->right, name);
    }
}

void avl_clean(AVLNODE **rootp)
{
    AVLNODE *root = *rootp;
    if (root)
    {
        if (root->left)
            avl_clean(&root->left);
        if (root->right)
            avl_clean(&root->right);
        free(root);
    }
    *rootp = NULL;
}