#ifndef __TREE_H_
#define __TREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define P_PREORDER   0
#define P_INORDER    1
#define P_POSTORDER  2
#define P_LEVELORDER 3

typedef struct tree
{
    int code;
    char* country;

    struct tree* left;
    struct tree* right;
} Tree;

Tree* add_node(Tree* root, char* new_name, int new_code);
void __tree_print(Tree* root, int convention);
void __2D_tree_printer(Tree* root, int space);
void print_tree(Tree* root, int convention);
void print_tree_2D(Tree* root);
Tree* findMin(Tree* root);
Tree* findMax(Tree* root);


#endif