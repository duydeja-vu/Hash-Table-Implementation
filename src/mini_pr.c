#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct customer
{
    char customer_name[20];
    int customer_age;
    char customer_sex[6];
    int customer_salary;
    char customer_nation[10];
} customer;

struct node
{
    char key_name[20];
    int value_age;
    char value_sex[6];
    int value_salary;
    char value_nation[10];
    struct node *next;
};
typedef struct node node;

struct array_item
{
    struct node *head;
    struct node *tail;
};
typedef struct array_item array_item;

int number_customer_in_database;
array_item *array;
int number_element = 0;
int hash_table_size = 5003;

int get_number_customer_database()
{
    FILE *file_handle;
    file_handle = fopen("input.txt", "r");
    char next_line = getc(file_handle);
    int count_line = 1;
    while (next_line != EOF)
    {
        if (next_line == '\n')
        {
            count_line++;
        }
        next_line = getc(file_handle);
    }
    fclose(file_handle);
    return count_line;
}

int hash_function(char s[])
{
    unsigned long hash_code = 5381;
    for (int i = 0; i < strlen(s); i++)
    {
        hash_code = ((hash_code << 5) + hash_code) + s[i];
    }
    return hash_code % hash_table_size;
}

void insert(char key_name[],
            int value_age,
            char value_sex[],
            int value_salary,
            char value_nation[])
{
    int index = hash_function(key_name);
    node *list = (node *)array[index].head;
    node *item = (node *)malloc(sizeof(node));
    strcpy(item->key_name, key_name);
    item->value_age = value_age;
    strcpy(item->value_sex, value_sex);
    item->value_salary = value_salary;
    strcpy(item->value_nation, value_nation);
    item->next = NULL;
    if (list == NULL)
    {
        array[index].head = item;
        array[index].tail = item;
    }
    else
    {
        array[index].tail->next = item;
        array[index].tail = item;
        number_element++;
    }
}

int search_for_remove(node *list,
                      char key_name[])
{
    printf("\n%s", key_name);
    int retval = 0;
    node *temp = list;
    while (temp != NULL)
    {
        if (0 == strcmp(temp->key_name, key_name))
        {
            return retval;
        }
        temp = temp->next;
        retval++;
    }
    return -1;
}

void search_for_display(char key_name[])
{
    int index = hash_function(key_name);
    node *list = (node *)array[index].head;
    if(list == NULL)
    {
        printf("Customer does not exist");
        return;
    }

    node *temp = list;
    while (temp != NULL)
    {
        if (0 == strcmp(temp->key_name, key_name))
        {
            printf("Name: %s ", temp->key_name);
            printf("Age: %d ", temp->value_age);
            printf("Sex: %s ", temp->value_sex);
            printf("Salary: %d ", temp->value_salary);
            printf("Nation: %s ", temp->value_nation);
        }
        printf("\n");
        temp = temp->next;
    }
}

void remove_element(char key_name[],
                    int value_age,
                    char value_sex[],
                    int value_salary,
                    char value_nation[])
{
    int index = hash_function(key_name);
    node *list = (node *)array[index].head;

    if (list == NULL)
    {
        printf("This key does not fucking exists\n");
    }
    else
    {
        int find_index = search_for_remove(list, key_name);
        if (find_index == -1)
        {
            printf("\nThis key does not exists");
        }
        else
        {
            printf("in Else");
            node *temp = list;
            if ((0 == strcmp(temp->key_name, key_name)) && temp->value_age == value_age)
            {
                array[index].head = temp->next;
                printf("\nThis key has been removed\n");
                return;
            }
            printf("Outside if");
            while ((0 != strcmp(temp->next->key_name, key_name)) || (temp->next->value_age != value_age))
            {
                temp = temp->next;
            }
            if (array[index].tail == temp->next)
            {
                temp->next = NULL;
                array[index].tail = temp;
    
            }
            else
            {
                temp->next = temp->next->next;
            }
            printf("\nThis key has been removed\n");
        }
    }
}

