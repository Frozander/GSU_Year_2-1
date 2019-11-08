#ifndef __KD_TREE_H
#define __KD_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define S_LEN 30
#ifndef K_DIM
    #define K_DIM 2
#endif

typedef struct kd_tree
{
    char door_code;
    char door_name[S_LEN];
    int data[K_DIM];

    struct kd_tree *left;
    struct kd_tree *right;
} KD_Tree;

KD_Tree *create_node(int arg_count, char new_code, char* new_name, int* data_array);
KD_Tree *insert_node(KD_Tree* root, char new_code, char* new_name, int* data_array);

#endif