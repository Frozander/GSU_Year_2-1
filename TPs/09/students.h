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
    F,
    D,
    CC,
    BB,
    BA,
    AA
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

// Technically is the same but exists just for consistent function definitions
typedef struct __student_bst
{
    Student *data;
    struct __student_bst *left;
    struct __student_bst *right;
} Student_BST;

States add_student(Student_DL **root, char *name, char *surname);
Student *create_student(char *name, char *surname);

float give_random_note();
int give_random_credits();

#endif