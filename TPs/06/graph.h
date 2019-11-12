#ifndef __GRAPH_USR_H_
#define __GRAPH_USR_H_

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef enum __error_types
{
    MALLOC_ERR,
    NULL_OBJECT
} ErrorType;

typedef struct __adj_list_node 
{ 
    int destination; 
    struct __adj_list_node *next; 
} AdjListNode;

typedef struct __adj_list 
{ 
    AdjListNode *head;  
} AdjList;

typedef struct __graph
{
    int vertices;
    AdjList *vertex_array;
} Graph;

AdjListNode *new_adj_list_node(int destination);
Graph *create_graph(int vertices);
void add_edge(Graph *graph, int from, int to);

void log_error(char* function_name, ErrorType error_type);
char* error_type(ErrorType);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         ADJ MATRIX FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

#define START 0
#define TARGET -1
#define NO_CONNECTION 0
#define CONNECTION 1
#define INFINITY INT_MAX

typedef struct __adj_matrix_node
{
    int connection;
    int distance;
} AdjMatrixNode;

AdjMatrixNode **create_adj_matrix(int node_count);
AdjMatrixNode **add_connection(AdjMatrixNode **matrix, int node_count, int from, int to);
AdjMatrixNode **remove_connection(AdjMatrixNode **matrix, int node_count, int from, int to);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

typedef struct __sensor_data
{
    int index;
    float x, y, z;
} Sensor_Data;

#define LINE_MAX 256

Sensor_Data *read_data(char *filename);
unsigned int line_counter(char *filename);



#endif