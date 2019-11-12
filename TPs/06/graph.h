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


#endif