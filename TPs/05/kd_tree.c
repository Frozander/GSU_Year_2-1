#include "kd_tree.h"

int coord_offset = 0;

KD_Tree *create_node(int arg_count, char new_code, char* new_name, int* data_array)
{
    KD_Tree *new_node = malloc(sizeof(KD_Tree));
    if (new_node == NULL)
    {
        printf("Malloc Error at node creation\n");
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;

    // Insert door data
    new_node->door_code = new_code;
    strcpy(new_node->door_name, new_name);
    
    // Insert Coordinates
    int i;
    for (i = 0; i < arg_count; i++)
    {
        new_node->data[i] = data_array[i];
    }
    
    return new_node;
}

KD_Tree *insert_node(KD_Tree* root, char new_code, char* new_name, int* data_array)
{
    // Exit condition
    if (root == NULL)
    {
        KD_Tree* new_node = create_node(K_DIM, new_code, new_name, data_array);
        if (new_node == NULL) return NULL;
        root = new_node;
        return root;
    }

    // Recursion
    // NOTE: Used global variable coord_offset because didn't wanted to copy an int
    // to each recursion. Just for saving microseconds.
    if (data_array[coord_offset] < root->data[coord_offset])
    {
        coord_offset = (coord_offset + 1) % K_DIM;
        root->left = insert_node(root->left, new_code, new_name, data_array);
    }
    else
    {
        coord_offset = (coord_offset + 1) % K_DIM;
        root->right = insert_node(root->right, new_code, new_name, data_array);
    }
    coord_offset = 0;
    return root;
}