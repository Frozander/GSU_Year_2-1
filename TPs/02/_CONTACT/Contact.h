#ifndef __CONTACT_H_
#define __CONTACT_H_

#define NAME_MAX 25
#define NUM_MAX 15

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct contact
{
    char* name;
    char* surname;
    char* city;
    char* homeNumber;
} Contact;

typedef struct city
{
    char* city;
    int code;
} City;

Contact* create_contact(char* name, char* surname, char* city, char* homeNumber);
City* create_city(char* city, int code);

void free_contact(Contact* input);

void print_contact(Contact* input, City* location);
void print_city(City* input);
//Contact functions need to be declared at each type unfortunately

#endif