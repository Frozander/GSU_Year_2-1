#include "DList.h"

// return 1 on success, 0 on fail
int add_contact_dl(DContactList* head, Contact* new_contact, int isCircular)
{
    DContactList* cursor = head;
    if (head == NULL)
    {
        head = malloc(sizeof(DContactList));
        if (head == NULL) return 0;
            head->data = new_contact;
        if (isCircular == 1) 
        {
            head->next = head;
            head->prev = head;
        }
        else
        {
            head->next = NULL;
            head->prev = NULL;
        }
        return 1;
    }

    DContactList* new_node = malloc(sizeof(DContactList));
    if (new_node == NULL) return 0;
    new_node->data = new_contact;

    if (isCircular == 0)
    {
        while (cursor != NULL && strcmp(new_node->data->surname, cursor->data->surname) >= 0)
            cursor = cursor->next;
    } else
    {
        while (cursor != head && strcmp(new_node->data->surname, cursor->data->surname) >= 0)
            cursor = cursor->next;
    }

    new_node->next = cursor->next;
    cursor->next = new_node;
    return 1;
}

int add_city_dl(DCityList* head, City* new_city, int isCircular)
{
    DCityList* cursor = head;
    if (cursor == NULL)
    {
        cursor = malloc(sizeof(DCityList));
        if (cursor == NULL) return 0;
        cursor->data = new_city;
        if (isCircular == 1) cursor->next = cursor;
        else cursor->data = NULL;
        return 1;
    }

    DCityList* new_node = malloc(sizeof(DCityList));
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
int remove_contact_dl(DContactList* head, char* name, char* surname, int isCircular)
{
    DContactList* cursor = head;
    DContactList* prev;
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

int remove_city_dl(DCityList* head, char* city_name, int isCircular)
{
    DCityList* cursor = head;
    DCityList* prev;
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
Contact* search_contact_dl(DContactList* head, char* name, char* surname, int isCircular)
{
    DContactList* cursor = head;
    if (cursor == NULL) return NULL;
    while (strcmp(cursor->data->name, name) != 0 && strcmp(cursor->data->surname, surname) != 0)
    {
        if(cursor == NULL) return NULL;
        cursor = cursor->next;
    }

    return cursor->data;
}

City* search_city_dl(DCityList* head, char* city_name, int isCircular)
{
    DCityList* cursor = head;
    if (cursor == NULL) return 0;
    while (strcmp(cursor->data->city, city_name) != 0)
    {
        if(cursor == NULL) return 0;
        cursor = cursor->next;
    }

    return cursor->data;
}
// prints whole list, stops when next == NULL or next == head (when circular)
void print_contact_dl(DContactList* head, DCityList* location, int isCircular)
{
    DContactList* cursor = head;
    if (cursor == NULL) return;
    City* current_city;
    if (isCircular == 0)
    {
        while (cursor != NULL)
        {
            printf("\n");
            current_city = search_city_dl(location, cursor->data->city, isCircular);
            print_contact(cursor->data, current_city);
            cursor = cursor->next;
        }
    } else
    {
        do
        {
            printf("\n");
            current_city = search_city_dl(location, cursor->data->city, isCircular);
            print_contact(cursor->data, current_city);
            cursor = cursor->next;
        } while (cursor != head);
    }
}

void print_city_dl(DCityList* head, int isCircular)
{
    DCityList* cursor = head;
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