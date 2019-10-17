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

void print_tree(Tree* root)
{
    if (root == NULL) return;
    print_tree(root->left);
    printf("%d ", root->code);
    print_tree(root->right);
    
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
