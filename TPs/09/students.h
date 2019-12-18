#ifndef __USR_STUDENT_H_
#define __USR_STUDENT_H_

#include <stdlib.h>
#include <stdio.h>
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

// Combines all other auxhilary functions for grading,
// encryption and calculation to create a student
// with random grades.
Student *create_student(char *name, char *surname);

// Inserts a stundent with random grades into a Double Linked List
Student_DL *add_student(Student_DL *root, char *name, char *surname);

// Auxhilary function to give a random grade between [0 - 100] to a student
float give_random_note();
// Auxhilary function to give a random credit weight for a class
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

// Auxhilary function that encrypts a floating point value (intended to use for means)
// using 2 char values (preferably first letters of a students name and surname)
float encrypt_student_mean(float mean, char key1, char key2);
// Auxhilary function that decrypts a floating point value (intended to use for means)
// using 2 char values (preferably first letters of a students name and surname)
float decrypt_student_mean(float mean, char key1, char key2);

// Inserts a stundent with random grades into a Binary Search Tree
Student_BST *add_tree_node(Student_BST *root, Student *student_data);
// Feeds student data from a Double Linked List to a Binary Search Tree
Student_BST *feed_to_tree(Student_DL *DL_list);

// Prints all the data from a Student struct
void print_student(Student *student_data);
// Prints out the students with higher mean than the threshold
// The function decrypts the value inside it.
void means_with_threshold(Student_DL *DL_list, float threshold);

#endif