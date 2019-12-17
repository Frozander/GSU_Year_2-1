#include "students.h"

Student *create_student(char *name, char *surname)
{
    Student *new_student = malloc(sizeof(Student));
    int total_credits = 0;
    strcpy(new_student->name, name);
    strcpy(new_student->surname, surname);
    new_student->mean = 0.0f;
    for (short i = 0; i < 3; ++i)
    {
        new_student->notes[i] = give_random_note();
        strcpy(new_student->char_grades[i], num_to_char_grade(new_student->notes[i]));
    }
    for (short i = 0; i < 3; ++i)
    {
        new_student->credits[i] = give_random_credits();
        total_credits += new_student->credits[i];
        new_student->mean += (new_student->credits[i] * new_student->notes[i]);
    }
    new_student->mean /= (float) total_credits;
    new_student->mean = encrypt_student_mean(new_student->mean, name[0], surname[0]);
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
    if (cursor->prev == NULL)
    {
        cursor->prev = new_node;
        new_node->prev = NULL;
        new_node->next = cursor;
        (*root) = new_node;
        return SUCCESS;
    } else
    {
        new_node->next = cursor->next;
        cursor->next = new_node;
        new_node->prev = cursor;
        if (new_node->next != NULL)
            new_node->next->prev = new_node; 
        return SUCCESS;
    }
    return FAIL;
}

float give_random_note()
{
    return (float) (rand() % 201) / 2.0f;
}

int give_random_credits()
{
    return (rand() % 3) + 3;
}

char *num_to_char_grade(float num_grade)
{
    switch ((int) num_grade)
    {
        case  0 ... 49 : return "F";
        case 50 ... 59 : return "CC";
        case 60 ... 69 : return "CB";
        case 70 ... 79 : return "BB";
        case 80 ... 89 : return "BA";
        case 90 ... 100: return "AA";
        default        : return "NaN";
    }
}

States add_tree_node(Student_BST **root, Student *student_data)
{
    Student_BST *head = (*root);
    if (head == NULL)
    {
        head = malloc(sizeof(Student_BST));
        head->data = student_data;
        head->left = NULL;
        head->right = NULL;
        return SUCCESS;
    }

    int err;
    if(strcmp(head->data->name, student_data->name) >= 0)
        err = add_tree_node(&(head->right), student_data);
    else
        err = add_tree_node(&(head->left), student_data);
    return err;
}

Student_BST *feed_to_tree(Student_DL *DL_list)
{
    Student_BST *new_tree;
    States err;

    while (DL_list != NULL)
    {
        if (err != SUCCESS) return NULL; // Not really a good way of dealing with errors
        err = add_tree_node(&new_tree, DL_list->data);
        DL_list = DL_list->next;
    }
    return new_tree;
}

float encrypt_student_mean(float mean, char key1, char key2)
{
    return mean * (key1 * key2);
}

float decrypt_student_mean(float mean, char key1, char key2)
{
    return mean / (key1 * key2);
}

void print_student(Student *student_data)
{
    printf("Name   : %30s\n", student_data->name);
    printf("Surname: %30s\n", student_data->surname);
    printf("Grades : English[%d]->(%-3.2f, %2s) Maths[%d]->(%-3.2f, %2s) Physics[%d]->(%-3.2f, %2s)\n",
            student_data->credits[0], student_data->notes[0], student_data->char_grades[0],
            student_data->credits[1], student_data->notes[1], student_data->char_grades[1],
            student_data->credits[2], student_data->notes[2], student_data->char_grades[2]);
    printf("Mean   : %-3.2f", decrypt_student_mean(student_data->mean, student_data->name[0], student_data->surname[0]));
}

void means_with_threshold(Student_DL *DL_list, float threshold)
{
    while (DL_list != NULL)
    {
        if(decrypt_student_mean(DL_list->data->mean, DL_list->data->name[0], DL_list->data->surname[0]) > threshold)
            print_student(DL_list->data);
        DL_list = DL_list->next;
    }
}
