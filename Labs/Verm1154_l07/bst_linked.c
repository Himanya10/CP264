/**
 * -------------------------------------
 * @file  bst_linked.c
 * Linked BST Source Code File
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "bst_linked.h"

// Macro for comparing node heights
#define MAX_HEIGHT(a, b) ((a) > (b) ? a : b)

//--------------------------------------------------------------------
// Local Functions

/**
 * Initializes a new BST node with a copy of item.
 *
 * @param source pointer to a BST source
 * @param item pointer to the item to assign to the node
 * @return a pointer to a new BST node
 */
static bst_node *bst_node_initialize(const data_ptr item)
{
    // Base case: add a new node containing a copy of item.
    bst_node *node = malloc(sizeof *node);
    node->item = malloc(sizeof *node->item);
    data_copy(node->item, item);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Helper function to determine the height of node - handles empty node.
 * @param node The node to process.
 * @return The height of the current node.
 */
static int bst_node_height(const bst_node *node)
{
    int height = 0;

    if (node != NULL)
    {
        height = node->height;
    }
    return height;
}

/**
 * Updates the height of a node. Its height is the max of the heights of its
 * child nodes, plus 1.
 * @param node The node to process.
 */
static void bst_update_height(bst_node *node)
{
    int left_height = bst_node_height(node->left);
    int right_height = bst_node_height(node->right);

    node->height = MAX_HEIGHT(left_height, right_height) + 1;
    return;
}

/**
 * Inserts item into a BST. Insertion must preserve the BST definition.
 * item may appear only once in source.
 *
 * @param source - pointer to a BST
 * @param node - pointer to a node
 * @param item - the item to insert
 * @return - true if item inserted, false otherwise
 */
static bool bst_insert_aux(bst_linked *source, bst_node **node, const data_ptr item)
{
    bool inserted = false;

    if (*node == NULL)
    {
        // Base case: add a new node containing the item.
        *node = bst_node_initialize(item);
        source->count += 1;
        inserted = true;
    }
    else
    {
        // Compare the node data_ptr against the new item.
        int comp = data_compare(item, (*node)->item);

        if (comp < 0)
        {
            // General case: check the left subsource.
            inserted = bst_insert_aux(source, &(*node)->left, item);
        }
        else if (comp > 0)
        {
            // General case: check the right subsource.
            inserted = bst_insert_aux(source, &(*node)->right, item);
        }
    }
    if (inserted)
    {
        // Update the node height if any of its children have been changed.
        bst_update_height(*node);
    }
    return inserted;
}

static void free_node_aux(bst_node *current)
{
    if (current != NULL)
    {
        free_node_aux(current->left);
        free_node_aux(current->right);

        data_free(&current->item);
        free(current);
    }
}

static bool balanced_aux(const bst_node *node)
{
    if (node == NULL)
    {
        return true;
    }

    int left_height = bst_node_height(node->left);
    int right_height = bst_node_height(node->right);

    if (abs(left_height - right_height) > 1)
    {
        return false;
    }

    return balanced_aux(node->left) && balanced_aux(node->right);
}

static int leaf_count_aux(const bst_node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }

    return leaf_count_aux(node->left) + leaf_count_aux(node->right);
}

static void inorder_aux(bst_node *node, data_ptr *items, int *index)
{
    if (node == NULL)
    {
        return;
    }
    inorder_aux(node->left, items, index);

    items[*index] = node->item;
    (*index)++;
    inorder_aux(node->right, items, index);
}
//--------------------------------------------------------------------
// Functions

// Initializes a BST.
bst_linked *bst_initialize()
{
    bst_linked *source = malloc(sizeof *source);
    source->root = NULL;
    source->count = 0;
    return source;
}

// frees a BST.
void bst_free(bst_linked **source)
{

    // your code here
    if (*source == NULL)
    {
        return;
    }

    free_node_aux((*source)->root);
    free(*source);

    *source = NULL;
}

// Determines if a BST is empty.
bool bst_empty(const bst_linked *source)
{

    // your code here
    return source->root == NULL;
}

