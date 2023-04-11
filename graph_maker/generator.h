#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_PATH_LENGTH 1024

int check_if_can_be_opened(char *file_path);
int graph_to_file(const char *name_of_output_file, Graph *graph);
void fprintf_vertex_and_weight(Graph *graph, FILE *out, int from, int to, int num_of_neighbour);
void fprintf_all_existing_connections(Graph *graph, FILE *out, int from);
double get_random_double(double lower_bounds_of_weight, double upper_bounds_of_weight);
Graph *generate_graph_where_all_connections_exist(double lower_bounds_of_weight, double upper_bounds_of_weight, int num_of_rows, int num_of_columns);
Graph *generate_graph_randomly_till_its_connected(double lower_bounds_of_weight, double upper_bounds_of_weight, int num_of_rows, int num_of_columns);
Graph *generate_graph_randomly(double lower_bounds_of_weight, double upper_bounds_of_weight, int num_of_rows, int num_of_columns);

#endif