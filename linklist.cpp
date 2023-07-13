# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <iostream>
# include <ctype.h>


struct node 
{
    int value;
    struct node *next;
    struct node *prev;
};

struct node *first;
struct node *end;
struct node *current;

struct node* add(void)
{
    struct node* a = (struct node *)malloc(sizeof(struct node)*1);
    if (a==NULL)
    {
        printf("Unable to allocate memory\n");
        exit(1);
    }
    return(a);
}

int menu(void);
int create(void);
void show(void);
void reverse(void);
void insert(int& numOfNodes);
void del(int& numOfNodes);
void max(void);
void min(void);
void find(void);
void sort(int numOfNodes);
void tostr(void);
void toarr(int numOfNodes);

int menu(void)
{
    int ch;
    printf("--------------------------------------\n");
    printf("Create  => Create a new set of linked list\n");
    printf("Reverse => Print the list in reverse, not reverse the list\n");
    printf("Insert  => Only when you have already created a linked list\n");
    printf("A) Max\nB) Min\nC) Create\nD) Delete\nE) Show\nF) Find\nG) Reverse\nH) Sort\nI) Insert\nJ) toString\nK) toArray\nQ) Quit\n");
    ch = getchar();
    while (getchar() != '\n' && getchar() != EOF)
        continue;
    return(toupper(ch));
}

int create(void)
{
    int n, i, num;
    printf("Enter the number of nodes to add:\n");
    scanf("%d", &n);
    while(getchar() != '\n' && getchar() != EOF)
        continue;

    if(n==1)
    {
        first = add();
        printf("Input data for node 1:\n");
        scanf("%d", &num);
        while (getchar() != '\n' && getchar() != EOF)
            continue;
        first->value = num;
        first->next = NULL;
        first->prev = NULL;
        end = first;
        current = first;
    }

    else if(n>1)
    {
        first = add();
        printf("Input data for node 1:\n");
        scanf("%d", &num);
        while (getchar() != '\n' && getchar() != EOF)
            continue;
        first->value = num;
        first->next = NULL;
        first->prev = NULL;
        end = first;
        current = first;
        for(i=2; i<=n; i++)
        {
            current->next = add();
            current = current->next;
            printf("Input data for node %d:\n", i);
            scanf("%d", &num);
            while (getchar() != '\n' && getchar() != EOF)
                continue;
            current->value = num;
            current->prev = end;
            current->next = NULL;

            end->next = current;
            end = current;
        }
    }

    else
    {
        printf("Too few nodes\n");
        return(0);
    }

    return n;
}

void show(void)
{
    int n=1;

    if(first==NULL)
    {
        printf("No data found\n");
        return;
    }

    current = first;
    printf("----------------------------------\n");
    printf("Data entered in the list are:\n");
    while(current)
    {
        printf("Node %d : %d\n", n, current->value);
        n++;
        current = current->next;
    }
    printf("----------------------------------\n");
}

void reverse(void)
{
    int n=1;

    if(first==NULL)
    {
        printf("No data found\n");
        return;
    }

    else
    {
        printf("----------------------------------\n");
        printf("Data entered in reverse:\n");
        current = end;
        while(current!=NULL)
        {
            printf("Node %d : %d\n", n, current->value);
            n++;
            current = current->prev;  
        }
        printf("----------------------------------\n");
    }
}

void insert(int& numOfNodes)
{
    int num, pos;
    printf("Enter a number to be insert:\n");
    scanf("%d", &num);
    while (getchar() != '\n' && getchar() != EOF)
        continue;
    printf("Enter the position to insert it at:\n");
    scanf("%d", &pos);
    while (getchar() != '\n' && getchar() != EOF)
        continue;
    
    if(first==NULL)
    {
        printf("No link list created yet\n");
        return;
    }

    if(pos==1)
    {
        struct node* temp = add();
        temp->value = num;
        temp->next = first;
        first->prev = temp;
        temp->prev = NULL;
        first = temp;
        numOfNodes++;
    }
    
    else if(pos == numOfNodes+1)
    {
        struct node* temp = add();
        temp->value = num;
        temp->next = NULL;
        temp->prev = end;
        end->next = temp;
        end = temp;
        numOfNodes++;
    }

    else if(pos>1 && pos<=numOfNodes)
    {
        struct node* temp = add();
        temp->value = num;
        current = first;
        for (int i=1; i<pos; i++)
        {
            current = current->next;
        }
        temp->prev = current->prev;
        temp->next = current;
        current->prev->next = temp;
        current->prev = temp;
        numOfNodes++;
    }

    else 
    {
        printf("Invalid position\n");
        return;
    }
}

