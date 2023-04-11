#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h> // for comparing doubles
#include <ctype.h>
#include <string.h>
#include "queue.h" //header file with functions for queue
#include <stdbool.h>
#define LINE_BUFFER_SIZE 1024

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

typedef struct Graph
{
    double **weight;         // weight of connections weigth[u][c]
                             // c stands for neightbours from vertex u
                             // c = 0 - right
                             // c = 1 - up
                             // c = 2 - left
                             // c = 3 - down
    bool **adjacency_matrix; // adjacency_matrix[u][c]==1 means there is connection beetween node u and neightbour c
    int dimension;           // dimension=number_of_rows*number_of_columns
    int number_of_rows;
    int number_of_columns;
} Graph;

Graph *initiate_graph(int num_of_rows, int num_of_columns);

void free_graph(Graph **graph);

void reverse_connections(Graph *graph);

int is_graph_strongly_connected(Graph *graph);
// runs bfs then reverse connections and then run bfs again

void mark_as_visited_and_enqueue(Queue *q, bool *visited_arr, int node_num);

int bfs(Graph *graph, int start);
// performs a bfs algorithm from single node
// returns 1 if all nodes were visited starting from "start" node
// if not returns 0

int create_graph_from_file(Graph **graph, char *name_of_input_file, char *line_with_error);
// returns 1 if creating file failed
// returns 2 if format of input file was incorrect
// returns 3 if unexpected error occured during reading line
// returns 4 if file was empty
// returns 5 if there can't be connection due to not existing node
// returns 6 if there can't be connection due to not being neighbour
// returns 7 if weight is negative

#endif