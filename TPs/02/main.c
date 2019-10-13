#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./_CONTACT/Contact.h"
#include "./_DL/Dlist.h"
#include "./_SL/Slist.h"
// Adds defines
#include "defines.h"

// Bool checker
int check = SUCCESS;

// For function calls;
int S_or_D = 0;
int isCircular = 0;

// Event handler (the most primitive)
int menu_state = M_MAIN;

// For SL/SC
SCityList* s_Cities;
SContactList* s_Contacts;

// For DL/DC
DCityList* d_Cities;
DContactList* d_Contacts;

// Input Variables
char i_name[NAME_MAX];
char i_surname[NAME_MAX];
char i_city[NAME_MAX];
char i_homeNumber[NUM_MAX];
int i_code = 0;

// For search
Contact* found_contact;
City* found_city;

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./Agenda (SL/SC/DL/DC)\n");
        return 1;
    }
    if (!strcmp(argv[1], "SL"))
    {
        isCircular = 0;
        S_or_D = SLIST;
    } else if (!strcmp(argv[1], "SC"))
    {
        isCircular = 1;
        S_or_D = SLIST;
    } else if (!strcmp(argv[1], "DL"))
    {
        isCircular = 0;
        S_or_D = DLIST;
    } else if (!strcmp(argv[1], "DC"))
    {
        isCircular = 1;
        S_or_D = DLIST;
    } else
    {
        printf("Unrecognised Token! Exiting...\n");
        return 2;
    }
    printf("You choose, %s\n", argv[1]);
    
    /*
    <<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>
                SWITCH CASE
    <<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>
    */

    while (1)
    {
        printf("\n\n\n\n");
        switch (menu_state)
        {
        case M_MAIN:
            printf("1. Add Contact\n");
            printf("2. Add City\n");
            printf("3. Delete Contact\n");
            printf("4. Delete City\n");
            printf("5. Search Contact\n");
            printf("6. Search City\n");
            printf("7. Print Contacts\n");
            printf("8. Print City\n");
            printf("9. Exit\n");

            scanf("%d", &menu_state);
            break;
        
        case M_A_CON:

            printf("Name: ");
            scanf("%s", i_name);
            printf("Surname: ");
            scanf("%s", i_surname);
            printf("City: ");
            scanf("%s", i_city);
            printf("Home Number: ");
            scanf("%s", i_homeNumber);
            
            Contact* new_contact = create_contact(i_name, i_surname, i_city, i_homeNumber);

            if (S_or_D == SLIST)
                check = add_contact_sl(s_Contacts, new_contact, isCircular);
            else
                check = add_contact_dl(d_Contacts, new_contact, isCircular);

            menu_state = M_MAIN;

        break;
        
        case M_A_CIT:
            printf("City: ");
            scanf("%s", i_city);
            printf("Code: ");
            scanf("%d", &i_code);

            City* new_city = create_city(i_city, i_code);

            if (S_or_D == SLIST)
                check = add_city_sl(s_Cities, new_city, isCircular);
            else
                check = add_city_dl(d_Cities, new_city, isCircular);
            
            menu_state = M_MAIN;
            
        break;
        
        case M_D_CON:
            printf("Enter the name and surname of the contact: ");
            scanf("%s %s", i_name, i_surname);

            if (S_or_D == SLIST)
                check = remove_contact_sl(s_Contacts, i_name, i_surname, isCircular);
            else
                check = remove_contact_dl(d_Contacts, i_name, i_surname, isCircular);
            
            menu_state = M_MAIN;
        break;
        
        case M_D_CIT:
            printf("Enter the name of the city: ");
            scanf("%s", i_city);

            if (S_or_D == SLIST)
                check = remove_city_sl(s_Cities, i_city, isCircular);
            else
                check = remove_city_dl(d_Cities, i_city, isCircular);

            menu_state = M_MAIN;
        break;
        
        case M_S_CON:
            printf("Enter the name and surname of the contact: ");
            scanf("%s %s", i_name, i_surname);
            
            if (S_or_D == SLIST)
            {
                found_contact = search_contact_sl(s_Contacts, i_name, i_surname, isCircular);
                found_city = search_city_sl(s_Cities, i_city, isCircular);
            }
            else
            {
                found_contact = search_contact_dl(d_Contacts, i_name, i_surname, isCircular);
                found_city = search_city_dl(d_Cities, i_city, isCircular);
            }
            
            if (found_contact != NULL)
                print_contact(found_contact, found_city);
            else 
                check = FAIL;
            
            menu_state = M_MAIN;
        break;
        
        case M_S_CIT:
            printf("Enter the name of the city: ");
            scanf("%s", i_city);

            if (S_or_D == SLIST)
                found_city = search_city_sl(s_Cities, i_city, isCircular);
            else
                found_city = search_city_dl(d_Cities, i_city, isCircular);
            
            if (found_city != NULL)
                print_city(found_city);
            else 
                check = FAIL;
            
            menu_state = M_MAIN;
        break;
        
        case M_P_CON:
            if (S_or_D == SLIST)
                print_contact_sl(s_Contacts, s_Cities, isCircular);
            else
                print_contact_dl(d_Contacts, d_Cities, isCircular);

            menu_state = M_MAIN;
        break;
        
        case M_P_CIT:
            if (S_or_D == SLIST)
                print_city_sl(s_Cities, isCircular);
            else
                print_city_dl(d_Cities, isCircular);
            
            menu_state = M_MAIN;
        break;
        
        case M_EXIT:
            printf("Exiting...\n");
            return 0;
        break;
        
        default:
            printf("Unrecognised menu event! Reseting menu...\n");
            menu_state = M_MAIN;
        break;
        }

        if (check == SUCCESS && menu_state == M_MAIN)
            printf("Operation Completed!\n");
        else if (check == FAIL)
            printf("Operation Failed!\n");
    }
    return 0;
}