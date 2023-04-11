#include "generator.h"

double get_random_double(double lower_bounds_of_weight, double upper_bounds_of_weight)
{
    return lower_bounds_of_weight + (double)rand() * (upper_bounds_of_weight - lower_bounds_of_weight) / (double)RAND_MAX;
}

void fprintf_all_existing_connections(Graph *graph, FILE *out, int from)
{
    fprintf(out, "\t");
    if (graph->adjacency_matrix[from][RIGHT] == true) // checking if a connection to right node can exist
    {
        fprintf(out, " %d :%.16lf ", from + 1, graph->weight[from][RIGHT]);
    }
    if (graph->adjacency_matrix[from][UP] == true) // checking if a connection to upper node can exist
    {
        fprintf(out, " %d :%.16lf ", from - graph->number_of_columns, graph->weight[from][UP]);
    }
    if (graph->adjacency_matrix[from][LEFT] == true) // checking if a connection to left node can exist
    {
        fprintf(out, " %d :%.16lf ", from - 1, graph->weight[from][LEFT]);
    }
    if (graph->adjacency_matrix[from][DOWN] == true) // checking if a connection to lower node can exist
    {
        fprintf(out, " %d :%.16lf ", from + graph->number_of_columns, graph->weight[from][DOWN]);
    }
}

int check_if_can_be_opened(char *file_path)
{
    FILE *in = fopen(file_path, "r");
    if (in != NULL)
    {
        fclose(in);
        return 1;
    }
    return 0;
}

int graph_to_file(const char *name_of_output_file, Graph *graph)
{
    FILE *out = fopen(name_of_output_file, "w");
    if (out == NULL)
    {
        return 1;
    }
    fprintf(out, "%d %d\n", graph->number_of_rows, graph->number_of_columns);
    int i = 0;
    for (; i < graph->dimension - 1; i++) // loop n-1 times so we dont generate newline in last line of file
    {
        fprintf_all_existing_connections(graph, out, i);
        fprintf(out, "\n");
    }
    // everything is the same as in the loop without "\n" at the end
    fprintf_all_existing_connections(graph, out, i);
    fclose(out);
    return 0;
}

Graph *generate_graph_where_all_connections_exist(double lower_bounds_of_weight, double upper_bounds_of_weight, int num_of_rows, int num_of_columns)
{
    srand(time(NULL));
    Graph *graph = initiate_graph(num_of_rows, num_of_columns);
    if (graph == NULL)
    {
        return NULL;
    }
    // generating connection from every node in graph to every adjacent node
    for (int i = 0; i < graph->dimension; i++)
    {
        if (i % graph->number_of_columns + 1 < graph->number_of_columns) // checking if a connection to right node can exist
        {
            graph->adjacency_matrix[i][RIGHT] = true;
            graph->weight[i][RIGHT] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
        }
        if (i - graph->number_of_columns >= 0) // checking if a connection to upper node can exist
        {
            graph->adjacency_matrix[i][UP] = true;
            graph->weight[i][UP] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
        }
        if (i % graph->number_of_columns - 1 >= 0) // checking if a connection to left node can exist
        {
            graph->adjacency_matrix[i][LEFT] = true;
            graph->weight[i][LEFT] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
        }
        if (i + graph->number_of_columns < graph->dimension)
        {
            graph->adjacency_matrix[i][DOWN] = true;
            graph->weight[i][DOWN] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
        }
    }
    return graph;
}

Graph *generate_graph_randomly_till_its_connected(double lower_bounds_of_weight, double upper_bounds_of_weight, int num_of_rows, int num_of_columns)
{
    srand(time(NULL));
    Graph *graph = initiate_graph(num_of_rows, num_of_columns);
    if (graph == NULL)
    {
        return NULL;
    }
    int coinflip;
    while (!is_graph_strongly_connected(graph))
    {
        for (int i = 0; i < graph->dimension; i++)
        {
            if (i % graph->number_of_columns + 1 < graph->number_of_columns) // checking if a connection to right node can exist
            {
                if (graph->adjacency_matrix[i][RIGHT] == false)
                {
                    coinflip = rand() % 2;
                    if (coinflip == 1)
                    {
                        graph->adjacency_matrix[i][RIGHT] = true;
                        graph->weight[i][RIGHT] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                    }
                }
            }
            if (i - graph->number_of_columns >= 0) // checking if a connection to upper node can exist
            {
                if (graph->adjacency_matrix[i][UP] == false)
                {
                    coinflip = rand() % 2;
                    if (coinflip == 1)
                    {
                        graph->adjacency_matrix[i][UP] = true;
                        graph->weight[i][UP] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                    }
                }
            }
            if (i % graph->number_of_columns - 1 >= 0) // checking if a connection to left node can exist
            {
                if (graph->adjacency_matrix[i][LEFT] == false)
                {
                    coinflip = rand() % 2;
                    if (coinflip == 1)
                    {
                        graph->adjacency_matrix[i][LEFT] = true;
                        graph->weight[i][LEFT] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                    }
                }
            }
            if (i + graph->number_of_columns < graph->dimension)
            {
                if (graph->adjacency_matrix[i][DOWN] == false)
                {
                    coinflip = rand() % 2;
                    if (coinflip == 1)
                    {
                        graph->adjacency_matrix[i][DOWN] = true;
                        graph->weight[i][DOWN] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                    }
                }
            }
        }
    }
    return graph;
}

Graph *generate_graph_randomly(double lower_bounds_of_weight, double upper_bounds_of_weight, int num_of_rows, int num_of_columns)
{
    srand(time(NULL));
    Graph *graph = initiate_graph(num_of_rows, num_of_columns);
    if (graph == NULL)
    {
        return NULL;
    }
    int coinflip;
    for (int i = 0; i < graph->dimension; i++)
    {
        if (i % graph->number_of_columns + 1 < graph->number_of_columns) // checking if a connection to right node can exist
        {
            if (graph->adjacency_matrix[i][RIGHT] == false)
            {
                coinflip = rand() % 2;
                if (coinflip == 1)
                {
                    graph->adjacency_matrix[i][RIGHT] = true;
                    graph->weight[i][RIGHT] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                }
            }
        }
        if (i - graph->number_of_columns >= 0) // checking if a connection to upper node can exist
        {
            if (graph->adjacency_matrix[i][UP] == false)
            {
                coinflip = rand() % 2;
                if (coinflip == 1)
                {
                    graph->adjacency_matrix[i][UP] = true;
                    graph->weight[i][UP] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                }
            }
        }
        if (i % graph->number_of_columns - 1 >= 0) // checking if a connection to left node can exist
        {
            if (graph->adjacency_matrix[i][LEFT] == false)
            {
                coinflip = rand() % 2;
                if (coinflip == 1)
                {
                    graph->adjacency_matrix[i][LEFT] = true;
                    graph->weight[i][LEFT] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                }
            }
        }
        if (i + graph->number_of_columns < graph->dimension)
        {
            if (graph->adjacency_matrix[i][DOWN] == false)
            {
                coinflip = rand() % 2;
                if (coinflip == 1)
                {
                    graph->adjacency_matrix[i][DOWN] = true;
                    graph->weight[i][DOWN] = get_random_double(lower_bounds_of_weight, upper_bounds_of_weight);
                }
            }
        }
    }

    return graph;
}