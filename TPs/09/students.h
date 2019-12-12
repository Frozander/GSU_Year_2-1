#ifndef __USR_STUDENT_H_
#define __USR_STUDENT_H_

#include <stdlib.h>
#include <string.h>

#define NAME_LEN_MAX 50

typedef enum __states
{
    SUCCESS,
    FAIL,
    MALLOC_ERR,
} States;

typedef enum __note_bottom 
{
    AA,
    BB,
    CB,
    CC,
    D,
    F
} Note;

typedef struct __student
{
    char  name[NAME_LEN_MAX];
    char  surname[NAME_LEN_MAX];
    int   credits[3];
    int   notes[3];
    float mean;
} Student;

typedef struct __student_list
{
    Student *data;
    struct __student_list *prev;
    struct __student_list *next;
} Student_DL;

States add_student(Student_DL **root, char *name, char *surname);
Student *create_student(char *name, char *surname);

#endif