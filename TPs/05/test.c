// Standard Library Headers
#include <stdlib.h>
#include <stdio.h>

// User Headers
#include "kd_tree.h"

KD_Tree* main_root = NULL;

int main(int argc, char const *argv[])
{
    int data[] = {6, 9};
    main_root = insert_node(main_root, data, 0);

    // TESTING
    if (main_root == NULL)
    {
        printf("You just got prank'd bruh!\n");
        return 1;
    }

    KD_Tree *cursor = main_root;
    printf("(%d, %d)\n", cursor->data[0], cursor->data[1]);
    
    return 0;
}