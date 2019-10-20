#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "tree.h"
#include "menu.h"

int main()
{
    int menu_state = 0;

    Tree* main_tree;

    Tree* temp;

    char input_str[30];
    int input_code;

    // for level order (declared outside function to prevent memory leaks and redeclarations with each call)
    Queue* print_queue = create_queue(LEVELORDER_STACK);

    // Add first values
    main_tree = add_avl_node(main_tree, "test1", 10);
    main_tree = add_avl_node(main_tree, "test2", 20);
    main_tree = add_avl_node(main_tree, "test3", 30);
    main_tree = add_avl_node(main_tree, "test4", 40);
    main_tree = add_avl_node(main_tree, "test5", 50);
    main_tree = add_avl_node(main_tree, "test6", 25);

    printf("Test Values added, current tree: \n");
    print_tree(main_tree, P_INORDER, print_queue);

    printf("Removing 40\n");
    main_tree = remove_avl_node(main_tree, 40);
    print_tree(main_tree, P_INORDER, print_queue);

    printf("Removing 20\n");
    main_tree = remove_avl_node(main_tree, 20);
    print_tree(main_tree, P_INORDER, print_queue);

    printf("Removing 25\n");
    main_tree = remove_avl_node(main_tree, 25);
    print_tree(main_tree, P_INORDER, print_queue);



    while (menu_state != M_EXIT)
    {
        printf("\n\n");
        switch (menu_state)
        {
        case M_MAIN:

            printf("1-Add Country\n");
            printf("2-Remove Country\n");
            printf("3-Find Max and Min Country\n");
            printf("4-Print Countries\n");
            printf("5-EXIT\n");

            scanf("%d", &menu_state);
            break;
        
        case M_ADD:

            printf("Country Name: ");
            scanf("%s", input_str);
            printf("Country Code: ");
            scanf("%d", &input_code);

            main_tree = add_avl_node(main_tree, input_str, input_code);          

            menu_state = M_MAIN;
            break;

        case M_DEL:

            printf("Code of the country to delete: ");
            scanf("%d", &input_code);
            main_tree = remove_avl_node(main_tree, input_code);
            
            menu_state = M_MAIN;
            break;

        case M_SRCH:
            
            temp = findMin(main_tree);
            printf("Min: %d - %s\n", temp->code, temp->country);
            temp = findMax(main_tree);
            printf("Max: %d - %s\n", temp->code, temp->country);

            menu_state = M_MAIN;
            break;

        case M_PRNT:

            printf("Select Notation: ");
            scanf("%s", input_str);
            int i = 0;
            // SANITIZE
            while (input_str[i] != '\0')
            {
                input_str[i] = tolower(input_str[i]);
                i++;
            }
            
            if (strcmp(input_str, "postorder") == 0)
            {
                print_tree(main_tree, P_POSTORDER, print_queue);
            } else if (strcmp(input_str, "inorder") == 0)
            {
                print_tree(main_tree, P_INORDER, print_queue);
            } else if (strcmp(input_str, "preorder") == 0)
            {
                print_tree(main_tree, P_PREORDER, print_queue);
            } else if (strcmp(input_str, "levelorder") == 0)
            {
                print_tree(main_tree, P_LEVELORDER, print_queue);
            } else
            {
                printf("Possible notations: postorder - inorder - preorder - levelorder");
            }

            menu_state = M_MAIN;
            break;

        case M_EXIT:
            printf("Exiting!\n");
            break;
        
        default:
            printf("Unknown Input, reseting menu!\n");

            menu_state = M_MAIN;
            break;
        }

        
    }
    
    return 0;
}
