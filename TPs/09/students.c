#include "students.h"

Student *create_student(char *name, char *surname)
{
    Student *new_student = malloc(sizeof(Student));
    if (new_student == NULL) return NULL; // Malloc check
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

Student_DL *add_student(Student_DL *root, Student *student_data)
{
    Student_DL *cursor = root;
    // if no root is present
    if (cursor == NULL)
    {
        cursor = malloc(sizeof(Student_DL));
        if (cursor == NULL) return NULL; // Malloc Error
        cursor->data = student_data;
        cursor->prev = NULL;
        cursor->next = NULL;
        return cursor;
    }

    // Create new node
    Student_DL *new_node = malloc(sizeof(Student_DL));
    if (new_node == NULL) return NULL; // Malloc Error
    // Create new student
    new_node->data = student_data;
    if (new_node->data == NULL) return NULL;

    // If first value is smaller than head
    if (strcmp(student_data->name, root->data->name) <= 0)
    {
        new_node->next = root;
        new_node->prev = NULL; // Just in case
        new_node->next->prev = new_node;
        root = new_node;
        return root;
    }

    // Traverse alphabethically
    while(cursor->next != NULL && strcmp(student_data->name, cursor->next->data->name) > 0) cursor = cursor->next;
    
    // Insert in the right spot (Hopefully...)
    new_node->next = cursor->next;
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
    
    cursor->next = new_node;
    new_node->prev = cursor;
    return root;
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
        default        : return "!!";
    }
}

Student_BST *add_tree_node(Student_BST *root, Student *student_data)
{
    if (root == NULL)
    {
        root = malloc(sizeof(Student_BST));
        root->data = student_data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    if(strcmp(student_data->name, root->data->name) >= 0)
        root->right = add_tree_node(root->right, student_data);
    else
        root->left = add_tree_node(root->left, student_data);
    return root;
}

Student_BST *feed_to_tree(Student_DL *DL_list)
{
    Student_BST *new_tree = NULL;

    while (DL_list != NULL)
    {
        new_tree = add_tree_node(new_tree, DL_list->data);
        DL_list = DL_list->next;
    }
    return new_tree;
}

void print_tree_inorder(Student_BST *root)
{
    if(root == NULL) return;
    print_tree_inorder(root->left);
    print_student(root->data);
    print_tree_inorder(root->right);
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
    printf("\n");
    printf("Name   : %s\n", student_data->name);
    printf("Surname: %s\n", student_data->surname);
    printf("Grades : English[%d]->(%-3.2f, %2s) Maths[%d]->(%-3.2f, %2s) Physics[%d]->(%-3.2f, %2s)\n",
            student_data->credits[0], student_data->notes[0], student_data->char_grades[0],
            student_data->credits[1], student_data->notes[1], student_data->char_grades[1],
            student_data->credits[2], student_data->notes[2], student_data->char_grades[2]);
    printf("Mean   : %-3.2f\n", decrypt_student_mean(student_data->mean, student_data->name[0], student_data->surname[0]));
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
