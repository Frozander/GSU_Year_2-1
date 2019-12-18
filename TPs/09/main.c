// Checks if case range used in note_to_grade function is supported by the compiler
#if (defined(__GNUC__) ||defined(__GNUG__) || defined(__clang__))
    #define HAS_GNU_CLANG
#endif

#if defined(_MSC_VER) && defined(__INTEL_COMPILER)
    #define HAS_MSVC_OR_INTEL
#endif

#if (defined(HAS_GNU_CLANG) && !defined(HAS_MSVC_OR_INTEL))
    #define CASE_RANGE_SUPPORT
#endif
// Error if not
#ifndef CASE_RANGE_SUPPORT
    #error "Your compiler does not support ranges in switch-case statements. Use GCC or Clang... Or manually change the switch case into a series of if-else statements"
#endif

// C standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Internal Headers
#include "students.h"

int main()
{   
    srand(clock());
    int state = -1;
    float mean = -1.0f;
    Student *student_data = NULL;
    Student_DL *list = NULL;
    Student_BST *tree = NULL;
    char name[NAME_LEN_MAX];
    char surname[NAME_LEN_MAX];

    printf("Welcome to student adding revision TP...\n\n");
    printf("The program adds every student to both a DL List and a BST Tree\n");
    printf("Each student has their mean encrypted in case of a possible data leak\n");
    printf("However I/O functions handle the encryption/decryption for the user\n");
    printf("Known Issue: Since strcmp is case sensitive, upper case strings always come before lower case strings\n");

    while (1)
    {
        printf("\n\n");
        printf("1) Add a student with random grades\n");
        printf("2) Display students with average above a threshold\n");
        printf("3) Display all students\n");
        printf("4) Exit\n");

        printf("\nInput: ");
        scanf("%d", &state);

        if (state == 1) {
            printf("\nName Surname: ");
            scanf("%s %s", name, surname);
            
            student_data = create_student(name, surname);

            list = add_student(list, student_data);
            tree = add_tree_node(tree, student_data);
            printf("\nStudent Added!\n");
            state = -1;
        } else if (state == 2)
        {
            printf("\nMinimum Mean of Grades: ");
            scanf("%f", &mean);
            printf("\nHere are students with higher mean grade than %f:\n", mean);
            means_with_threshold(list, mean);
            state = -1;
        } else if (state == 3)
        {
            printf("\nDisplaying all students:\n");
            print_tree_inorder(tree);
            state = -1;
        } else if (state == 4)
        {
            break;
        } else
        {
            printf("Unrecognised input!\n Reseting the menu!\n\n");
            state = -1;
        }
    }

    printf("\n\nExiting...\n");
    
    return 0;
}
