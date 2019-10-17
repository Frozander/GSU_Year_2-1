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

void __tree_print(Tree* root, int convention)
{
    if (convention == P_INORDER)
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        printf("%d ", root->code);
        __tree_print(root->right, convention);
    } else if (convention == P_POSTORDER)
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
        printf("%d ", root->code);
    } else if (convention == P_PREORDER)
    {
        if (root == NULL) return;
        printf("%d ", root->code);
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
    } else if (convention == P_LEVELORDER)
    {
        return;
    }
}

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

// Wrapper for __tree_print
void print_tree(Tree* root, int convention)
{
    if (convention <= 0 || convention >= 3)
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

