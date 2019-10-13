#include "_CONTACT/Contact.h"
#include "_SL/SList.h"
#include "_DL/DList.h"

SContactList* s_Contacts = NULL;
SCityList* s_Cities = NULL;
int isCircular = 0;

int main(int argc, char const *argv[])
{
    char name_1[NAME_MAX] = "Batuhan";
    char surname_1[NAME_MAX] = "Ceylan";
    char city_1[NAME_MAX] = "Balikesir";
    char homeNumber_1[NUM_MAX]  = "7507777";

    char name_2[NAME_MAX] = "XDDXD";
    char surname_2[NAME_MAX] = "LULW";
    char city_2[NAME_MAX] = "ASDASD";
    char homeNumber_2[NUM_MAX]  = "4564564";

    int code_1 = 555;
    int code_2 = 123;

    // WORKS
    City* c_1 = create_city(city_1, code_1);
    City* c_2 = create_city(city_2, code_2);

    // WORKS
    Contact* contact_1 = create_contact(name_1, surname_1, city_1, homeNumber_1);
    //Contact* contact_2 = create_contact(name_2, surname_2, city_2, homeNumber_2);

    //add_city_sl(s_Cities, c_1, isCircular);
    //add_city_sl(s_Cities, c_2, isCircular);


    //printf("%s\n%d\n", cursor->data->city, cursor->data->code);
    int check = add_contact_sl(s_Contacts, contact_1, isCircular);
    //add_contact_sl(s_Contacts, contact_2, isCircular);
    printf(check? "PASSED" : "FAILED");
    SContactList* cursor = s_Contacts;
    printf("%s\n%s\n%s\n%s\n", contact_1->name, contact_1->surname, contact_1->city, contact_1->homeNumber);
    printf("%s\n", cursor->data->name);
    //cursor = cursor->next;
    //printf("%s\n%s\n%s\n%s\n", cursor->data->name, cursor->data->surname, cursor->data->city, cursor->data->homeNumber);
    //cursor = cursor->next;
    

    return 0;
}
