#include "kd_tree.h"

int coord_offset = 0;

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//           TREE FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

KD_Tree *create_node(int arg_count, char new_code, char *new_name, int *data_array)
{
    KD_Tree *new_node = malloc(sizeof(KD_Tree));
    if (new_node == NULL)
    {
        printf("Malloc Error at node creation\n");
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;

    // Insert door data
    new_node->door_code = new_code;
    strcpy(new_node->door_name, new_name);

    // Insert Coordinates
    int i;
    for (i = 0; i < arg_count; i++)
    {
        new_node->data[i] = data_array[i];
    }

    return new_node;
}

KD_Tree *insert_node(KD_Tree *root, char new_code, char *new_name, int *data_array)
{
    // Exit condition
    if (root == NULL)
    {
        KD_Tree *new_node = create_node(K_DIM, new_code, new_name, data_array);
        if (new_node == NULL) return NULL;
        root = new_node;
        return root;
    }

    // Recursion
    // NOTE: Used global variable coord_offset because didn't wanted to copy an int
    // to each recursion. Just for saving microseconds.
    if (data_array[coord_offset] < root->data[coord_offset])
    {
        coord_offset = (coord_offset + 1) % K_DIM;
        root->left = insert_node(root->left, new_code, new_name, data_array);
    }
    else
    {
        coord_offset = (coord_offset + 1) % K_DIM;
        root->right = insert_node(root->right, new_code, new_name, data_array);
    }
    coord_offset = 0;
    return root;
}

KD_Tree *init_tree(KD_Tree *root, char *filename)
{
    unsigned int l_count = line_counter(filename) - 1;
    Tree_Data *data_list = read_data(filename);

    for (unsigned int i = 0; i < l_count; i++)
    {
        // Inserts alphabethically since csv is alphabetically sorted already
        // So needs a sorting algorithm for inserting with different values
        root = insert_node(root, data_list[i].door_code, data_list[i].door_name, data_list[i].data);
    }
    return root;
}

void __tree_print(KD_Tree *root, int convention)
{
    // If statement for 3 recursive 1 iterative printing function
    if (convention == P_INORDER) // LNR
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        printf("%c ", root->door_code);
        __tree_print(root->right, convention);
    } else if (convention == P_POSTORDER) // LRN
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
        printf("%c ", root->door_code);
    } else if (convention == P_PREORDER) // NLR
    {
        if (root == NULL) return;
        printf("%c ", root->door_code);
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
    }
}

void print_tree(KD_Tree *root, int convention)
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
    
    __tree_print(root, convention);
    printf("\n");
}

KD_Tree *kill_tree(KD_Tree *root)
{
    if (root == NULL) return NULL;
    kill_tree(root->left);
    kill_tree(root->right);
    free(root);
    root = NULL;
}

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

// Unfortunately this function only works for my specific type of csv
Tree_Data *read_data(char *filename)
{
    unsigned int l_count = line_counter(filename);
    Tree_Data *data_list = malloc(sizeof(Tree_Data) * (l_count - 1));

    FILE *file_pointer;
    file_pointer = fopen(filename, "r");
    if (file_pointer == NULL)
    {
        printf("Could not open the file %s!", filename);
        return 0;
    }

    char line[LINE_MAX];
    char buffer[S_LEN];
    int i = 0;

    // Discard first line for now
    fgets(line, LINE_MAX, file_pointer);
    while (fgets(line, LINE_MAX, file_pointer) != NULL)
    {
        sscanf(line, "%c, %s, %d, %d", &data_list[i].door_code, data_list[i].door_name, &(data_list[i].data[0]), &(data_list[i].data[1]));
        i++;
    }
    fclose(file_pointer);
    return data_list;
}

unsigned int line_counter(char *filename)
{
    FILE *file_pointer;
    file_pointer = fopen(filename, "r");

    if (file_pointer == NULL)
    {
        printf("Could not open the file %s!", filename);
        return 0;
    }

    char c;
    unsigned int l_count = 0;
    for (c = getc(file_pointer); c != EOF; c = getc(file_pointer))
        if (c == '\n')
            ++l_count;

    fclose(file_pointer);
    return l_count;
}