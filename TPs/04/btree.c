#include "btree.h"


B_Tree* add_node(B_Tree* root, char* new_name, int new_code)
{
    // Create new node if current root is empty
    if (root == NULL)
    {
        root = malloc(sizeof(B_Tree));
        root->data[0] = new_code;
        return root;
    }
    // Recursively add
    if (root->code < new_code)
        root->right = add_node(root->right, new_name, new_code);
    else if (root->code > new_code)
        root->left = add_node(root->left, new_name, new_code);
    return root;
}

void free_node(B_Tree* root)
{
    free(root);
}

B_Tree* remove_node(B_Tree* root, int target)
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
            B_Tree* temp = root->right;
            free_node(root);
            return temp;
        } else if (root->right == NULL)
        {
            B_Tree* temp = root->left;
            free_node(root);
            return temp;
        }
        // For node with two children
        // Find the best node on the right side of current node
        B_Tree* temp = findMin(root->right);
        // Copy it to current node;
        // Remove the best node on the right to avoid duplicates
        root->right = remove_node(root->right, temp->code);
    }
    return root;
}

B_Tree* search_node(int target)
{

}

void __level_order_print(B_Tree* root, Queue* print_queue)
{
    B_Tree* cursor = root;

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

void __tree_print(B_Tree* root, int convention, Queue* print_queue)
{
    // If statement for 3 recursive 1 iterative printing function
    if (convention == P_INORDER) // LNR
    {
        if (root == NULL) return;
        __tree_print(root->left, convention, print_queue);
        printf("%d ", root->code);
        __tree_print(root->right, convention, print_queue);
    } else if (convention == P_POSTORDER) // LRN
    {
        if (root == NULL) return;
        __tree_print(root->left, convention, print_queue);
        __tree_print(root->right, convention, print_queue);
        printf("%d ", root->code);
    } else if (convention == P_PREORDER) // NLR
    {
        if (root == NULL) return;
        printf("%d ", root->code);
        __tree_print(root->left, convention, print_queue);
        __tree_print(root->right, convention, print_queue);
    } else if (convention == P_LEVELORDER)
    {
        __level_order_print(root, print_queue);
        return;
    }
}

// Wrapper for __tree_print which also wraps __level_order_print
void print_tree(B_Tree* root, int convention, Queue* print_queue)
{
    if (convention < 0 || convention > 3)
    {
        printf("Invalid Convention\n");
        return;
    }
    
    printf("\nTree in ");
    if (convention == P_INORDER)
        printf("INORDER: ");
    if (convention == P_POSTORDER)
        printf("POSTORDER: ");
    if (convention == P_PREORDER)
        printf("PREORDER: ");
    if (convention == P_LEVELORDER)
        printf("LEVELORDER: ");
    
    
    __tree_print(root, convention, print_queue);
    printf("\n");
}

B_Tree* findMin(B_Tree* root)
{
    while (root->left != NULL)
        root = root->left;
    return root;    
}

B_Tree* findMax(B_Tree* root)
{
    while (root->right != NULL)
        root = root->right;
    return root;    
}

/*
  .--.      .-'.      .--.      .--.      .--.      .--.      .`-.      .--.
:::::.\::::::::.\::::::::. QUEUE FUNCS ::::::.\::::::::.\::::::::.\::::::::.\
'      `--'      `.-'      `--'      `--'      `--'      `-.'      `--'      `
*/

Queue* create_queue(unsigned capacity)
{ 
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->data = malloc(queue->capacity * sizeof(B_Tree*));
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

void enqueue(Queue* queue, B_Tree* item)
{
    if (is_full(queue))
        return;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size = queue->size + 1;
}

B_Tree* dequeue(Queue* queue)
{ 
    if (is_empty(queue)) 
        return NULL;
    B_Tree* item = queue->data[queue->front]; 
    queue->front = (queue->front + 1) % queue->capacity; 
    queue->size = queue->size - 1; 
    return item;
}

B_Tree* front(Queue* queue)
{ 
    if (is_empty(queue)) 
        return NULL; 
    return queue->data[queue->front]; 
}

B_Tree* rear(Queue* queue)
{ 
    if (is_empty(queue)) 
        return NULL; 
    return queue->data[queue->rear]; 
}
