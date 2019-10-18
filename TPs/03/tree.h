#pragma once
#ifndef __TREE_H_
#define __TREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define P_PREORDER   0
#define P_INORDER    1
#define P_POSTORDER  2
#define P_LEVELORDER 3

#define LEVELORDER_STACK 512

typedef struct tree
{
    int code;
    char* country;

    struct tree* left;
    struct tree* right;
    // Only to be used by AVL
    int height;
} Tree;

typedef struct queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    Tree** data;
} Queue; 

// Tree Functions
Tree* add_node(Tree* root, char* new_name, int new_code);
void free_node(Tree* root);
Tree* remove_node(Tree* root, int target);
void __level_order_print(Tree* root, Queue* print_queue);
void __tree_print(Tree* root, int convention, Queue* print_queue);
void __2D_tree_printer(Tree* root, int space);
void print_tree(Tree* root, int convention, Queue* print_queue);
void print_tree_2D(Tree* root);
Tree* findMin(Tree* root);
Tree* findMax(Tree* root);

// Queue Functions
Queue* create_queue(unsigned capacity);
int is_full(Queue* queue);
int is_empty(Queue* queue);
void enqueue(Queue* queue, Tree* item);
Tree* dequeue(Queue* queue);
Tree* front(Queue* queue);
Tree* rear(Queue* queue);

// AVL Tree Functions

#endif