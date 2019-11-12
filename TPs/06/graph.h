#ifndef __GRAPH_USR_H_
#define __GRAPH_USR_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define MAX_DIST 30

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


//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         ADJ MATRIX FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

#define NO_CONNECTION 0
#define CONNECTION 1

typedef struct __adj_matrix_node
{
    float distance;
} AdjMatrixNode;

AdjMatrixNode **create_adj_matrix(int node_count);
AdjMatrixNode **add_connection(AdjMatrixNode **matrix, int node_count, int from, int to, float distance);
AdjMatrixNode **remove_connection(AdjMatrixNode **matrix, int node_count, int from, int to);
AdjMatrixNode **create_matrix_from_data(char *filename);
void print_graph(Graph *graph);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

typedef struct __sensor_data
{
    int index;
    float x, y, z;
} Sensor_Data;

#define L_MAX 256

Sensor_Data *read_data(char *filename);
unsigned int line_counter(char *filename);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//       SENSOR DATA FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

float get_distance(Sensor_Data point1, Sensor_Data point2);
float is_connected(Sensor_Data point1, Sensor_Data point2, float max);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//       ERROR LOGGING FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

typedef enum __error_types
{
    MALLOC_ERR,
    NULL_OBJECT_ERR,
    FILE_READ_ERR
} ErrorType;

void log_error(char* function_name, ErrorType error_type);
char* error_type(ErrorType);

#endif