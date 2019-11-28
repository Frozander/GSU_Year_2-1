#include "kd_tree.h"

int coord_offset = 0;

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//           TREE FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

KD_Tree *create_node(int arg_count, char new_code, char *new_name, int *data_array)
{
    KD_Tree *new_node = malloc(sizeof(KD_Tree));
    if (new_node == NULL)
    {
        printf("Malloc Error at node creation\n");
        return NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;

    // Insert door data
    new_node->door_code = new_code;
    strcpy(new_node->door_name, new_name);

    // Insert Coordinates
    int i;
    for (i = 0; i < arg_count; i++)
    {
        new_node->data[i] = data_array[i];
    }

    return new_node;
}

KD_Tree *insert_node(KD_Tree *root, char new_code, char *new_name, int *data_array)
{
    // Exit condition
    if (root == NULL)
    {
        KD_Tree *new_node = create_node(K_DIM, new_code, new_name, data_array);
        if (new_node == NULL) return NULL;
        root = new_node;
        return root;
    }

    // Recursion
    // NOTE: Used global variable coord_offset because didn't wanted to copy an int
    // to each recursion. Just for saving microseconds.
    if (data_array[coord_offset] < root->data[coord_offset])
    {
        coord_offset = (coord_offset + 1) % K_DIM;
        root->left = insert_node(root->left, new_code, new_name, data_array);
    }
    else
    {
        coord_offset = (coord_offset + 1) % K_DIM;
        root->right = insert_node(root->right, new_code, new_name, data_array);
    }
    coord_offset = 0;
    return root;
}

// Reads from a Tree_Data struct and fills the root pointer. Frees data_list afterwards.
KD_Tree *init_tree(KD_Tree *root, Tree_Data *data_list, int len)
{
    for (unsigned int i = 0; i < len; i++)
    {
        // Inserts alphabethically since csv is alphabetically sorted already
        // So needs a sorting algorithm for inserting with different values
        printf("%c)%s - (%d, %d)\n", data_list[i].door_code, data_list[i].door_name, data_list[i].data[0], data_list[i].data[1]);
        root = insert_node(root, data_list[i].door_code, data_list[i].door_name, data_list[i].data);
    }
    free(data_list);
    return root;
}

void __tree_print(KD_Tree *root, int convention)
{
    // If statement for 3 recursive 1 iterative printing function
    if (convention == P_INORDER) // LNR
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        printf("%c ", root->door_code);
        __tree_print(root->right, convention);
    } else if (convention == P_POSTORDER) // LRN
    {
        if (root == NULL) return;
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
        printf("%c ", root->door_code);
    } else if (convention == P_PREORDER) // NLR
    {
        if (root == NULL) return;
        printf("%c ", root->door_code);
        __tree_print(root->left, convention);
        __tree_print(root->right, convention);
    }
}

void print_tree(KD_Tree *root, int convention)
{
    if (convention < 0 || convention > 3)
    {
        printf("Invalid Convention\n");
        return;
    }
    
    printf("\nTree in ");
    if (convention == P_INORDER)
        printf("INORDER: ");
    if (convention == P_POSTORDER)
        printf("POSTORDER: ");
    if (convention == P_PREORDER)
        printf("PREORDER: ");
    
    __tree_print(root, convention);
    printf("\n");
}

void print_node(KD_Tree *root)
{
    if (root == NULL)
        return;    
    printf("%c)%s - (%d, %d)\n", root->door_code, root->door_name, root->data[0], root->data[1]);
}

KD_Tree *kill_tree(KD_Tree *root)
{
    if (root == NULL) return NULL;
    kill_tree(root->left);
    kill_tree(root->right);
    free(root);
    root = NULL;
}

/*  IMPORTANT:
    Use of the __funcname type funtions alone is not advised since
    they don't have neccesary sanity checks which are done in wrapper funtions.
*/
KD_Tree *__search_index(KD_Tree *root, char key, Queue **queue)
{
    Queue* q_cursor = *queue;
    while (root != NULL)
    {
        if (root->door_code == key)
            return root;
        
        enqueue(q_cursor, root->left);
        enqueue(q_cursor, root->right);
        root = dequeue(q_cursor);
    }
    printf("Could not find the key: %c\n", key);
    return NULL;
}

KD_Tree *__search_name(KD_Tree *root, char *key, Queue **queue)
{
    Queue* q_cursor = *queue;
    while (root != NULL)
    {
        if (strcmp(root->door_name, key) == 0)
            return root;
        
        enqueue(q_cursor, root->left);
        enqueue(q_cursor, root->right);
        root = dequeue(q_cursor);
    }
    printf("Could not find the key: %s\n", key);
    return NULL;
}

/*  TODO:
    I need to change this to use the insertion method to find the coordinate
    in a more efficient way. But this is a just in case solution which was easy
    to port from other search methods.
*/
KD_Tree *__search_coordinate(KD_Tree *root, int *key, Queue **queue)
{
    Queue* q_cursor = *queue;
    while (root != NULL)
    {
        if ((root->data[0] == key[0]) && (root->data[1] == key[1]))
            return root;
        
        enqueue(q_cursor, root->left);
        enqueue(q_cursor, root->right);
        root = dequeue(q_cursor);
    }
    printf("Could not find the key: (%d, %d)\n", key[0], key[1]);
    return NULL;
}

