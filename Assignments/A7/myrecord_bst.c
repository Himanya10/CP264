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
#include <math.h>
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record)
{
    // your code
    bst_insert(&ds->root, record);

    // update the stats
    ds->count++;

    // update mean value
    float delta_old = ds->mean;
    ds->mean = delta_old + (record.score - delta_old) / ds->count;

    // update stddev
    if (ds->count > 1)
    {
        ds->stddev = sqrt(((ds->stddev * ds->stddev * (ds->count - 1)) + (record.score - delta_old) * (record.score - ds->mean)) / ds->count);
    }
    else
    {
        ds->stddev = 0;
    }
}

void remove_record(BSTDS *ds, char *name)
{
    // your code
    // retreive the node that we want to remove
    BSTNODE *node = bst_search(ds->root, name);

    if (!node)
    {
        return;
    }

    // Save the value of the node that we want to remove
    float removed_value = node->data.score;

    // Remove
    bst_delete(&ds->root, name);
    ds->count--;

    if (ds->count == 0)
    {
        ds->mean = 0;
        ds->stddev = 0;
    }

    // Use Morris Traversal
    float sum = 0.0, sum_sq = 0.0;
    BSTNODE *current = ds->root, *pre = NULL;

    while (current)
    {
        if (!current->left)
        {
            // No left child, move to right child
            sum += current->data.score;
            sum_sq += current->data.score * current->data.score;
            current = current->right;
        }
        else
        {
            // the most right node of the left child
            pre = current->left;

            while (pre->right && pre->right != current)
            {
                pre = pre->right;
            }

            if (!pre->right)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = NULL;

                sum += current->data.score;
                sum_sq += current->data.score * current->data.score;
                current = current->right;
            }
        }
    }
    // Updated the newest information
    ds->mean = sum / ds->count;
    if (ds->count > 1)
    {
        float variance = (sum_sq - (sum * sum) / ds->count) / ds->count;
        ds->stddev = sqrt(variance);
    }
    else
    {
        ds->stddev = 0.0;
    }
}

void bstds_clean(BSTDS *ds)
{
    bst_clean(&ds->root);
    ds->count = 0;
    ds->mean = 0;
    ds->stddev = 0;
}