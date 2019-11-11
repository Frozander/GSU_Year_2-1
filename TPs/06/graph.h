#ifndef __GRAPH_USR_H_
#define __GRAPH_USR_H_

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

typedef enum __status_control
{
    SUCCESS,
    FAILURE
} StatusControl;

AdjMatrixNode **create_adj_matrix(int node_count);
AdjMatrixNode **add_connection(AdjMatrixNode **matrix, int node_count, char from, char to);
AdjMatrixNode **remove_connection(AdjMatrixNode **matrix, int node_count, char from, char to);

char sanitize_char(char c);
int code_to_index(char code);
char index_to_code(int index);


#endif