// Search wrapper
KD_Tree *search_kdtree(KD_Tree *root, int token, Queue **queue)
{
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return NULL;
    }

    if (!is_empty(*queue))
        empty_queue(*queue);
    
    printf("Enter Search Keyword: ");
    char key_c;
    char key_s[S_LEN];
    int key_d[K_DIM];
    int check;

    switch (token)
    {
    case S_CODE:
            scanf("%c", &key_c);
            return __search_index(root, key_c, queue);
        break;
    
    case S_NAME:
            scanf("%s", &key_s);
            return __search_name(root, key_s, queue);
        break;
    
    case S_COORD:
            printf("(use x, y for coordinates) ");
            check = scanf("%d, %d", &key_d[0], &key_d[1]);
            if (check != 2)
            {
                printf("Unexpected token!");
                return NULL;
            }
            return __search_coordinate(root, key_d, queue);
        break;
    
    default:
            printf("Unexpected token!\n");
            return NULL;
        break;
    }
}

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//           QUEUE FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

Queue *create_queue(unsigned capacity)
{ 
    Queue* queue = (Queue*) malloc(sizeof(Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1;  // This is important, see the enqueue 
    queue->data = malloc(queue->capacity * sizeof(KD_Tree*));
    return queue; 
} 

int is_full(Queue *queue) 
{
    return (queue->size == queue->capacity);
}

int is_empty(Queue *queue)
{
    return (queue->size == 0);
}

void enqueue(Queue *queue, KD_Tree *item)
{
    if (is_full(queue))
        return;
    if (item != NULL)
    {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = item;
        queue->size = queue->size + 1;
    }
}

KD_Tree *dequeue(Queue *queue)
{
    if (is_empty(queue)) 
        return NULL;
    KD_Tree* item = queue->data[queue->front]; 
    queue->front = (queue->front + 1) % queue->capacity; 
    queue->size = queue->size - 1; 
    return item;
}

KD_Tree *front(Queue *queue)
{
    if (is_empty(queue)) 
        return NULL; 
    return queue->data[queue->front]; 
}

KD_Tree *rear(Queue *queue)
{
    if (is_empty(queue)) 
        return NULL; 
    return queue->data[queue->rear]; 
}

void empty_queue(Queue *queue)
{
    while (!is_empty(queue))
        dequeue(queue);    
}

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         FILE STREAM FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

// Unfortunately this function only works for my specific type of csv
Tree_Data *read_data(char *filename)
{
    unsigned int l_count = line_counter(filename);
    Tree_Data *data_list = malloc(sizeof(Tree_Data) * (l_count - 1));

    FILE *file_pointer;
    file_pointer = fopen(filename, "r");
    if (file_pointer == NULL)
    {
        printf("Could not open the file %s!", filename);
        return 0;
    }

    char line[LINE_MAX];
    char buffer[S_LEN];
    int i = 0;

    // Discard first line for now
    fgets(line, LINE_MAX, file_pointer);
    const char s[2] = ", ";
    char *token;

    while (fgets(line, LINE_MAX, file_pointer) != NULL)
    {
        
        token = strtok(line, s);
        sscanf(token, "%c", &data_list[i].door_code);
        token = strtok(NULL, s);
        sscanf(token, "%s", data_list[i].door_name);
        token = strtok(NULL, s);
        data_list[i].data[0] = atoi(token);
        token = strtok(NULL, s);
        data_list[i].data[1] = atoi(token);
        

        ++i;
    }
    fclose(file_pointer);
    return data_list;
}

unsigned int line_counter(char *filename)
{
    FILE *file_pointer;
    file_pointer = fopen(filename, "r");

    if (file_pointer == NULL)
    {
        printf("Could not open the file %s!", filename);
        return 0;
    }

    char c;
    unsigned int l_count = 0;
    for (c = getc(file_pointer); c != EOF; c = getc(file_pointer))
        if (c == '\n')
            ++l_count;

    fclose(file_pointer);
    return l_count;
}

//◤━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◥
//         TREE DATA FUNCTIONS
//◣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━◢

Tree_Data *sort_data(Tree_Data *data_list, SortType type, int len)
{
    Tree_Data *new_data;
    switch (type)
    {
    case COORD_X:
            qsort(new_data, len, sizeof(Tree_Data), __compare_COORDX);
        break;
    case COORD_Y:
            qsort(new_data, len, sizeof(Tree_Data), __compare_COORDY);
        break;
    case CODE:
            qsort(new_data, len, sizeof(Tree_Data), __compare_CODE);
        break;
    case NAME:
            qsort(new_data, len, sizeof(Tree_Data), __compare_NAME);
        break;
    default:
        break;
    }
}

int __compare_COORDX(const void * a, const void * b) {
   return ( ((Tree_Data*)a)->data[0] - ((Tree_Data*)b)->data[0] );
}

int __compare_COORDY(const void * a, const void * b) {
   return ( ((Tree_Data*)a)->data[1] - ((Tree_Data*)b)->data[1] );
}

int __compare_CODE(const void * a, const void * b) {
   return ( ((Tree_Data*)a)->door_code - ((Tree_Data*)b)->door_code );
}

int __compare_NAME(const void * a, const void * b) {
   return ( strcmp(((Tree_Data*)a)->door_name, ((Tree_Data*)b)->door_name) );
}