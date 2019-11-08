#include "kd_tree.h"

KD_Tree *create_node(int arg_count, int* data_array)
{
    KD_Tree *new_node = malloc(sizeof(KD_Tree));
    if (new_node == NULL)
    {
        printf("Malloc Error at node creation\n");
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;
    
    int i;

    for (i = 0; i < arg_count; i++)
    {
        new_node->data[i] = data_array[i];
    }
    
    return new_node;
}

KD_Tree *insert_node(KD_Tree* root, int* data_array, int coord)
{

    if (root == NULL)
    {
        KD_Tree* new_node = create_node(K_DIM, data_array);
        if (new_node == NULL) return NULL;
        root = new_node;
        return root;
    }

    if (data_array[coord] < root->data[coord])
        root->left = insert_node(root->left, data_array, (coord + 1) % K_DIM);
    else
        root->right = insert_node(root->right, data_array, (coord + 1) % K_DIM);
    return root;
}

