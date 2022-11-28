/*
Project Done by :

Moughel Mohamed Souhail 105672
El Mehdi Laidoudi 102320

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct tag
{
    int ID;
    char name[30];
    struct tag *next;
} node;

void menu(void)
{
    printf("\n\n\t\t--------------- Menu to Use------------------------\n");
    printf("\t\t|                                                   |\n");
    printf("\t\t|1.  New student joins                              |\n");
    printf("\t\t|2.  Student time is up. Next!                      |\n");
    printf("\t\t|3.  Print list of student interested in playing    |\n");
    printf("\t\t|4.  A student wants to leave the Queue             |\n");
    printf("\t\t|5.  Dr. Talei wants her Toy back                   |\n");
    printf("\t\t|6.  To Quit                                        |\n");
    printf("\t\t----------------------------------------------------\n");
    printf("\n\t\tYour Choice Please:");
}

node *create_fill()
{
    node *new_node;
    new_node = (node *)malloc(sizeof(node));
    getchar();
    printf("\n\t\tPlease enter the name of the student :");
    gets(new_node->name);
    printf("\n\t\tPlease enter the ID :");
    scanf("%d", &new_node->ID);
    new_node->next = NULL;
    return (new_node);
}

void enqueue(node **front, node **rear, node *new_node)
{
    if (*front == NULL && *rear == NULL)
    {
        *front = *rear = new_node;
        (*rear)->next = *front;
    }
    else
    {
        (*rear)->next = new_node;
        (*rear) = new_node;
        (*rear)->next = *front;
    }
}
void dequeue(node **front, node **rear)
{
    node *temp;
    temp = *front;
    if (*front == NULL && *rear == NULL)
    {
        printf("The queue is Empty");
    }
    else if (*front == *rear)
    {
        *front = *rear = NULL;
        free(temp);
    }
    else
    {
        *front = (*front)->next;
        (*rear)->next = *front;
        free(temp);
    }
}

void display(node **front)
{
    node *temp;
    temp = *front;
    if (*front == NULL)
    {
        printf("\n\t\tThe queue is Empty");
    }
    else
    {
        while (temp->next != *front)
        {
            printf("\n\t\tStudent : %s \t with ID : %d\n", temp->name,
                   temp->ID);
            temp = temp->next;
        }
        printf("\n\t\tStudent : %s \t with ID : %d\n", temp->name, temp->ID);
    }
}

void moove(node **front, node **rear)
{
    node *temp;
    temp = *front;
    if (*front == NULL && *rear == NULL)
    {
        printf("\n\t\tThe queue is Empty");
    }
    else
    {
        *front = (*front)->next;
        (*rear)->next = temp;
        *rear = temp;
        temp->next = *front;
    }
}

void remove_student(node **front, node **rear, int id)
{
    node *temp, *walker;
    if ((*front)->ID == id)
    {
        if ((*front) == (*rear))
        {
            temp = *front;
            free(temp);
            *front = *rear = NULL;
        }
        else
        {
            temp = *front;
            *front = (*front)->next;
            (*rear)->next = *front;
            free(temp);
        }
    }

    else
    {

        walker = *front;
        do
        {
            if (walker->next->ID == id)
            {
                if (walker->next == *rear)
                {
                    *rear = walker;
                }
                temp = walker->next;
                walker->next = temp->next;
                free(temp);
                break;
            }
            walker = walker->next;
        } while (walker != *front);
    }
}

void destroy_queue(node **pfront, node **prear)
{
    node *walker;
    walker = *pfront;
    node *temp;
    while (walker != NULL)
    {
        if (walker == *prear)
        {
            free(walker);
            *prear = NULL;
            *pfront = NULL;
            break;
        }
        temp = walker;
        walker = walker->next;
        free(temp);
    }
}

int main()
{
    node *front = NULL, *rear = NULL, *new_node;
    char choice_2;
    int choice, leave_id;
    do
    {
        menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            new_node = create_fill();
            enqueue(&front, &rear, new_node);
            break;
        case 2:
            printf(
                "The first student wants to remain in the queue ?\n\t -Y "
                "for yes and N for No :");
            getchar();
            scanf("%c", &choice_2);
            if (choice_2 == 'N')
            {
                dequeue(&front, &rear);
            }
            else
            {
                moove(&front, &rear);
            }
            break;
        case 3:
            display(&front);
            break;
        case 4:
            printf("Please Enter the id of the student: ");
            scanf("%d", &leave_id);
            remove_student(&front, &rear, leave_id);
            break;
        case 5:
            // destroys the queue and ends program
            destroy_queue(&front, &rear);
            printf("\n\n\t\tQueue Destroyed successfully\n");
            break;
        case 6:
            break;
        default:
            printf("Wrong input");
            break;
        }
    } while (choice != 6);
    printf("Good Bye!");
}
