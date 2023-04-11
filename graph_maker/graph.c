#include "graph.h"

Graph *initiate_graph(int num_of_rows, int num_of_columns)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->dimension = num_of_rows * num_of_columns;
    graph->weight = (double **)malloc(graph->dimension * sizeof(double *));
    if (graph->weight == NULL)
    {
        return NULL;
    }
    graph->adjacency_matrix = (bool **)malloc(graph->dimension * sizeof(bool *));
    if (graph->adjacency_matrix == NULL)
    {
        return NULL;
    }
    graph->number_of_rows = num_of_rows;
    graph->number_of_columns = num_of_columns;
    for (int i = 0; i < graph->dimension; i++)
    {
        graph->weight[i] = (double *)calloc(4, sizeof(double)); // changed to calloc
        if (graph->weight[i] == NULL)
        {
            return NULL;
        }
        graph->adjacency_matrix[i] = (bool *)calloc(4, sizeof(bool)); // calloc initiates all adjacency_matrix[i][j]=false
        if (graph->adjacency_matrix[i] == NULL)
        {
            return NULL;
        }
    }
    return graph;
}

void free_graph(Graph **graph)
{
    for (int i = 0; i < (*graph)->dimension; i++)
    {
        free((*graph)->adjacency_matrix[i]);
        (*graph)->adjacency_matrix[i] = NULL;
        free((*graph)->weight[i]);
        (*graph)->weight[i] = NULL;
    }
    free((*graph)->adjacency_matrix);
    (*graph)->adjacency_matrix = NULL;
    free((*graph)->weight);
    (*graph)->weight = NULL;
    free((*graph));
    (*graph) = NULL;
}

void reverse_connections(Graph *graph)
{
    bool temp_is_connected;
    double temp_weight;
    for (int i = 0; i < graph->dimension; i++)
    {
        if (i % graph->number_of_columns + 1 < graph->number_of_columns)
        {
            temp_is_connected = graph->adjacency_matrix[i][RIGHT];
            temp_weight = graph->weight[i][RIGHT];
            graph->adjacency_matrix[i][RIGHT] = graph->adjacency_matrix[i + 1][LEFT];
            graph->weight[i][RIGHT] = graph->weight[i + 1][LEFT];
            graph->adjacency_matrix[i + 1][LEFT] = temp_is_connected;
            graph->weight[i + 1][LEFT] = temp_weight;
        }
        if (i + graph->number_of_columns < graph->dimension)
        {
            temp_is_connected = graph->adjacency_matrix[i][DOWN];
            temp_weight = graph->weight[i][DOWN];
            graph->adjacency_matrix[i][DOWN] = graph->adjacency_matrix[i + graph->number_of_columns][UP];
            graph->weight[i][DOWN] = graph->weight[i + graph->number_of_columns][UP];
            graph->adjacency_matrix[i + graph->number_of_columns][UP] = temp_is_connected;
            graph->weight[i + graph->number_of_columns][UP] = temp_weight;
        }
    }
}

int is_graph_strongly_connected(Graph *graph)
{
    int start = 0;
    if (bfs(graph, start) != 1)
    {
        return 0;
    }
    reverse_connections(graph);
    if (bfs(graph, start) != 1)
    {
        return 0;
    }
    return 1;
}

void mark_as_visited_and_enqueue(Queue *q, bool *visited_arr, int node_num)
{
    if (visited_arr[node_num] == false)
    {
        visited_arr[node_num] = true;
        queue_push(q, node_num);
    }
}

int bfs(Graph *graph, int start)
{
    bool *visited_arr = (bool *)calloc(graph->dimension, sizeof(bool));
    if (visited_arr == NULL)
    {
        return 2;
    }
    Queue *q = queue_init();
    if (q == NULL)
    {
        return 2;
    }
    visited_arr[start] = true;
    queue_push(q, start);
    int v;
    while (q->size != 0)
    {
        v = q->first->vertex;
        queue_pop(q);
        if (v % graph->number_of_columns + 1 < graph->number_of_columns && graph->adjacency_matrix[v][RIGHT] == true)
        {
            mark_as_visited_and_enqueue(q, visited_arr, v + 1);
        }
        if (v - graph->number_of_columns >= 0 && graph->adjacency_matrix[v][UP] == true)
        {
            mark_as_visited_and_enqueue(q, visited_arr, v - graph->number_of_columns);
        }
        if (v % graph->number_of_columns - 1 < graph->number_of_columns && graph->adjacency_matrix[v][LEFT] == true)
        {
            mark_as_visited_and_enqueue(q, visited_arr, v - 1);
        }
        if (v + graph->number_of_columns < graph->dimension && graph->adjacency_matrix[v][DOWN] == true)
        {
            mark_as_visited_and_enqueue(q, visited_arr, v + graph->number_of_columns);
        }
    }
    free(q);
    for (int i = 0; i < graph->dimension; i++)
    {
        if (visited_arr[i] == false)
        {
            free(visited_arr);
            return 0;
        }
    }
    free(visited_arr);

    return 1; // return 1 if graph is connected
}