void del(int& numOfNodes)
{
    int i;
    int pos;
    printf("Enter position to delete:\n");
    scanf("%d", &pos);
    while (getchar() != '\n' && getchar() != EOF)
        continue;
    struct node* temp;

    if (first == NULL)
    {
        printf("Nothing to delete\n");
        return;
    }

    else if(numOfNodes==1)
    {
        printf("Node not deleted\n");
        printf("Use either q to quit or c to create a new list\n");
        return;
    }

    else 
    {
        if(pos==1)
        {
            temp = first;
            first = first->next;
            first->prev = NULL;
            free(temp);
            numOfNodes--;
        }

        else if(pos == numOfNodes)
        {
            temp = end;
            end = end->prev;
            end->next = NULL;
            free(temp);
            numOfNodes--;
        }

        else if(pos>1 && pos<numOfNodes)
        {
            current = first;
            for(i=1; i<pos; i++)
                current = current->next;
            temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(temp);
            numOfNodes--;
        }

        else
        {
            printf("Invalid position\n");
            return;
        }
    }
}

void max()
{
    if (first==NULL)
    {
        printf("No values yet\n");
        return;
    }
    
    int max = INT_MIN;
    current = first;
    while(current != NULL)
    {
        if(current->value>max)
            max = current->value;
        current = current->next;
    }

    printf("----------------------------------\n");
    printf("The max value is %d\n", max);
    printf("----------------------------------\n");
}

void min()
{
    if (first==NULL)
    {
        printf("No values yet\n");
        return;
    }

    int min = INT_MAX;
    current = first;
    while(current!=NULL)
    {
        if(current->value<min)
            min = current->value;
        current = current->next;
    }
    
    printf("----------------------------------\n");
    printf("The min value is %d\n", min);
    printf("----------------------------------\n");
}

void find()
{
    int num, i = 1;
    int flag = 0;
    current = first;
    if (first==NULL)
    {
        printf("Nothing in list\n");
        return;
    }
    printf("Searching for which number?");
    scanf("%d", &num);
    while (getchar() != '\n' && getchar() != EOF)
        continue;
    do
    {
        if(current->value == num)
        {
            printf("Number found at node %d\n", i);
            flag = 1;
        }
        current = current->next;
        i++;
    } while(current!=NULL);

    if(flag==0)
    {
        printf("Number not found on this list\n");
        return;
    }
}

void sort(int numOfNodes)
{
    if (first==NULL)
    {
        printf("Nothing to sort yet\n");
        return;
    }

    struct node* temp1, *temp2;
    int outer, inner, temp;
    for (outer=0; outer<numOfNodes-1; outer++)
    {
        temp1 = first;
        temp2 = temp1->next;
        for (inner=outer+1; inner<numOfNodes; inner++)
        {
            if(temp1->value > temp2->value)
            {
                temp = temp1->value;
                temp1->value = temp2->value;
                temp2->value = temp;
            }
            temp1 = temp2;
            temp2 = temp2->next;
        }
    }

    current = first;
    while(current!=NULL)
    {
        printf("%d\t", current->value);
        current = current->next;
    }

    printf("\n");
}

void tostr()
{
    if (first==NULL)
    {
        printf("Nothing to show yet\n");
        return;
    }
    else 
    {
        char text[100] = "";
        current = first;
        while (current != NULL)
        {
            char str[10];
            sprintf(str, "%d", current->value);
            strcat(text, str);
            strcat(text, " ");
            current = current->next;
        }
        printf("The string format of linked list is %s\n", text);
    }
}

void toarr(int numOfNodes)
{
    if (first==NULL)
    {
        printf("Nothing to show yet\n");
        return;
    }
    else
    {
        struct node* temp;
        temp = first;
        int i;
        int arr[numOfNodes];
        for(i=0; i<numOfNodes; i++)
        {
            arr[i] = temp->value;
            temp = temp->next;
        }
        for (i=0; i<numOfNodes; i++)
        {
            printf("%d ", arr[i]);
        }

        printf("\n");
    }
}

int main()
{
    int choice = '\0';
    int numOfNodes;
    first = NULL;
    end = NULL;
    while(choice!='Q')
    {
        choice = menu();
        switch(choice)
        {
            case 'A':
                max();
                break;
            case 'B':
                min();
                break;
            case 'C':
                numOfNodes = create();
                break;
            case 'D':
                del(numOfNodes);
                break;
            case 'E':
                show();
                break;
            case 'F':
                find();
                break;
            case 'G':
                reverse();
                break;
            case 'H':
                sort(numOfNodes);
                break;
            case 'I':
                insert(numOfNodes);
                break;
            case 'J':
                tostr();
                break;
            case 'K':
                toarr(numOfNodes);
                break;
            case 'Q':
                break;
        }
    }

    return(0);
}