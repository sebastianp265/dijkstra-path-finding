#include "path.h"

Dijkstra_result *dijkstra(Graph *graph, int start)
{
    double *distance = (double *)malloc(graph->dimension * sizeof(double));
    int *prev = (int *)malloc(graph->dimension * sizeof(int));

    Priority_queue *pq = initiate_priority_queue();

    distance[start] = 0;
    prev[start] = -1;
    for (int i = 0; i < graph->dimension; i++)
    {
        if (i != start)
        {
            distance[i] = __DBL_MAX__;
            prev[i] = -1;
        }
        Node *node = initiate_node(i, distance[i]);
        push_priority_queue(pq, node);
    }

    int u, v;
    while (!is_empty_priority_queue(pq))
    {
        u = peek_priority_queue(pq)->node_num;
        pop_priority_queue(pq);
        v = u + 1; // right node
        if (u % graph->number_of_columns + 1 < graph->number_of_columns)
        {
            edge_relaxation(pq, graph, u, v, RIGHT, distance, prev);
        }
        v = u - graph->number_of_columns; // upper node
        if (v >= 0)                       // checking if connecion is possible
        {
            edge_relaxation(pq, graph, u, v, UP, distance, prev);
        }
        v = u - 1; // left node
        if (u % graph->number_of_columns - 1 >= 0)
        {
            edge_relaxation(pq, graph, u, v, LEFT, distance, prev);
        }
        v = u + graph->number_of_columns; // lower node
        if (v < graph->dimension)         // checking if connecion is possible
        {
            edge_relaxation(pq, graph, u, v, DOWN, distance, prev);
        }
    }

    Dijkstra_result *result = (Dijkstra_result *)malloc(sizeof(Dijkstra_result));
    result->distance = distance;
    result->number_of_nodes = graph->dimension;
    result->prev = prev;
    result->start = start;
    result->weight = graph->weight;
    result->num_of_columns=graph->number_of_columns;

    free_priority_queue(&pq);
    return result;
}

int is_node_in_queue(Priority_queue *pq, int node_num_v)
{
    for (int i = 0; i < pq->size; i++)
    {
        if (pq->node[i]->node_num == node_num_v)
        {
            return 1; // found!
        }
    }
    return 0; // not found!
}

void edge_relaxation(Priority_queue *pq, Graph *graph, int u, int v, int neighbour_num, double *distance, int *prev)
{
    if (graph->adjacency_matrix[u][neighbour_num] == true && is_node_in_queue(pq, v)) // check if there is connection between u and v and if node v is in queue
    {
        double temp = distance[u] + graph->weight[u][neighbour_num];
        if (temp < distance[v])
        {
            distance[v] = temp;
            prev[v] = u;
            decrease_priority_queue(pq, v, temp);
        }
    }
}

Stack *fill_stack_from_dijkstra(Dijkstra_result *result, int end)
{
    Stack *top_of_stack = NULL;
    // filling backwards

    if (result->start != end && result->prev[end] == -1) // dijkstra algorithm didn't reach end node
    {
        return NULL;
    }
    int current_node = end; // fills stack backwards from end to start from prev array
    int prev_node = result->prev[current_node];
    while (current_node != result->start)
    {
        if (prev_node + 1 == current_node)
        {
            push_stack(&top_of_stack, current_node, result->weight[prev_node][RIGHT]);
        }
        else if(prev_node - result->num_of_columns == current_node)
        {
            push_stack(&top_of_stack, current_node, result->weight[prev_node][UP]);
        }
        else if(prev_node - 1 == current_node)
        {
            push_stack(&top_of_stack, current_node, result->weight[prev_node][LEFT]);
        }
        else if(prev_node + result->num_of_columns == current_node)
        {
            push_stack(&top_of_stack, current_node, result->weight[prev_node][DOWN]);
        }
        current_node = prev_node;
        prev_node = result->prev[current_node];
    }
    push_stack(&top_of_stack, current_node, result->distance[current_node]); // add last node (current_node==(*result)->start)
    return top_of_stack;
}

void free_dijkstra_result(Dijkstra_result **result)
{
    if ((*result)->distance != NULL)
    {
        free((*result)->distance);
        (*result)->distance = NULL;
    }
    if ((*result)->prev != NULL)
    {
        free((*result)->prev);
        (*result)->prev = NULL;
    }
    if ((*result) != NULL)
    {
        free(*result);
        result = NULL;
    }
}

Node_pair_input *fill_input_from_string(char **str)
{
    if (**str == '\0')
    {
        return NULL;
    }
    if (isdigit(**str) == 0)
    {
        return NULL;
    }
    if (**str == '0')
    {
        if (*(*str + 1) == '\0')
        {
            return NULL;
        }
        if (isdigit(*(*str + 1))) // eliminate inputs with leading zeroes (for ex. 06, 00, etc.)
        {
            return NULL;
        }
    }
    int start = strtol(*str, str, 10);
    if (**str == '\0') // next two characters must be '-'
    {
        return NULL;
    }
    if (**str == '-')
    {
        (*str)++;
    }
    else
    {
        return NULL;
    }
    // getting second node -similar procedure
    if (isdigit(**str) == 0)
    {
        return NULL;
    }
    if (**str == '0')
    {
        if (*(*str + 1) != '\0' && isdigit(*(*str + 1)) == 1) // eliminate inputs with leading zeroes (for ex. 06, 00, etc.)
        {
            return NULL;
        }
    }
    int end = strtol(*str, str, 10);
    if (**str != '\0')
    {
        if (**str == ',')
        {
            (*str)++;
        }
        else
        {
            return NULL;
        }
    }
    Node_pair_input *pair_input = (Node_pair_input *)malloc(sizeof(Node_pair_input));
    pair_input->start = start;
    pair_input->end = end;
    return pair_input;
}