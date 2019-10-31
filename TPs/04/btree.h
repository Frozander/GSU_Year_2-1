#pragma once
#ifndef __B_TREE_H_
#define __B_TREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define P_PREORDER   0
#define P_INORDER    1
#define P_POSTORDER  2
#define P_LEVELORDER 3

#define LEVELORDER_STACK 512
#define MAX_SIZE 2

typedef struct b_tree
{
    int data_size;
    int data[MAX_SIZE];

    struct b_tree* leafs[MAX_SIZE + 1];
} B_Tree;

typedef struct queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    B_Tree** data;
} Queue; 

// B Tree Functions
B_Tree* add_node(B_Tree* root, int new_data);
void free_node(B_Tree* root);
B_Tree* remove_node(B_Tree* root, int target);
B_Tree* search_node(int target);
void __tree_print(B_Tree* root, int convention, Queue* print_queue);
void print_tree(B_Tree* root, int convention, Queue* print_queue);
void print_tree_2D(B_Tree* root);
B_Tree* findMin(B_Tree* root);
B_Tree* findMax(B_Tree* root);

// Queue Functions
Queue* create_queue(unsigned capacity);
int is_full(Queue* queue);
int is_empty(Queue* queue);
void enqueue(Queue* queue, B_Tree* item);
B_Tree* dequeue(Queue* queue);
B_Tree* front(Queue* queue);
B_Tree* rear(Queue* queue);

#endif