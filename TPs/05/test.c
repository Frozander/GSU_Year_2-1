// Standard Library Headers
#include <stdlib.h>
#include <stdio.h>

// User Headers
#include "kd_tree.h"

KD_Tree* main_root = NULL;

int main(int argc, char const *argv[])
{
    // TESTING
    int l_count = line_counter("data.csv");
    Tree_Data* data_list = read_data("data.csv");

    main_root = init_tree(main_root, "data.csv");
    print_tree(main_root, P_INORDER);

    
    return 0;
}