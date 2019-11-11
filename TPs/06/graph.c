#include "graph.h"


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

AdjMatrixNode **add_connection(AdjMatrixNode **matrix, int node_count, char from, char to)
{
    int d_from = code_to_index(sanitize_char(from));
    int d_to   = code_to_index(sanitize_char(to));

    if (d_from > node_count || d_to > node_count)
    {
        printf("Node does not exist");
        return matrix;
    }
    matrix[d_from][d_to].connection = CONNECTION;
}

AdjMatrixNode **remove_connection(AdjMatrixNode **matrix, int node_count, char from, char to)
{
    
}


char sanitize_char(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
}

int code_to_index(char code)
{
    return (int) code - 97;
}

char index_to_code(int index)
{
    return (char) index + 97;
}