#include "students.h"

Student *create_student(char *name, char *surname)
{
    Student *new_student = malloc(sizeof(Student));

    strcpy(new_student->name, name);
    strcpy(new_student->surname, surname);
    new_student->mean = 0.0f;
    for (short i = 0; i < 3; ++i)
        new_student->notes[i] = 0;
    for (short i = 0; i < 3; ++i)
        new_student->credits[i] = 0;
    
    return new_student;
}

States add_student(Student_DL **root, char *name, char *surname)
{
    Student_DL *cursor = *root;
    // if no root is present
    if (cursor == NULL)
    {
        cursor = malloc(sizeof(Student_DL));
        if (cursor == NULL) return MALLOC_ERR; // Malloc Error
        cursor->data = create_student(name, surname);
        cursor->prev = NULL;
        cursor->next = NULL;
        return SUCCESS;
    }

    // Traverse alphabethically
    while(cursor->next != NULL || strcmp(name, cursor->data->name) >= 0) cursor = cursor->next;
    
    // Create new node
    Student_DL *new_node = malloc(sizeof(Student_DL));
    if (new_node == NULL) return MALLOC_ERR; // Malloc Error

    // Create new student
    new_node->data = create_student(name, surname);
    
    // Pointer management
    cursor->next = new_node;
    new_node->prev = cursor;
    new_node->next = NULL;
    return SUCCESS;
}
