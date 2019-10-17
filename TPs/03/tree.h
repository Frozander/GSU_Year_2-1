#ifndef __TREE_H_
#define __TREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tree
{
    int code;
    char* country;

    struct tree* left;
    struct tree* right;
} Tree;

Tree* add_node(Tree* root, char* new_name, int new_code);
void print_tree(Tree* root);
Tree* findMin(Tree* root);
Tree* findMax(Tree* root);


#endif