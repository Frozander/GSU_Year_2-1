#include "SList.h"

// return 1 on success, 0 on fail
int add_contact_sl(SContactList* head, char* name, char* surname, char* city, char* homeNumber, int isCircular)
{
    SContactList* cursor = head;
    if (cursor == NULL)
    {
        cursor = malloc(sizeof(SContactList));
        if (cursor == NULL) return 0;

        cursor->data = malloc(sizeof(Contact));

        cursor->data->name = malloc(sizeof(char) * NAME_MAX);
        cursor->data->surname = malloc(sizeof(char) * NAME_MAX);
        cursor->data->city = malloc(sizeof(char) * NAME_MAX);
        cursor->data->homeNumber = malloc(sizeof(char) * NUM_MAX);

        strcpy(cursor->data->name, name);
        strcpy(cursor->data->surname, surname);
        strcpy(cursor->data->city , city);
        strcpy(cursor->data->homeNumber, homeNumber);

        if (isCircular == 1)
            cursor->next = cursor;
        else
            cursor->next = NULL;
        return 1;
    }

    /*
    SContactList* new_node = malloc(sizeof(SContactList));
    if (new_node == NULL) return 0;
    new_node->data = new_contact;

    if (isCircular == 0)
    {
        if (cursor->next == NULL)
        {
            cursor->next = new_node;
        } else
        {
            while (cursor->next != NULL)
            {
                if (strcmp(cursor->data->surname, new_contact->surname) <= 0)
                {
                    new_node->next = cursor->next;
                    cursor->next = new_node;
                    return 1;
                }
                cursor = cursor->next;
            }
            cursor->next = new_node;
            return 1;
        }
        
    } else
    {
        if (head->next == head)
        {
            head->next = new_node;
            new_node->next = head;
            return 1;
        }
        else
        {
            while (cursor->next != head)
            {
                if (strcmp(cursor->data->surname, new_contact->surname) <= 0)
                {
                    new_node->next = cursor->next;
                    cursor->next = new_node;
                    return 1;
                }
                cursor = cursor->next;
            }
            new_node->next = cursor->next;
            cursor->next = new_node;
            return 1;
        }
    }
    */
}

int add_city_sl(SCityList* head, City* new_city, int isCircular)
{
    if (head == NULL)
    {
        head = malloc(sizeof(SCityList));
        if (head == NULL) return 0;
        head->data = new_city;
        if (isCircular == 1) head->next = head;
        else head->next = NULL;
        return 1;
    }

    SCityList* cursor = head;
    SCityList* new_node = malloc(sizeof(SCityList));
    if (new_node == NULL) return 0;
    new_node->data = new_city;

    if (isCircular == 0)
    {
        while (cursor != NULL && strcmp(new_node->data->city, cursor->data->city) >= 0)
            cursor = cursor->next;
    } else
    {
        while (cursor != head && strcmp(new_node->data->city, cursor->data->city) >= 0)
            cursor = cursor->next;
    }

    new_node->next = cursor->next;
    cursor->next = new_node;
    return 1;
}
// return 1 on success, 0 on fail
int remove_contact_sl(SContactList* head, char* name, char* surname, int isCircular)
{
    SContactList* cursor = head;
    SContactList* prev;
    if (cursor == NULL) return 0;
    while (strcmp(cursor->data->name, name) != 0 && strcmp(cursor->data->surname, surname) != 0)
    {
        if(cursor == NULL) return 0;
        prev = cursor;
        cursor = cursor->next;
    }

    prev->next = cursor->next;
    cursor->next = NULL;

    // Free all values, I guess?
    free(cursor->data->name);
    free(cursor->data->surname);
    free(cursor->data->city);
    free(cursor->data->homeNumber);
    free(cursor->data);
    free(cursor);
    return 1;
}

int remove_city_sl(SCityList* head, char* city_name, int isCircular)
{
    SCityList* cursor = head;
    SCityList* prev;
    if (cursor == NULL) return 0;
    while (strcmp(cursor->data->city, city_name) != 0)
    {
        if(cursor == NULL) return 0;
        prev = cursor;
        cursor = cursor->next;
    }

    prev->next = cursor->next;
    cursor->next = NULL;

    // Free all values, I guess?
    free(cursor->data->city);
    free(cursor->data);
    free(cursor);
    return 1;
}

// return data on success, NULL if fail
Contact* search_contact_sl(SContactList* head, char* name, char* surname, int isCircular)
{
    SContactList* cursor = head;
    if (cursor == NULL) return NULL;
    while (strcmp(cursor->data->name, name) != 0 && strcmp(cursor->data->surname, surname) != 0)
    {
        if(cursor == NULL) return NULL;
        cursor = cursor->next;
    }

    return cursor->data;
}

City* search_city_sl(SCityList* head, char* city_name, int isCircular)
{
    SCityList* cursor = head;
    if (cursor == NULL) return 0;
    while (strcmp(cursor->data->city, city_name) != 0)
    {
        if(cursor == NULL) return 0;
        cursor = cursor->next;
    }

    return cursor->data;
}
// prints whole list, stops when next == NULL or next == head (when circular)
void print_contact_sl(SContactList* head, SCityList* location, int isCircular)
{
    SContactList* cursor = head;
    if (cursor == NULL) return;
    City* current_city;
    if (isCircular == 0)
    {
        while (cursor != NULL)
        {
            printf("\n");
            current_city = search_city_sl(location, cursor->data->city, isCircular);
            print_contact(cursor->data, current_city);
            cursor = cursor->next;
        }
    } else
    {
        do
        {
            printf("\n");
            current_city = search_city_sl(location, cursor->data->city, isCircular);
            print_contact(cursor->data, current_city);
            cursor = cursor->next;
        } while (cursor != head);
    }
}

void print_city_sl(SCityList* head, int isCircular)
{
    SCityList* cursor = head;
    if (cursor == NULL) return;
    if (isCircular == 0)
    {
        while (cursor != NULL)
        {
            printf("\n");
            print_city(cursor->data);
            cursor = cursor->next;
        }
    } else
    {
        do
        {
            printf("\n");
            print_city(cursor->data);
            cursor = cursor->next;
        } while (cursor != head);
    }
}