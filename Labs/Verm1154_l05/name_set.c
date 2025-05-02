/**
 * -------------------------------------
 * @file  name_set_initialize.c
 * Lab 5 Source Code File
 * -------------------------------------
 * @author Heider Ali, 999999999, heali@wlu.ca
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "name_set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize a new name_set
name_set* name_set_initialize() {
    name_set *set = malloc(sizeof *set);
    if (set != NULL) {
        set->front = NULL;
        set->rear = NULL;
    }
    return set;
}

// Free all memory associated with the name_set
int name_set_free(name_set **set) {
    if (set == NULL || *set == NULL) {
        return 0; // Nothing to free
    }

    int freed_count = 0;
    name_set_node *current = (*set)->front;
    name_set_node *next;

    // Traverse the list and free each node
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
        freed_count++;
    }

    // Free the set header
    free(*set);
    *set = NULL; // Set the pointer to NULL to avoid dangling reference

    // Include the set header in the count
    freed_count++;

    return freed_count;
}

// Append a new name to the set
BOOLEAN name_set_append(name_set *set, const char *first_name, const char *last_name) {
    if (set == NULL || first_name == NULL || last_name == NULL) {
        return FALSE; // Invalid input
    }

    // Check if the name is already in the set
    if (name_set_contains(set, first_name, last_name)) {
        return FALSE; // Name already exists
    }

    // Allocate memory for a new node
    name_set_node *new_node = malloc(sizeof *new_node);
    if (new_node == NULL) {
        return FALSE; // Memory allocation failed
    }

    // Copy the strings into the fixed-size arrays
    strncpy(new_node->first_name, first_name, NAME_LEN - 1);
    new_node->first_name[NAME_LEN - 1] = '\0'; // Ensure null-termination
    strncpy(new_node->last_name, last_name, NAME_LEN - 1);
    new_node->last_name[NAME_LEN - 1] = '\0'; // Ensure null-termination

    // Add the new node to the list
    new_node->next = NULL;
    if (set->rear == NULL) {
        // List is empty
        set->front = new_node;
        set->rear = new_node;
    } else {
        // Append to the end of the list
        set->rear->next = new_node;
        set->rear = new_node;
    }

    return TRUE; // Name appended successfully
}

// Check if a name exists in the set
BOOLEAN name_set_contains(const name_set *set, const char *first_name, const char *last_name) {
    if (set == NULL || first_name == NULL || last_name == NULL) {
        return FALSE; // Invalid input
    }

    name_set_node *current = set->front;
    while (current != NULL) {
        if (strcmp(current->first_name, first_name) == 0 &&
            strcmp(current->last_name, last_name) == 0) {
            return TRUE; // Name found
        }
        current = current->next;
    }

    return FALSE; // Name not found
}

// Print all names in the set
void name_set_print(const name_set *set) {
    if (set == NULL) {
        return; // Invalid input
    }

    name_set_node *current = set->front;
    while (current != NULL) {
        printf("%s, %s\n", current->last_name, current->first_name);
        current = current->next;
    }
}