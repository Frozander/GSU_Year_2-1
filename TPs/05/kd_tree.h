#ifndef __KD_TREE_H
#define __KD_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define S_LEN 30
#ifndef K_DIM
    #define K_DIM 2
#endif

#define P_PREORDER   0
#define P_INORDER    1
#define P_POSTORDER  2

typedef struct kd_tree
{
    char door_code;
    char door_name[S_LEN];
    int data[K_DIM];

    struct kd_tree *left;
    struct kd_tree *right;
} KD_Tree;

typedef struct tree_data
{
    char door_code;
    char door_name[S_LEN];
    int data[K_DIM];
} Tree_Data;


//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//           TREE FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢
KD_Tree *create_node(int arg_count, char new_code, char *new_name, int *data_array);
KD_Tree *insert_node(KD_Tree *root, char new_code, char *new_name, int *data_array);
KD_Tree *init_tree(KD_Tree *root, char *filename);
void __tree_print(KD_Tree *root, int convention);
void print_tree(KD_Tree *root, int convention);
void kill_tree(KD_Tree *root);
//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢
#define LINE_MAX 256

Tree_Data* read_data(char *filename);
unsigned int line_counter(char *filename);
#endif