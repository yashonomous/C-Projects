#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct node{
    char *data;
    struct node *next;
    struct node *prev;
};

static struct node *last = NULL;
static int length = 0;

struct node *get_node(char *data){
    struct node *temp_node = (struct node*)malloc(sizeof(struct node));
    temp_node->data = data;
    temp_node->next = temp_node->prev = NULL;
    return temp_node;
}

struct node *insert_at_begin(struct node *head, char *data){
    if(head == NULL){
        head = get_node(data);
        last = head;
        length++;
        return head;
    }
    struct node *temp_node = get_node(data);
    temp_node->next = head;
    head->prev = temp_node;
    head = temp_node;
    length++;
    return head;
}

struct node *insert_at_end(struct node *head, char *data){
    if(head == NULL){
        head = get_node(data);
        last = head;
        length++;
        return head;
    }
    struct node *temp_node = get_node(data);
    last->next = temp_node;
    temp_node->prev = last;
    last = temp_node;
    length++;
    return head;
}

struct node *insert_at_n(struct node *head, char *data, int position){
    if(head == NULL){
        head = get_node(data);
        last = head;
        return head;
    }
    if(position==1 && head!=NULL){
        struct node *temp_node = get_node(data);
        temp_node->next = head;
        head->prev = temp_node;
        head = temp_node;
        length++;
        return head;
    }
    struct node *temp_ptr = head;
    while(position-2 > 0){
        temp_ptr = temp_ptr->next;
        position--;
    }
    struct node *temp_node = get_node(data);
    temp_node->next = temp_ptr->next;
    temp_node->prev = temp_ptr;
    
    if(temp_ptr->next == NULL){
        temp_ptr->next = temp_node;
        length++;
        return head;
    }
    
    temp_ptr->next->prev = temp_node;
    temp_ptr->next = temp_node;
    length++;
    return head;
}

struct node *delete_first(struct node *head){
    if(head == NULL){
        printf("\nError!! List empty. Try again with different input\n\n");
        return head;
    }
    if(head->next == NULL){
        free(head);
        length--;
        return NULL;
    }
    struct node *temp_node = head;
    head = head->next;
    head->prev = NULL;
    free(temp_node);
    length--;
    return head;
}

struct node *delete_last(struct node *head){
    if(head == NULL){
        printf("\nError!! List empty. Try again with different input\n\n");
        return head;
    }
    if(head->next == NULL){
        free(head);
        length--;
        return NULL;
    }
    struct node *temp_ptr = head;
    while(temp_ptr->next->next != NULL)
        temp_ptr = temp_ptr->next;
    struct node *temp_node = temp_ptr->next;
    temp_ptr->next = NULL;
    free(temp_node);
    length--;
    return head;
}

struct node *delete_at_n(struct node *head, int position){
    if(head == NULL){
        printf("\nError!! List empty. Try again with different input\n\n");
        return head;
    }
    struct node *temp_ptr = head;
    while(position-2 > 0){
        temp_ptr = temp_ptr->next;
        position--;
    }
    struct node *temp_node = temp_ptr->next;
    temp_ptr->next->next->prev = temp_ptr;
    temp_ptr->next = temp_ptr->next->next;
    free(temp_node);
    length--;
    return head;
}

void print_list(struct node *head){
    printf("\nLinked list is -> ");
    while (head != NULL)
    {
        printf("%s ", head->data);
        head = head->next;
    }
    printf("\n\n");
}

int main(int argc, char const *argv[])
{
    printf("*-*-*-*-*-This program implements basic functions of doubly linked list-*-*-*-*-*\n");
    struct node *head = NULL;
    
    while (1)
    {
        printf("Choose operation -> \n1 -> insert at begin.\n2 -> insert at end.\n3 -> insert at n.\n4 -> delete first node\n5 -> delete last node\n6 -> delete at n\n7 -> print list\n8 -> length of list\n-1 -> exit.\n");
        int choice, position, break_flag=0;
        printf("Enter your choice -> ");
        scanf("%d", &choice);
        char *data = (char*)malloc(sizeof(char));
        switch (choice){
            case 1:
                printf("Enter string to be inserted at begining -> ");
                scanf("%s", data);
                head = insert_at_begin(head, data);
                printf("\nSuccess!! Successfuly inserted at the begining\n\n");
                break;
            case 2:
                printf("Enter string to be inserted at end -> ");
                scanf("%s", data);
                head = insert_at_end(head, data);
                printf("\nSuccess!! Successfuly inserted at the end\n\n");
                break;
            case 3:
                printf("Enter the position -> ");
                scanf("%d", &position);
                printf("Enter string to be inserted at %d place -> ", position);
                scanf("%s", data);
                head = insert_at_n(head, data, position);
                printf("\nSuccess!! Successfuly inserted at position %d\n\n", position);
                break;
            case 4:
                head = delete_first(head);
                printf("\nSuccess!! Successfuly deleted first node\n\n");
                break;
            case 5:
                head = delete_last(head);
                printf("\nSuccess!! Successfuly deleted last node\n\n");
                break;
            case 6:
                printf("Enter the position to be deleted -> ");
                scanf("%d", &position);
                head = delete_at_n(head, position);
                if(head)
                    printf("\nSuccess!! Successfuly deleted node at position %d\n\n", position);
                break;    
            case 7:
                print_list(head);
                break;
            case 8:
                printf("\nLength of linked list is %d\n\n", length);
                break;
            case -1:
                printf("Got termination input.");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".\n");
                printf("Terminating.");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".\n");
                printf("Program terminated.\n");
                break_flag = 1;
                break;
            default:
                printf("\nError!! Invalid input. Try again.\n\n");
                break;
        }
        if(break_flag)  break;
    }
    
    return 0;
}
