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

#define S_CODE  0
#define S_NAME  1
#define S_COORD 2

typedef struct kd_tree
{
    char door_code;
    char door_name[S_LEN];
    int data[K_DIM];

    struct kd_tree *left;
    struct kd_tree *right;
} KD_Tree;

typedef struct queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    KD_Tree** data;
} Queue;

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
KD_Tree *init_tree(KD_Tree *root, Tree_Data *data_list, int len);
void __tree_print(KD_Tree *root, int convention);
void print_tree(KD_Tree *root, int convention);
void print_node(KD_Tree *root);
KD_Tree *kill_tree(KD_Tree *root);
KD_Tree *__search_index(KD_Tree *root, char key, Queue **queue);
KD_Tree *__search_name(KD_Tree *root, char *key, Queue **queue);
KD_Tree *__search_coordinate(KD_Tree *root, int *key, Queue **queue);
KD_Tree *search_kdtree(KD_Tree *root, int token, Queue **queue);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//           QUEUE FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢
Queue *create_queue(unsigned capacity);
int is_full(Queue *queue);
int is_empty(Queue *queue);
void enqueue(Queue *queue, KD_Tree *item);
KD_Tree *dequeue(Queue *queue);
KD_Tree *front(Queue *queue);
KD_Tree *rear(Queue *queue);
void empty_queue(Queue *queue);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢
#define LINE_MAX 256

Tree_Data *read_data(char *filename);
unsigned int line_counter(char *filename);

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         TREE DATA FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

typedef enum sort_type
{
    COORD_X,
    COORD_Y,
    NAME,
    CODE
} SortType;

Tree_Data *sort_data(Tree_Data *data_list, SortType type, int len);
int __compare_COORDX(const void * a, const void * b);
int __compare_COORDY(const void * a, const void * b);
int __compare_CODE(const void * a, const void * b);
int __compare_NAME(const void * a, const void * b);

#endif