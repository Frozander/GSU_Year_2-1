#include "kd_tree.h"

KD_Tree *create_node(int arg_count, ...)
{
    KD_Tree *new_node = malloc(sizeof(KD_Tree));
    if (new_node == NULL)
    {
        printf("Malloc Error at node creation\n");
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;
    
    va_list vl;
    int i;

    va_start(vl, arg_count);
    for (i = 0; i < arg_count; i++)
    {
        new_node->data[i] = va_arg(vl, int);
    }
    va_end(vl);
    
    return new_node;
}