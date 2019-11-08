// Standard Library Headers
#include <stdlib.h>
#include <stdio.h>

// User Headers
#include "kd_tree.h"

KD_Tree* main_root = NULL;

int main(int argc, char const *argv[])
{
    int data[] = {28, 16};
    char name[] = "Cevahir Bedesteni - Merkez";
    char code = 'T';
    main_root = insert_node(main_root, code, name, data);

    // TESTING
    if (main_root == NULL)
    {
        printf("You just got prank'd bruh!\n");
        return 1;
    }

    KD_Tree *cursor = main_root;
    printf("%c)%s - (%d, %d)\n", code, name, cursor->data[0], cursor->data[1]);

    read_data("data.csv");
    
    return 0;
}