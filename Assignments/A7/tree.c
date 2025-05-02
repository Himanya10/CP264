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
#include "queue_stack.h"
#include "tree.h"

TPROPS tree_property(TNODE *root)
{
    // your code
    TPROPS r = {0};

    if (root)
    {
        // Use Recursion to get the height and order of the tree
        TPROPS left = tree_property(root->left);
        TPROPS right = tree_property(root->right);

        // Total order is the sum of the left and right order plus 1
        r.order = 1 + left.order + right.order;

        // Height = Heighest Tree + 1
        r.height = 1 + (left.height > right.height ? left.height : right.height);
    }

    return r;
}

// The order for pre-order will be root -> left -> right
void preorder(TNODE *root)
{
    // your code
    if (root)
    {
        printf("%c ", root->data);

        // use recursion to get the left and right order
        preorder(root->left);
        preorder(root->right);
    }
    else
    {
        return;
    }
}

// Order: Left -> root -> Right
void inorder(TNODE *root)
{
    // your code
    if (root)
    {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
    else
    {
        return;
    }
}

// Order: Left -> Right -> Root
void postorder(TNODE *root)
{
    // your code
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
    else
    {
        return;
    }
}

// 广度优先遍历
void bforder(TNODE *root)
{
    // your code
    if (root)
    {
        QUEUE q = {NULL, NULL};
        // Enqueue the root node
        enqueue(&q, root);

        while (q.front)
        {
            // get the front node and print it out
            TNODE *current = dequeue(&q);
            printf("%c ", current->data);

            // if this tree got children, enqueue them
            if (current->left)
            {
                enqueue(&q, current->left);
            }
            if (current->right)
            {
                enqueue(&q, current->right);
            }
        }
    }
    else
    {
        return;
    }
}

// 广度优先搜索
TNODE *bfs(TNODE *root, char val)
{
    // your code
    TNODE *r = NULL;
    if (root)
    {
        QUEUE q = {0};
        enqueue(&q, root);

        while (q.front)
        {
            TNODE *current = (TNODE *)dequeue(&q);

            // Start to seartch the value
            if (current->data == val)
            {
                r = current;
                break;
            }

            // Otherwise keep searching
            if (current->left)
            {
                enqueue(&q, current->left);
            }
            if (current->right)
            {
                enqueue(&q, current->right);
            }
        }
        clean_queue(&q);
    }
    return r;
}

// 深度优先搜索
TNODE *dfs(TNODE *root, char val)
{
    // your code
    TNODE *r = NULL;
    if (root)
    {
        // different from BFS, DFS uses stack to store the data
        STACK s = {0};
        push(&s, root);

        while (s.top)
        {
            TNODE *current = (TNODE *)pop(&s);

            // Start to seartch the value
            if (current->data == val)
            {
                r = current;
            }

            // Otherwise keep searching
            if (current->right)
            {
                push(&s, current->right);
            }
            if (current->left)
            {
                push(&s, current->left);
            }
        }
        clean_stack(&s);
    }
    return r;
}

TNODE *tree_node(char val)
{
    TNODE *np = (TNODE *)malloc(sizeof(TNODE));
    if (np != NULL)
    {
        np->data = val;
        np->left = NULL;
        np->right = NULL;
    }
    return np;
}

void clean_tree(TNODE **rootp)
{
    TNODE *p = *rootp;
    if (p)
    {
        if (p->left)
            clean_tree(&p->left);
        if (p->right)
            clean_tree(&p->right);
        free(p);
    }
    *rootp = NULL;
}

void insert_tree(TNODE **rootp, char val)
{
    if (*rootp == NULL)
    {
        *rootp = tree_node(val);
    }
    else
    {
        QUEUE queue = {0};
        TNODE *p;
        enqueue(&queue, *rootp);
        while (queue.front)
        {
            p = dequeue(&queue);
            if (p->left == NULL)
            {
                p->left = tree_node(val);
                break;
            }
            else
            {
                enqueue(&queue, p->left);
            }

            if (p->right == NULL)
            {
                p->right = tree_node(val);
                break;
            }
            else
            {
                enqueue(&queue, p->right);
            }
        }
    }
}
