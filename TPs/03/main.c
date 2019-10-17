#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int main(int argc, char const *argv[])
{
    Tree* my_tree;
    
    my_tree = add_node(my_tree, "Turkey", 90);
    my_tree = add_node(my_tree, "USA", 1);
    my_tree = add_node(my_tree, "Germany", 49);
    my_tree = add_node(my_tree, "Greece", 30);
    my_tree = add_node(my_tree, "Argentina", 54);
    my_tree = add_node(my_tree, "Netherlands", 31);
    my_tree = add_node(my_tree, "France", 33);
    my_tree = add_node(my_tree, "England", 44);
    my_tree = add_node(my_tree, "Ispanya", 34);

    print_tree(my_tree);
    printf("\n");

    Tree *min = findMin(my_tree);
    Tree *max = findMax(my_tree);
    
    printf("Max: %d - %s\n", max->code, max->country);
    printf("Min: %d - %s\n", min->code, min->country);
    
    return 0;
}
