#include "Contact.h"

Contact* create_contact(char* name, char* surname, char* city, char* homeNumber)
{
    Contact* new_contact = malloc(sizeof(Contact));

    new_contact->name = strdup(name);
    new_contact->surname = strdup(surname);
    new_contact->city = strdup(city);
    new_contact->homeNumber = strdup(homeNumber);

    return new_contact;
}

City* create_city(char* city, int code)
{
    City* new_city = malloc(sizeof(City));

    new_city->city = malloc(sizeof(char) * NAME_MAX);

    strcpy(new_city->city, city);
    new_city->code = code;

    return new_city;
}

void free_contact(Contact* input)
{
    free(input->name);
    free(input->surname);
    free(input->city);
    free(input->homeNumber);
    free(input);
}

void print_contact(Contact* input, City* location)
{
    printf("Name       : %s", input->name);
    printf("Surname    : %s", input->name);
    printf("City       : %s", input->name);
    printf("Home Number: %d %s", location->code, input->name);
}

void print_city(City* input)
{
    printf("City Name  : %s", input->city);
    printf("City Code  : %d", input->code);
}