// Determines if a BST is full.
bool bst_full(const bst_linked *source)
{
    if (source == NULL)
    {
        return true;
    }

    if ((source->root->left == NULL && source->root->right != NULL) || (source->root->left != NULL && source->root->right == NULL))
    {
        return false;
    }

    return bst_full(source->root->left) && bst_full(source->root->right);
}

// Returns number of items in a BST.
int bst_count(const bst_linked *source)
{

    // your code here
    return source->count;
}

// Copies the contents of a BST to an array in inorder.
void bst_inorder(const bst_linked *source, data_ptr *items)
{

    // your code here
    if (index == NULL || items == NULL || source == NULL)
    {
        return;
    }

    int index = 0;

    if (source->root != NULL)
    {

        inorder_aux(source->root, items, &index);
    }
}

// Copies the contents of a BST to an array in preorder.
void bst_preorder(const bst_linked *source, data_ptr *items)
{

    // your code here

    return;
}

// Copies the contents of a BST to an array in postorder.
void bst_postorder(const bst_linked *source, data_ptr *items)
{

    // your code here

    return;
}

// Inserts a copy of an item into a BST.
bool bst_insert(bst_linked *source, const data_ptr item)
{
    return bst_insert_aux(source, &(source->root), item);
}

// Retrieves a copy of a value matching key in a BST.
bool bst_retrieve(bst_linked *source, const data_ptr key, data_ptr item)
{

    // your code here
    if (source == NULL)
    {
        return false;
    }

    bst_node *current = source->root;

    while (current != NULL)
    {
        int comp_result = data_compare(key, current->item);

        if (comp_result == 0)
        {
            data_copy(item, current->item);
            return true;
        }
        else if (comp_result < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return false;
}

// Removes a value matching key in a BST.
bool bst_remove(bst_linked *source, const data_ptr key, data_ptr item)
{

    // your code here

    return false;
}

// Copies source to target.
void bst_copy(bst_linked **target, const bst_linked *source)
{

    // your code here

    return;
}

// Finds the maximum item in a BST.
bool bst_max(const bst_linked *source, data_ptr item)
{

    // your code here

    return false;
}

// Finds the minimum item in a BST.
bool bst_min(const bst_linked *source, data_ptr item)
{

    // your code here

    return false;
}

// Finds the number of leaf nodes in a tree.
int bst_leaf_count(const bst_linked *source)
{

    // your code here

    if (source == NULL || source->root == NULL)
    {
        return 0;
    }

    return leaf_count_aux(source->root);
}

// Finds the number of nodes with one child in a tree.
int bst_one_child_count(const bst_linked *source)
{

    // your code here

    return 0;
}

// Finds the number of nodes with two children in a tree.
int bst_two_child_count(const bst_linked *source)
{

    // your code here

    return 0;
}

// Determines the number of nodes with zero, one, and two children.
// (May not call bst_leaf_count, bst_one_child_count, or bst_two_child_count.)
void bst_node_counts(const bst_linked *source, int *zero, int *one, int *two)
{

    // your code here

    return;
}

// Determines whether or not a tree is a balanced tree.
bool bst_balanced(const bst_linked *source)
{

    // your code here
    if (source == NULL)
    {
        return true;
    }

    return balanced_aux(source->root);
}

// Determines whether or not a tree is a valid BST.
bool bst_valid(const bst_linked *source)
{

    // your code here

    return false;
}

// Determines if two trees contain same data in same configuration.
bool bst_equals(const bst_linked *target, const bst_linked *source)
{

    // your code here

    return false;
}

/**
 * Private helper function to print contents of BS in preorder.
 *
 * @param to_string - function to print data_ptr
 * @param node - pointer to bst_node
 */
static void bst_print_aux(bst_node *node)
{
    char string[DATA_STRING_SIZE];

    if (node != NULL)
    {
        data_string(string, DATA_STRING_SIZE, node->item);
        printf("%s\n", string);
        bst_print_aux(node->left);
        bst_print_aux(node->right);
    }
    return;
}

// Prints the items in a BST in preorder.
void bst_print(const bst_linked *source)
{
    printf("  count: %d, height: %d, items:\n", source->count, source->root->height);
    bst_print_aux(source->root);
    printf("\n");
    return;
}