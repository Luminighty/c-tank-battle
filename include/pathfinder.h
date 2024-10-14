#ifndef PATHFINDER_H
#define PATHFINDER_H

typedef struct {
	int speed;
	int x;
	int y;
} PathFinderNode;

typedef struct {
    int node_count;
    int node_capacity;
    PathFinderNode* nodes;
} PathFinderResult;

typedef int (*PathFinderGetWeight)(int x, int y, void* context);

PathFinderResult pathfinder_run(int start_x, int start_y, int speed, PathFinderGetWeight weights, void* context);
PathFinderNode* pathfinder_prev(PathFinderResult* result, PathFinderNode* current);
PathFinderNode* pathfinder_find(PathFinderResult* result, int x, int y);

void pathfinder_print(const PathFinderResult* result);
void pathfinder_node_print(const PathFinderNode* result);

void pathfinder_destroy(PathFinderResult* pathfinder_result);

#endif // PATHFINDER_H
