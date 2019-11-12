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
    {
        new_graph->vertex_array[i].head = NULL;
        new_graph->vertex_array[i].adj_count = 0;
    }
    return new_graph;   
}

void add_edge(Graph *graph, int from, int to)
{
    if (graph == NULL)
    {
        log_error("add_edge()", NULL_OBJECT_ERR);
        return;
    }

    AdjListNode *new_node = new_adj_list_node(to);
    if (new_node == NULL)
    {
        log_error("add_edge()", NULL_OBJECT_ERR);
        return;
    }

    new_node->next = graph->vertex_array[from].head; // Add linked list at 'from' to new_node
    graph->vertex_array[from].head = new_node;       // Then change linked list at 'from' to new_node's linked list
    graph->vertex_array[from].adj_count++;

    // Do the same for backwards
    new_node = new_adj_list_node(from);
    if (new_node == NULL)
    {
        log_error("add_edge()", NULL_OBJECT_ERR);
        return;
    }
    new_node->next = graph->vertex_array[to].head;
    graph->vertex_array[to].head = new_node;
    graph->vertex_array[to].adj_count++;

}

void print_graph(Graph *graph) 
{ 
    int vertex_index; 
    for (vertex_index = 0; vertex_index < graph->vertices; ++vertex_index) 
    { 
        AdjListNode *cursor = graph->vertex_array[vertex_index].head; 
        printf("\n%d ) ->", vertex_index); 
        while (cursor != NULL)
        { 
            printf("%d ->", cursor->destination); 
            cursor = cursor->next; 
        } 
        printf("\n"); 
    } 
}

Graph *matrix_to_graph(AdjMatrixNode **matrix, int node_count)
{
    Graph *new_graph = create_graph(node_count);
    for (size_t i = 0; i < node_count; ++i)
        for (size_t j = i; j < node_count; ++j)
            if (matrix[i][j].distance > 0)
                add_edge(new_graph, i, j);            
    return new_graph;    
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
            new_matrix[i][j].distance = NO_CONNECTION;
        }
    }
    return new_matrix;
}

AdjMatrixNode **add_connection(AdjMatrixNode **matrix, int node_count, int from, int to, float distance)
{
    if (from > node_count || to > node_count)
    {
        printf("Node does not exist");
        return matrix;
    }
    matrix[from][to].distance = distance;
}

AdjMatrixNode **remove_connection(AdjMatrixNode **matrix, int node_count, int from, int to)
{
    if (from > node_count || to > node_count)
    {
        printf("Node does not exist");
        return matrix;
    }
    matrix[from][to].distance = NO_CONNECTION;
}

AdjMatrixNode **create_matrix_from_data(char *filename)
{
    int node_count = line_counter(filename) - 1/* First line of the csv */;
    Sensor_Data *s_data = read_data(filename);

    if (s_data == NULL)
    {
        log_error("create_matrix_from_data()", NULL_OBJECT_ERR);
        return NULL;
    }

    AdjMatrixNode **new_matrix = create_adj_matrix(node_count);
    float distance;

    for (size_t i = 0; i < node_count; ++i)
        for (size_t j = 0; j < node_count; ++j)
            new_matrix[i][j].distance = is_connected(s_data[i], s_data[j], MAX_DIST);
    
    return new_matrix;
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

    char line[L_MAX];
    int i = 0;

    // Discard first line for now
    fgets(line, L_MAX, file_pointer);

    while (fgets(line, L_MAX, file_pointer) != NULL)
    {
        //printf("%s\n", line);
        sscanf(line, "%d,%f,%f,%f\n", &data_list[i].index, &data_list[i].x, &data_list[i].y, &data_list[i].z);
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
//       SENSOR DATA FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

float get_distance(Sensor_Data point1, Sensor_Data point2)
{
    return sqrtf(powf(point1.x - point2.x, 2) + powf(point1.y - point2.y, 2) + powf(point1.z - point2.z, 2));
}

float is_connected(Sensor_Data point1, Sensor_Data point2, float max)
{
    int distance = get_distance(point1, point2);
    if (distance <= max)
        return distance;
    else
        return 0;
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
    case MALLOC_ERR:         return "MALLOC ERROR";
    case NULL_OBJECT_ERR:    return "NULL OBJECT ERROR";
    case FILE_READ_ERR:      return "FILE READ ERROR";
    default:                 return "UNKNOWN ERROR";
    }
}