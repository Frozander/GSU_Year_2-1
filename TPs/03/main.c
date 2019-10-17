#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int main(int argc, char const *argv[])
{
    Tree* my_tree;
    
    my_tree = add_node(my_tree, "Turkey", 90);
    my_tree = add_node(my_tree, "USA", 1);
    my_tree = add_node(my_tree, "Germany", 49);
    my_tree = add_node(my_tree, "Argentina", 54);
    my_tree = add_node(my_tree, "Netherlands", 31);
    my_tree = add_node(my_tree, "France", 33);

    print_tree(my_tree);
    return 0;
}
