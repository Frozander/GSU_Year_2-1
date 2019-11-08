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

StatusControl insert_node(KD_Tree** root, int* data_array)
{
    KD_Tree* cursor = (*root);
    KD_Tree* new_node = create_node(K_DIM, data_array);
    if (new_node == NULL) return NULL_ERR;

    if (cursor == NULL)
    {
        cursor = new_node;
        return INSERT;
    }

    int i = 0;
    while (cursor)
    {
        if (new_node->data[i] < cursor->data[i])
            cursor = cursor->left;
        else
            cursor = cursor->right;

        i = (i + 1) % K_DIM;
    }
    cursor = new_node;
    return INSERT;
}

