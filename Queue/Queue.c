#include<stddef.h>
#include "Queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Node *Get_Node(Queue *queue, const void *data){
    Node *tempNode = (Node*)malloc(sizeof(Node));
    if(tempNode = NULL){
        fprintf(stderr, "%s\n", "Error!! Cannot assign memory to tempNode field.");
        return NULL;
    }
    tempNode->data = malloc(queue->memSize);
    if(tempNode->data == NULL){
        fprintf(stderr, "%s\n", "Error!! Cannot assign memory to data field.");
        return NULL;
    }
    memcpy(tempNode->data, data, queue->memSize);
    tempNode->next = NULL;
    return tempNode;
}

int Queue_Init(Queue *queue, size_t memSize){
    if(queue == NULL){
        fprintf(stderr, "%s\n", "Error!! NULL Queue object.");          //TODO: try adding to file as logger;
        return 0;
    }
    queue->memSize = memSize;
    queue->queueSize = 0;
    queue->head = queue->tail = NULL;
    fprintf(stdout, "%s\n\n", "Success!! Queue object creation successful.");
}

int enqueue(Queue *queue, const void *data){
    if(queue == NULL){
        fprintf(stderr, "%s\n", "Error!! NULL Queue object.");          //TODO: try adding to file as logger;
        return 0;
    }
    Node *newNode = Get_Node(queue, data);
    if(newNode == NULL){
        fprintf(stderr, "%s\n", "Error!! NULL Node object.");
        return 0;
    }
    if(queue->queueSize == 0){
        queue->head = queue->tail = newNode;
    }
    else{
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->queueSize++;
    fprintf(stdout, "%s\n", "Success!! Enqueue successful.");
    return 1;
}

void dequeue(Queue *queue, void *data){
    if(queue == NULL){
        fprintf(stderr, "%s\n", "Error!! Queue object passed to dequeue is NULL.");
        return;
    }
    if(queue->head==NULL && queue->tail==NULL && queue->queueSize==0){
        fprintf(stderr, "%s\n", "Error!! Cannot dequeue as queue is empty.");       //TODO: Reset data pointer.
        return;
    }
    Node *tempNode = queue->head;
    memcpy(data, queue->head->data, queue->memSize);
    if(queue->queueSize == 1){
        queue->head = NULL;
        queue->tail = NULL;
    }
    else{
        queue->head = queue->head->next;
    }
    free(tempNode->data);
    free(tempNode);
    queue->queueSize--;
    fprintf(stdout, "%s\n", "Success!! Dequeue successful.");
}

void Queue_Peek(Queue *queue, void *data){
    if(queue == NULL){
        fprintf(stderr, "%s\n", "Error!! Queue object passed to Queue_Peek is NULL.");
        return;
    }
    if(queue->head==NULL && queue->tail==NULL && queue->queueSize==0){
        fprintf(stderr, "%s\n", "Error!! Queue is empty.");
        //memcpy(data, NULL, sizeof(data));           //TODO: Reset value not working.
        return;
    }
    memcpy(data, queue->head->data, queue->memSize);
    fprintf(stdout, "%s\n", "Success!! Peek value returned.");          //TODO: Casting void pointer into format specifier
}

size_t Queue_Size(Queue *queue){
    if(queue == NULL){
        fprintf(stderr, "%s\n", "Error!! Queue object passed to Queue_Size is NULL.");
        return;
    }
    return queue->queueSize;
}

int Queue_Clear(Queue *queue){
    if(queue->head==NULL && queue->tail==NULL && queue->queueSize==0){
        fprintf(stderr, "%s\n", "Error!! Queue is empty.");
        return 0;
    }
    Node *tempNode = NULL;
    while (queue->queueSize > 0)
    {
        tempNode = queue->head;
        queue->head = queue->head->next;
        free(tempNode->data);
        free(tempNode);
        queue->queueSize--;
    }
    queue->head = NULL;
    queue->tail = NULL;
    fprintf(stdout, "%s\n", "Success!! Queue cleared.");
    return 1;
}
