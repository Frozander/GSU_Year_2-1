#ifndef __SLIST_H_
#define __SLIST_H_

#include <stdlib.h>
#include <stdio.h>

#include "../_CONTACT/Contact.h"

typedef struct sContactList
{
    Contact* data;
    struct sContactList* next;
} SContactList;

typedef struct sCityList
{
    City* data;
    struct sCityList* next;
} SCityList;

// return 1 on success, 0 on fail
int add_contact_sl(SContactList* head, char* name, char* surname, char* city, char* homeNumber, int isCircular);
int add_city_sl(SCityList* head, City* new_city, int isCircular);
// return 1 on success, 0 on fail
int remove_contact_sl(SContactList* head, char* name, char* surname, int isCircular);
int remove_city_sl(SCityList* head, char* city_name, int isCircular);
// return data on success, NULL if fail
Contact* search_contact_sl(SContactList* head, char* name, char* surname, int isCircular);
City* search_city_sl(SCityList* head, char* city_name, int isCircular);
// prints whole list, stops when next == NULL or next == head (when circular)
void print_contact_sl(SContactList* head, SCityList* location, int isCircular);
void print_city_sl(SCityList* head, int isCircular);

#endif