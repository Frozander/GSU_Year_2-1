// Standard Library Headers
#include <stdlib.h>
#include <stdio.h>

// User Headers
#include "kd_tree.h"

KD_Tree* main_root = NULL;
Queue* main_search_queue = NULL;

int main(int argc, char const *argv[])
{
    // TESTING
    main_root = init_tree(main_root, "data.csv");
    main_search_queue = create_queue(512);

    print_tree(main_root, P_PREORDER);
    
    // SEARCH TEST
    char key_c_1 = 'L';
    char key_c_2 = 'A';
    char *key_s_1 = "Haci_Husnu";
    char *key_s_2 = "Kurkculer";
    int key_d_1[] = {5, 33};
    int key_d_2[] = {32, 29};

    print_node(search_kdtree(main_root, S_CODE, &main_search_queue));
    print_node(search_kdtree(main_root, S_NAME, &main_search_queue));
    print_node(search_kdtree(main_root, S_COORD, &main_search_queue));


    return 0;
}