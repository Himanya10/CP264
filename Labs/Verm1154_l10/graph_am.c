/**
 * -------------------------------------
 * @file  graph_am.c
 * Adjacency Matrix Graph Implementation
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph_am.h"

// Helper function to get index xin 1D array for 2D matrix
static int get_index(int row, int col, int size) {
	return row * size + col;
}

graph_am* graph_am_initialize(int size) {
	graph_am *source = malloc(sizeof(graph_am));
	source->size = size;
	source->values = calloc(size * size, sizeof(int));
	return source;
}

void graph_am_free(graph_am **source) {
	if (source != NULL && *source != NULL) {
		free((*source)->values);
		free(*source);
		*source = NULL;
	}
}

int graph_am_add_vertice(graph_am *source, const graph_am_pair *pair) {
	if (source == NULL || pair == NULL)
		return 0;
	if (pair->row < 0 || pair->row >= source->size || pair->col < 0
			|| pair->col >= source->size) {
		return 0;
	}

	int index = get_index(pair->row, pair->col, source->size);
	if (source->values[index] != 0)
		return 0; // Already exists

	if (pair->row == pair->col) {
		source->values[index] = 2; // Loop
	} else {
		source->values[index] = 1;
		source->values[get_index(pair->col, pair->row, source->size)] = 1;
	}
	return 1;
}

int graph_am_remove_vertice(graph_am *source, const graph_am_pair *pair) {
	if (source == NULL || pair == NULL)
		return 0;
	if (pair->row < 0 || pair->row >= source->size || pair->col < 0
			|| pair->col >= source->size) {
		return 0;
	}

	int index = get_index(pair->row, pair->col, source->size);
	if (source->values[index] == 0)
		return 0; // Doesn't exist

	if (pair->row == pair->col) {
		source->values[index] = 0; // Loop
	} else {
		source->values[index] = 0;
		source->values[get_index(pair->col, pair->row, source->size)] = 0;
	}
	return 1;
}

graph_am* graph_am_create(int size, const graph_am_pair pairs[], int count) {
	graph_am *source = graph_am_initialize(size);
	for (int i = 0; i < count; i++) {
		graph_am_add_vertice(source, &pairs[i]);
	}
	return source;
}

void graph_am_neighbours(const graph_am *source, int vertex, int vertices[],
		int *count) {
	*count = 0;
	if (source == NULL || vertex < 0 || vertex >= source->size)
		return;

	for (int i = 0; i < source->size; i++) {
		int index = get_index(vertex, i, source->size);
		if (source->values[index] > 0) {
			vertices[(*count)++] = i;
		}
	}
}

int graph_am_degree(const graph_am *source, int vertex) {
	if (source == NULL || vertex < 0 || vertex >= source->size)
        return 0;

    int degree = 0;
    for (int i = 0; i < source->size; i++) {
        int index = get_index(vertex, i, source->size);
        if (source->values[index] == 1) {
            degree++;
        } else if (source->values[index] == 2) {
            degree += 2; // Corrected: loops contribute 2 to the degree
        }
    }
    return degree;
}

// Helper function for BFS
static void bfs(const graph_am *source, int vertex, int visited[],
		int vertices[], int *count) {
	int queue[source->size];
	int front = 0, rear = 0;

	visited[vertex] = 1;
	vertices[(*count)++] = vertex;
	queue[rear++] = vertex;

	while (front < rear) {
		int current = queue[front++];
		int neighbors[source->size];
		int neighbor_count = 0;
		graph_am_neighbours(source, current, neighbors, &neighbor_count);

		for (int i = 0; i < neighbor_count; i++) {
			int neighbor = neighbors[i];
			if (!visited[neighbor]) {
				visited[neighbor] = 1;
				vertices[(*count)++] = neighbor;
				queue[rear++] = neighbor;
			}
		}
	}
}

void graph_am_breadth_traversal(const graph_am *source, int vertex,
		int vertices[], int *count) {
	*count = 0;
	if (source == NULL || vertex < 0 || vertex >= source->size)
		return;

	int visited[source->size];
	for (int i = 0; i < source->size; i++) {
		visited[i] = 0;
	}

	bfs(source, vertex, visited, vertices, count);
}

static void dfs(const graph_am *source, int vertex, int visited[],
		int vertices[], int *count) {
	visited[vertex] = 1;
	vertices[(*count)++] = vertex;

	// Visit neighbors in reverse order to match expected traversal
	for (int i = source->size - 1; i >= 0; i--) {
		int index = get_index(vertex, i, source->size);
		if (source->values[index] > 0 && !visited[i]) {
			dfs(source, i, visited, vertices, count);
		}
	}
}

void graph_am_depth_traversal(const graph_am *source, int vertex,
		int vertices[], int *count) {
	*count = 0;
	if (source == NULL || vertex < 0 || vertex >= source->size)
		return;

	int visited[source->size];
	for (int i = 0; i < source->size; i++) {
		visited[i] = 0;
	}

	dfs(source, vertex, visited, vertices, count);
}

void graph_am_print(const graph_am *source) {
	if (source == NULL)
		return;

	printf("Size: %d\n", source->size);
	printf("Matrix:\n");

	for (int i = 0; i < source->size; i++) {
		for (int j = 0; j < source->size; j++) {
			int index = get_index(i, j, source->size);
			printf("%d ", source->values[index]);
		}
		printf("\n");
	}
}
