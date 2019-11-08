#ifndef __KD_TREE_H
#define __KD_TREE_H

#include <stdlib.h>
#include <stdio.h>

#ifndef K_DIM
    #define K_DIM 2
#endif

typedef struct kd_tree
{
    int data[K_DIM];
    struct kd_tree *left;
    struct kd_tree *right;
} KD_Tree;

KD_Tree *create_node(int arg_count, int* data_array);
KD_Tree *insert_node(KD_Tree* root, int* data_array, int coord);

#endif