int create_graph_from_file(Graph **graph, char *name_of_input_file, char *line_with_error)
{
    FILE *in = fopen(name_of_input_file, "r");
    if (in == NULL)
    {
        return 1;
    }

    char buff[LINE_BUFFER_SIZE];
    char *str;
    int num_of_rows;
    int num_of_columns;
    if ((str = fgets(buff, LINE_BUFFER_SIZE, in)) != NULL)
    {
        while (*str != '\0' && (*str == ' ' || *str == '\t'))
        {
            str++;
        }
        if (*str == '0')
        {
            if (*(str + 1) == '\0')
            {
                sprintf(line_with_error, "Linia %d:%s", 1, buff);
                fclose(in);
                return 2;
            }
            if (isdigit(*(str + 1))) // eliminate inputs with leading zeroes (for ex. 06, 00, etc.)
            {
                sprintf(line_with_error, "Linia %d:%s", 1, buff);
                fclose(in);
                return 2;
            }
        }
        num_of_rows = strtol(str, &str, 10);
        while (*str != '\0' && (*str == ' ' || *str == '\t'))
        {
            str++;
        }
        if (isdigit(*str) == 0)
        {
            sprintf(line_with_error, "Linia %d:%s", 1, buff);
            fclose(in);
            return 2;
        }
        if (*str == '0')
        {
            if (*(str + 1) != '\0' && isdigit(*(str + 1)) == 1) // eliminate inputs with leading zeroes (for ex. 06, 00, etc.)
            {
                sprintf(line_with_error, "Linia %d:%s", 1, buff);
                fclose(in);
                return 2;
            }
        }
        num_of_columns = strtol(str, &str, 10);
        while (*str != '\0' && (*str == ' ' || *str == '\t'))
        {
            str++;
        }
        if (*str != '\n')
        {
            sprintf(line_with_error, "Linia %d:%s", 1, buff);
            fclose(in);
            return 2;
        }
    }
    else
    {
        if (ferror(in) != 0) // if reading ended due to reading error
        {
            fclose(in);
            return 3;
        }
        else if (feof(in) != 0) // file was empty
        {
            fclose(in);
            return 4;
        }
    }
    Graph *graph_res = initiate_graph(num_of_rows, num_of_columns);

    int index_from = 0;
    int index_to;
    double weight;
    while ((str = fgets(buff, LINE_BUFFER_SIZE, in)) != NULL)
    {
        while (*str != '\n' && *str != '\0')
        {
            // skip whitespace
            while (*str != '\0' && (*str == ' ' || *str == '\t'))
            {
                str++;
            }
            if (*str == '\n' || *str == '\0') // if line was empty
            {
                break;
            }
            // check if number of node has no leading zeroes
            if (*str == '0')
            {
                if (*(str + 1) == '\0')
                {
                    free_graph(&graph_res);
                    sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                    fclose(in);
                    return 2;
                }
                if (isdigit(*(str + 1))) // eliminate inputs with leading zeroes (for ex. 06, 00, etc.)
                {
                    free_graph(&graph_res);
                    sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                    fclose(in);
                    return 2;
                }
            }
            index_to = strtol(str, &str, 10);
            while (*str != '\0' && (*str == ' ' || *str == '\t'))
            {
                str++;
            }
            if (*str == ':') // if first sign after read number is ':' then input is correct for now
            {
                str++;
            }
            else
            {
                free_graph(&graph_res);
                sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                fclose(in);
                return 2;
            }
            weight = strtod(str, &str);
            while (*str != '\0' && (*str == ' ' || *str == '\t'))
            {
                str++;
            }
            if (*str != '\n' && *str != '\0' && isdigit(*str) == 0) // if there is no end of line and next sign is not number then input file is in wrong format in this line
            {
                free_graph(&graph_res);
                sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                fclose(in);
                return 2;
            }
            // returns 5 if there can't be connection due to not existing node
            if (index_from >= graph_res->dimension || index_from < 0 || index_to >= graph_res->dimension || index_to < 0)
            {
                free_graph(&graph_res);
                sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                fclose(in);
                return 5;
            }
            // returns 6 if there can't be connection due to not being neighbour
            if (!(index_from - 1 == index_to || index_from + 1 == index_to || index_from - graph_res->number_of_columns == index_to || index_from + graph_res->number_of_columns == index_to))
            {
                free_graph(&graph_res);
                sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                fclose(in);
                return 6;
            }
            // returns 7 if weight is negative
            if (weight < 0)
            {
                free_graph(&graph_res);
                sprintf(line_with_error, "Linia %d:%s\nNr wierzchołka odpowiadającego tej linii: %d", index_from + 2, buff, index_from);
                fclose(in);
                return 7;
            }
            // right
            if (index_from % graph_res->number_of_columns + 1 < graph_res->number_of_columns && index_from + 1 == index_to)
            {
                graph_res->adjacency_matrix[index_from][0] = true;
                graph_res->weight[index_from][0] = weight;
            }
            // up
            else if (index_from - graph_res->number_of_columns >= 0 && index_from - graph_res->number_of_columns == index_to)
            {
                graph_res->adjacency_matrix[index_from][1] = true;
                graph_res->weight[index_from][1] = weight;
            }
            // left
            else if (index_from % graph_res->number_of_columns - 1 >= 0 && index_from - 1 == index_to)
            {
                graph_res->adjacency_matrix[index_from][2] = true;
                graph_res->weight[index_from][2] = weight;
            }
            // down
            else if (index_from + graph_res->number_of_columns < graph_res->dimension && index_from + graph_res->number_of_columns == index_to)
            {
                graph_res->adjacency_matrix[index_from][3] = true;
                graph_res->weight[index_from][3] = weight;
            }
            else // unexpected
            {
                free_graph(&graph_res);
                fclose(in);
                return 8;
            }
        }
        index_from++;
    }
    fclose(in);
    *graph = graph_res;
    return 0;
}
