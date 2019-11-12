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

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         ADJ MATRIX FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

AdjMatrixNode **create_adj_matrix(int node_count)
{
    AdjMatrixNode **new_matrix = malloc(sizeof(AdjMatrixNode*) * node_count);
    for (int i = 0; i < node_count; i++)
    {
        new_matrix[i] = malloc(sizeof(AdjMatrixNode) * node_count);
        for (int j = 0; j < node_count; j++)
        {
            new_matrix[i][j].connection = NO_CONNECTION;
            new_matrix[i][j].distance = INFINITY;
        }
    }
    return new_matrix;
}

AdjMatrixNode **add_connection(AdjMatrixNode **matrix, int node_count, int from, int to)
{

    if (from > node_count || to > node_count)
    {
        printf("Node does not exist");
        return matrix;
    }
    matrix[from][to].connection = CONNECTION;
}

AdjMatrixNode **remove_connection(AdjMatrixNode **matrix, int node_count, int from, int to)
{
    if (from > node_count || to > node_count)
    {
        printf("Node does not exist");
        return matrix;
    }
    matrix[from][to].connection = NO_CONNECTION;
}

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

// Unfortunately this function only works for my specific type of csv
Sensor_Data *read_data(char *filename)
{
    unsigned int l_count = line_counter(filename);
    Sensor_Data *data_list = malloc(sizeof(Sensor_Data) * (l_count - 1));

    FILE *file_pointer;
    file_pointer = fopen(filename, "r");
    if (file_pointer == NULL)
    {
        printf("Could not open the file %s!", filename);
        return 0;
    }

    char line[LINE_MAX];
    int i = 0;

    // Discard first line for now
    fgets(line, LINE_MAX, file_pointer);
    const char s[2] = ", ";
    char *token;

    while (fgets(line, LINE_MAX, file_pointer) != NULL)
    {
        token = strtok(line, s);
        sscanf(token, "%d", &data_list[i].index);
        token = strtok(NULL, s);
        data_list[i].x = atof(token);
        token = strtok(NULL, s);
        data_list[i].y = atof(token);
        token = strtok(NULL, s);
        data_list[i].z = atof(token);
        ++i;
    }
    fclose(file_pointer);
    return data_list;
}

unsigned int line_counter(char *filename)
{
    FILE *file_pointer;
    file_pointer = fopen(filename, "r");

    if (file_pointer == NULL)
    {
        printf("Could not open the file %s!", filename);
        return 0;
    }

    char c;
    unsigned int l_count = 0;
    for (c = getc(file_pointer); c != EOF; c = getc(file_pointer))
        if (c == '\n')
            ++l_count;

    fclose(file_pointer);
    return l_count;
}

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//       ERROR LOGGING FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

void log_error(char* function_name, ErrorType error_t)
{
    fprintf(stderr, "ERROR: %s at function '%s' at line %d in file %s\n",
            error_type(error_t), function_name, __LINE__, __FILE__);
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