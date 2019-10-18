#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "tree.h"
#include "menu.h"

int main()
{
    /*
      _______ ______  _____ _______ _____ 
     |__   __|  ____|/ ____|__   __/ ____|
        | |  | |__  | (___    | | | (___  
        | |  |  __|  \___ \   | |  \___ \ 
        | |  | |____ ____) |  | |  ____) |
        |_|  |______|_____/   |_| |_____/ 
    
    Tree* my_tree;
    
    my_tree = add_node(my_tree, "Turkey", 90);
    my_tree = add_node(my_tree, "USA", 1);
    my_tree = add_node(my_tree, "Germany", 49);
    my_tree = add_node(my_tree, "Greece", 30);
    my_tree = add_node(my_tree, "Argentina", 54);
    my_tree = add_node(my_tree, "Ispanya", 34);

    print_tree(my_tree, P_POSTORDER);
    printf("\n");
    printf("\n");
    
    my_tree = remove_node(my_tree, 49);

    print_tree(my_tree, P_POSTORDER);
    printf("\n");


    Tree *min = findMin(my_tree);
    Tree *max = findMax(my_tree);
    
    printf("Max: %d - %s\n", max->code, max->country);
    printf("Min: %d - %s\n", min->code, min->country);

    printf("\n");
    printf("\n");

    print_tree(my_tree, P_LEVELORDER);
    */

    int menu_state = 0;

    Tree* main_tree;

    Tree* temp;

    char input_str[30];
    int input_code;

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

            main_tree = add_node(main_tree, input_str, input_code);          

            menu_state = M_MAIN;
            break;

        case M_DEL:

            printf("Code of the country to delete: ");
            scanf("%d", &input_code);
            main_tree = remove_node(main_tree, input_code);
            
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
                print_tree(main_tree, P_POSTORDER);
            } else if (strcmp(input_str, "inorder") == 0)
            {
                print_tree(main_tree, P_INORDER);
            } else if (strcmp(input_str, "preorder") == 0)
            {
                print_tree(main_tree, P_PREORDER);
            } else if (strcmp(input_str, "levelorder") == 0)
            {
                print_tree(main_tree, P_LEVELORDER);
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
