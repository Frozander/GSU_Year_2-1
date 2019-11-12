#include "graph.h"

AdjListNode *new_adj_list_node(int destination)
{
    AdjListNode *new_node = malloc(sizeof(AdjListNode));
    if (new_node == NULL)
    {
        log_error("new_adj_list_node()", MALLOC_ERR);
        return NULL;
    }
    new_node->destination = destination;
    new_node->next = NULL;
    return new_node;
}

Graph *create_graph(int vertices)
{
    Graph *new_graph = malloc(sizeof(Graph));
    if (new_graph == NULL)
    {
        log_error("create_graph()", MALLOC_ERR);
        return NULL;
    }

    new_graph->vertices = vertices;

    new_graph->vertex_array = malloc(sizeof(AdjList) * vertices);
    if (new_graph->vertex_array == NULL)
    {
        log_error("create_graph()", MALLOC_ERR);
        return NULL;
    }

    for (int i = 0; i < vertices; ++i) // ++i because of performance gain
        new_graph->vertex_array[i].head = NULL;

    return new_graph;   
}

void add_edge(Graph *graph, int from, int to)
{
    if (graph == NULL)
    {
        log_error("add_edge()", NULL_OBJECT);
        return;
    }

    AdjListNode *new_node = new_adj_list_node(to);
    if (new_node == NULL)
    {
        log_error("add_edge()", NULL_OBJECT);
        return;
    }

    new_node->next = graph->vertex_array[from].head; // Add linked list at 'from' to new_node
    graph->vertex_array[from].head = new_node;       // Then change linked list at 'from' to new_node's linked list

    // Do the same for backwards
    new_node = new_adj_list_node(from);
    if (new_node == NULL)
    {
        log_error("add_edge()", NULL_OBJECT);
        return;
    }
    new_node->next = graph->vertex_array[to].head;
    graph->vertex_array[to].head = new_node;
}

void log_error(char* function_name, ErrorType error_t)
{
    fprintf(stderr, "ERROR: %s at function '%s' at line %d in file %s\n", error_type(error_t), function_name, __LINE__, __FILE__);
}

char* error_type(ErrorType error_t)
{
    switch (error_t)
    {
    case MALLOC_ERR:     return "MALLOC ERROR";
    case NULL_OBJECT:    return "NULL OBJECT ERROR";
    default:             return "UNKNOWN ERROR";
    }
}

