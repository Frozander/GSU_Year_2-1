#include "tree.h"

Tree* add_node(Tree* root, char* new_name, int new_code)
{
    // Create new node if current root is empty
    if (root == NULL)
    {
        root = malloc(sizeof(Tree));
        root->code = new_code;
        root->country = strdup(new_name);
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    // Recursively add
    if (root->code < new_code)
    {
        root->right = add_node(root->right, new_name, new_code);
        return root;
    } else if (root->code >= new_code)
    {
        root->left = add_node(root->left, new_name, new_code);
        return root;
    }
    return NULL;
}

void free_node(Tree* root)
{
    free(root->country);
    free(root);
}

Tree* remove_node(Tree* root, int target)
{
    // Exit case
    if (root == NULL) return root;
    
    // Find the node to delete
    if (target < root->code)
        root->left = remove_node(root->left, target);
    else if (target > root->code)
        root->right = remove_node(root->right, target);
    else // When the node is found, check left and right for single child nodes
    {
        if (root->left == NULL)
        {
            Tree* temp = root->right;
            free_node(root);
            return temp;
        } else if (root->right == NULL)
        {
            Tree* temp = root->left;
            free_node(root);
            return temp;
        }
        // For node with two children
        // Find the smallest node on the right side of current node
        Tree* temp = findMin(root->right);
        // Copy it to current node;
        root->code = temp->code;
        free(root->country);
        root->country = strdup(temp->country);
        // Remove the smallest node on the right to avoid duplicates
        root->right = remove_node(root->right, temp->code);
    }
    return root;
}

void __level_order_print(Tree* root)
{
    Queue* print_queue = create_queue(LEVELORDER_STACK);
    Tree* cursor = root;

    // Print Current level
    // Enqueue left, right nodes (next level)
    // Dequeue each node, one by one
    // Repeat until NULL
    while (cursor != NULL)
    {
        printf("%d ", cursor->code);

        if (cursor->left != NULL)
            enqueue(print_queue, cursor->left);
        if (cursor->right != NULL)
            enqueue(print_queue, cursor->right);

        cursor = dequeue(print_queue);                
    }
    
    
}

void __tree_print(Tree* root, int convention)
{
    // If statement for 3 recursive 1 iterative printing function
    if (convention == P_INORDER) // LNR
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        printf("%d ", root->code);
        __tree_print(root->right, convention);
    } else if (convention == P_POSTORDER) // LRN
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
        printf("%d ", root->code);
    } else if (convention == P_PREORDER) // NLR
    {
        if (root == NULL) return;
        printf("%d ", root->code);
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
    } else if (convention == P_LEVELORDER)
    {
        __level_order_print(root);
        return;
    }
}

// NOT MY CODE, USED ONLY FOR VISUALISATION AND CHECKING IF MY FUNCTIONS WORK AS INTENDED
void __2D_tree_printer(Tree* root, int space)
{
    if (root == NULL) return;

    space += 10;

    __2D_tree_printer(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->code);

    __2D_tree_printer(root->left, space);    
    
}

// Wrapper for __2D_tree_printer
void print_tree_2D(Tree* root)
{
    __2D_tree_printer(root, 0);
}

// Wrapper for __tree_print which also wraps __level_order_print
void print_tree(Tree* root, int convention)
{
    if (convention <= 0 || convention > 3)
    {
        printf("Invalid Convention");
        return;
    }
    
    printf("Tree in ");
    if (convention == P_INORDER)
        printf("INORDER:\n");
    if (convention == P_POSTORDER)
        printf("POSTORDER:\n");
    if (convention == P_PREORDER)
        printf("PREORDER:\n");
    if (convention == P_LEVELORDER)
        printf("LEVELORDER:\n");
    
    __tree_print(root, convention);
    printf("\n");
}

Tree* findMin(Tree* root)
{
    while (root->left != NULL)
        root = root->left;
    return root;    
}

Tree* findMax(Tree* root)
{
    while (root->right != NULL)
        root = root->right;
    return root;    
}

/*
  .--.      .-'.      .--.      .--.      .--.      .--.      .`-.      .--.
:::::.\::::::::.\::::::::.\QUEUE FUNCS:::::::.\::::::::.\::::::::.\::::::::.\
'      `--'      `.-'      `--'      `--'      `--'      `-.'      `--'      `
*/

Queue* create_queue(unsigned capacity)
{ 
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->data = malloc(queue->capacity * sizeof(Tree*));
    return queue; 
} 

int is_full(Queue* queue) 
{
    return (queue->size == queue->capacity);
}

int is_empty(Queue* queue)
{
    return (queue->size == 0);
}

void enqueue(Queue* queue, Tree* item)
{
    if (is_full(queue))
        return;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size = queue->size + 1;
}

Tree* dequeue(Queue* queue)
{ 
    if (is_empty(queue)) 
        return NULL;
    Tree* item = queue->data[queue->front]; 
    queue->front = (queue->front + 1) % queue->capacity; 
    queue->size = queue->size - 1; 
    return item;
}

Tree* front(Queue* queue)
{ 
    if (is_empty(queue)) 
        return NULL; 
    return queue->data[queue->front]; 
}

Tree* rear(Queue* queue)
{ 
    if (is_empty(queue)) 
        return NULL; 
    return queue->data[queue->rear]; 
} 