void display()
{
    int number_emty = 0;
    int number_have_element = 0;
    int max = 0;
    for (int i = 0; i < hash_table_size; i++)
    {
        node *temp = array[i].head;
        if (temp == NULL)
        {
            number_emty++;
        }
        else
        {
            printf("array[%d] has elements-: ", i);
            int max_temp = 0;
            while (temp != NULL)
            {
                max_temp++;
                printf(" Name: %s Age: %d Sex: %s Salary: %d Nation: %s || ",
                        temp->key_name, temp->value_age,
                        temp->value_sex, temp->value_salary,
                        temp->value_nation);
                temp = temp->next;
            }
            if (max_temp > max)
            {
                max = max_temp;
            }
            number_have_element++;
            printf("\n");
        }
    }
}

void init_array()
{
    int i = 0;
    for (i = 0; i < hash_table_size; i++)
    {
        array[i].head = NULL;
        array[i].tail = NULL;
    }
}

int main()
{
    FILE *file_handle;
    file_handle = fopen("input.txt", "r");
    number_customer_in_database = get_number_customer_database();
    customer record[number_customer_in_database];
    char *item;
    char lyne[121];
    int count = 0;
    while (fgets(lyne, 120, file_handle))
    {
        item = strtok(lyne, " ");
        strcpy(record[count].customer_name, item);
        item = strtok(NULL, " ");
        record[count].customer_age = atoi(item);
        item = strtok(NULL, " ");
        strcpy(record[count].customer_sex, item);
        item = strtok(NULL, " ");
        record[count].customer_salary = atoi(item);
        item = strtok(NULL, "\n");
        strcpy(record[count].customer_nation, item);
        count++;
        if (10000 == count)
        {
            fclose(file_handle);
        }
    }
    array = (array_item *)malloc(hash_table_size * sizeof(array_item));
    init_array();
    for (int i = 0; i < number_customer_in_database; i++)
    {
        insert(record[i].customer_name,
               record[i].customer_age,
               record[i].customer_sex,
               record[i].customer_salary,
               record[i].customer_nation);
    }
    printf("\nInserted item in database to hash table");
    int user_choice, quit_choice = 0;
    do
    {
        printf("\nImplementation of Hash Table in C chaining with Singly Linked List \n\n");
        printf("MENU-: \n1.Inserting new customer"
               "\n2.Removing customer"
               "\n3.Search customer"
               "\n4.Display Hash Table's data"
               "\n5.Quit"
               "\n\n Please enter your choice -: ");
        scanf("%d", &user_choice);
        switch (user_choice)
        {
        customer new_customer;
        case 1:
            printf("Inserting new customer");
            fflush(stdin);
            printf("\nName: ");
            gets(new_customer.customer_name);
            printf("\nAge: ");
            scanf("%d", &new_customer.customer_age);
            printf("\nSex: ");
            fflush(stdin);
            gets(new_customer.customer_sex);
            printf("\nSalary: ");
            scanf("%d", &new_customer.customer_salary);
            fflush(stdin);
            printf("\nNation: ");
            gets(new_customer.customer_nation);
            insert(new_customer.customer_name,
                   new_customer.customer_age,
                   new_customer.customer_sex,
                   new_customer.customer_salary,
                   new_customer.customer_nation);
            printf("Insertion successly");
            break;
        case 2:
            printf("Deleting in Hash Table \nEnter the key to delete-:");
            printf("Inserting new customer");
            fflush(stdin);
            printf("\nName: ");
            gets(new_customer.customer_name);
            printf("\nAge: ");
            scanf("%d", &new_customer.customer_age);
            printf("\nSex: ");
            fflush(stdin);
            gets(new_customer.customer_sex);
            printf("\nSalary: ");
            scanf("%d", &new_customer.customer_salary);
            fflush(stdin);
            printf("\nNation: ");
            gets(new_customer.customer_nation);
            remove_element(new_customer.customer_name,
                           new_customer.customer_age,
                           new_customer.customer_sex,
                           new_customer.customer_salary,
                           new_customer.customer_nation);
            break;

        case 3:
            printf("Search customer\n");
            fflush(stdin);
            printf("Inter the Name you want search: ");
            gets(new_customer.customer_name);
            search_for_display(new_customer.customer_name);
            break;

        case 4:
            printf("Display my Hash Table\n ");
            display();
        }
        printf("\nPress 0 for quit, 1 for continue: ");
        scanf("%d", &quit_choice);

    } while (1 == quit_choice);
}