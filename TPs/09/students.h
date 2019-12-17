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

// A struct that holds notes and identification of a student
// Includes:
//  char    name[NAME_LEN_MAX]
//  char    surname[NAME_LEN_MAX]
//  int     credits[3]
//  float   notes[3]
//  float   mean
//  Use create_student(char *name, char *surname) to create a student instance
//  Or use add_student(Student_DL **root, char *name, char *surname) to add a student to
//  a Double-Linked List
typedef struct __student
{
    char  name[NAME_LEN_MAX];
    char  surname[NAME_LEN_MAX];
    int   credits[3];
    float   notes[3];
    char  char_grades[3][3];
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

// Takes a numerical grade in the interval [0, 100]
// and returns a string containging one of the following:
//  [00 - 50)  -> "F"
//  [50 - 60)  -> "CC"
//  [60 - 70)  -> "CB"
//  [70 - 80)  -> "BB"
//  [80 - 90)  -> "BA"
//  [90 - 100] -> "AA"
// For unexpected values (e.g. -3, 132) the function returns: "NaN"
char *num_to_char_grade(float num_grade);

float encrypt_student_mean(float mean, char key1, char key2);
float decrypt_student_mean(float mean, char key1, char key2);

States add_tree_node(Student_BST **root, Student *student_data);
Student_BST *feed_to_tree(Student_DL *DL_list);

void means_with_threshold(Student_DL *DL_list, float threshold);

#endif