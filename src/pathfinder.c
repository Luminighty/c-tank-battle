#include "pathfinder.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


static PathFinderResult pathfinder_result_create() {
	PathFinderResult result;
	result.node_count = 0;
	result.node_capacity = 16;
	result.nodes = malloc(16 * sizeof(PathFinderNode));
	if (!result.nodes) {
		printf("malloc error at pathfinder_result_push :(");
		exit(1);
	}
	return result;
}

static void pathfinder_result_push(PathFinderResult* result, PathFinderNode node) {
	if (result->node_capacity <= result->node_count) {
		result->node_capacity *= 2;
		PathFinderNode* new_nodes = realloc(result->nodes, result->node_capacity * sizeof(PathFinderNode));
		if (!new_nodes) {
			printf("realloc error at pathfinder_result_push :(");
			exit(1);
		}
		result->nodes = new_nodes;
	}
	result->nodes[result->node_count++] = node;
}

static void pathfinder_queue_insert(PathFinderResult* queue, PathFinderNode node) {
	pathfinder_result_push(queue, node);
	int i = queue->node_count - 1;
	while (i > 0 && queue->nodes[i].speed > queue->nodes[i - 1].speed) {
		PathFinderNode temp = queue->nodes[i];
		queue->nodes[i] = queue->nodes[i - 1];
		queue->nodes[i - 1] = temp;
		i--;
	}
}

static PathFinderNode pathfinder_queue_pop(PathFinderResult* queue) {
	PathFinderNode node = queue->nodes[0];
	for (int i = 0; i < queue->node_count; i++)
		queue->nodes[i] = queue->nodes[i + 1];
	queue->node_count--;
	return node;
}

static PathFinderNode pathfinder_node_create(int x, int y, int speed) {
	PathFinderNode node;
	node.x = x;
	node.y = y;
	node.speed = speed;
	return node;
}

static bool pathfinder_contains(PathFinderResult* result, int x, int y, int speed) {
	for (int i = 0; i < result->node_count; i++)
		if (result->nodes[i].x == x && result->nodes[i].y == y && result->nodes[i].speed >= speed)
			return true;
	return false;
}

static inline void try_add_neighbour(PathFinderResult* results, PathFinderResult* queue, PathFinderGetWeight weights, void* context, PathFinderNode* node, int dx, int dy) {
	int new_x = node->x + dx;
	int new_y = node->y + dy;
	int weight = weights(new_x, new_y, context);
	int new_speed = node->speed - weight;
	if (new_speed < 0)
		return;
	if (pathfinder_contains(queue, new_x, new_y, new_speed))
		return;
	if (pathfinder_contains(results, new_x, new_y, 0))
		return;
	PathFinderNode new_node = pathfinder_node_create(new_x, new_y, node->speed - weight);
	pathfinder_queue_insert(queue, new_node);
}

PathFinderResult pathfinder_run(int start_x, int start_y, int speed, PathFinderGetWeight weights, void* context) {
	PathFinderResult result = pathfinder_result_create();
	PathFinderResult queue = pathfinder_result_create();

	pathfinder_queue_insert(&queue, pathfinder_node_create(start_x, start_y, speed));

	while (queue.node_count > 0) {
		PathFinderNode node = pathfinder_queue_pop(&queue);

		try_add_neighbour(&result, &queue, weights, context, &node,  1,  0);
		try_add_neighbour(&result, &queue, weights, context, &node, -1,  0);
		try_add_neighbour(&result, &queue, weights, context, &node,  0,  1);
		try_add_neighbour(&result, &queue, weights, context, &node,  0, -1);

		pathfinder_result_push(&result, node);
	}

	pathfinder_destroy(&queue);
	return result;
}

void pathfinder_destroy(PathFinderResult* pathfinder_result) {
	free(pathfinder_result->nodes);
}

PathFinderNode* pathfinder_prev(PathFinderResult* result, PathFinderNode* current) {
	int i = 0;
	while (&result->nodes[i] != current) {
		int dx = abs(current->x - result->nodes[i].x);
		int dy = abs(current->y - result->nodes[i].y);
		if (dx + dy == 1) {
			return &result->nodes[i];
		}
		i++;
	}
	return NULL;
}

PathFinderNode* pathfinder_find(PathFinderResult *result, int x, int y) {
	for (int i = 0; i < result->node_count; i++)
		if (result->nodes[i].x == x && result->nodes[i].y == y)
			return &result->nodes[i];
	return NULL;
}

void pathfinder_node_print(const PathFinderNode *node) {
	printf("Node { %d, %d, %d }", node->x, node->y, node->speed);
}

void pathfinder_print(const PathFinderResult *result) {
	printf("PathfinderResult {\n");
	for (int i = 0; i < result->node_count; i++) {
		printf("  ");
		pathfinder_node_print(&result->nodes[i]);
		printf("\n");
	}
	printf("}\n");
}
