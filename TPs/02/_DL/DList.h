#ifndef __DLIST_H_
#define __DLIST_H_

#include <stdlib.h>
#include <stdio.h>

#include "../_CONTACT/Contact.h"

typedef struct dContactList
{
    Contact* data;
    struct dContactList* prev;
    struct dContactList* next;
} DContactList;

typedef struct dCityList
{
    City* data;
    struct dCityList* prev;
    struct dCityList* next;
} DCityList;

// return 1 on success, 0 on fail
int add_contact_dl(DContactList* head, Contact* new_contact, int isCircular);
int add_city_dl(DCityList* head, City* new_city, int isCircular);
// return 1 on success, 0 on fail
int remove_contact_dl(DContactList* head, char* name, char* surname, int isCircular);
int remove_city_dl(DCityList* head, char* city_name, int isCircular);
// return data on success, NULL if fail
Contact* search_contact_dl(DContactList* head, char* name, char* surname, int isCircular);
City* search_city_dl(DCityList* head, char* city_name, int isCircular);
// prints whole list, stops when next == NULL or next == head (when circular)
void print_contact_dl(DContactList* head, DCityList* location, int isCircular);
void print_city_dl(DCityList* head, int isCircular);

#endif