#ifndef PATH_H
#define PATH_H

#include "../graph_maker/graph.h"
#include "stack.h"
#include "priority_queue.h"
#include <ctype.h>

typedef struct Dijkstra_result
{
    int start;
    double *distance;
    int *prev;
    int number_of_nodes;
    double **weight;
    int num_of_columns;
} Dijkstra_result;

Dijkstra_result *dijkstra(Graph *graph, int start);

void free_dijkstra_result(Dijkstra_result **result);

int is_node_in_queue(Priority_queue *pq, int node_num_v);
void edge_relaxation(Priority_queue *pq, Graph *graph, int u, int v, int neighbour_num, double *distance, int *prev);
Stack *fill_stack_from_dijkstra(Dijkstra_result *result, int end);

typedef struct Node_pair_input
{
    int start;
    int end;
} Node_pair_input;

Node_pair_input *fill_input_from_string(char **str);

#endif