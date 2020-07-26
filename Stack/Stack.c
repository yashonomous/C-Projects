#include<stddef.h>
#include "Stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Node *Get_Node(Stack *stack, void *data){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to Get_Node is NULL");
        return NULL;
    }
    Node *tempNode = (Node*)malloc(sizeof(Node));
    tempNode->data = malloc(stack->memSize);
    if(data == NULL){
        fprintf(stderr, "%s\n", "Error!! Data field in Get_Node is NULL.");
        return NULL;
    }
    memcpy(tempNode->data, data, stack->memSize);
    tempNode->next = NULL;
    fprintf(stdout, "%s\n", "Success!! Node created successfully.");
    return tempNode;
}

int Stack_Init(Stack *stack, size_t memSize){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to Stack_Init is NULL.");
        return 0;
    }
    stack->memSize = memSize;
    stack->sizeOfStack = 0;
    stack->head = NULL;
    fprintf(stdout, "%s\n", "Success!! Stack object created successfully.");
    return 1;
}

int push(Stack *stack, void *data){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to push is NULL.");
        return 0;
    }
    Node *tempNode = Get_Node(stack, data);
    if(tempNode == NULL){
        fprintf(stderr, "%s\n", "Error!! Get_Node returns NULL.");
        return 0;
    }
    if((stack->head==NULL) && (stack->sizeOfStack==0)){
        stack->head = tempNode;
    }
    else
    {
        tempNode->next = stack->head;
        stack->head = tempNode;
    }
    stack->sizeOfStack++;
    fprintf(stdout, "%s\n", "Success!! Pushed data successfully.");
    return 1;
}

int pop(Stack *stack, void *data){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to pop is NULL.");
        return 0;
    }
    if((stack->head==NULL) && (stack->sizeOfStack==0)){
        fprintf(stderr, "%s\n", "Error!! Cannot pop. Stack is empty.");
        return 0;
    }
    Node *tempNode = stack->head;
    memcpy(data, tempNode->data, stack->memSize);
    if(stack->sizeOfStack == 1){
        stack->head = NULL;
    }
    else
    {
        stack->head = stack->head->next;
    }
    free(tempNode->data);
    free(tempNode);
    stack->sizeOfStack--;
    fprintf(stdout, "%s\n", "Success!! Popped data successfully.");
    return 1;
}

int top(Stack *stack, void *data){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to top is NULL.");
        return 0;
    }
    if((stack->head==NULL) && (stack->sizeOfStack==0)){
        fprintf(stderr, "%s\n", "Error!! Cannot find top. Stack is empty.");
        return 0;
    }
    memcpy(data, stack->head->data, stack->memSize);
    fprintf(stdout, "%s\n", "Success!! Value of top copied successfully.");
    return 1;
}

size_t Stack_Size(Stack *stack){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to Stack_Size is NULL.");
        return -1;
    } 
    return stack->sizeOfStack;
}

int Stack_Clear(Stack *stack){
    if(stack == NULL){
        fprintf(stderr, "%s\n", "Error!! Stack object passed to pop is NULL.");
        return 0;
    }
    if((stack->head==NULL) && (stack->sizeOfStack==0)){
        fprintf(stderr, "%s\n", "Error!! Cannot clear. Stack is empty.");
        return 0;
    }
    while (stack->sizeOfStack > 0){
        Node *tempNode = stack->head;
        stack->head = stack->head->next;
        free(tempNode->data);
        free(tempNode);
        stack->sizeOfStack--;
    }
    if(stack->head != NULL){
        fprintf(stderr, "%s\n", "Error!! Cannot clear stack. Stack not cleared.");
        return 1;
    }
    fprintf(stdout, "%s\n", "Success!! Stack cleared.");
    return 1;    
}