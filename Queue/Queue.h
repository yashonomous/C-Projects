#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
    typedef struct Node_LL
    {
        void *data;
        struct Node_LL *next;
    }Node;
    

    typedef struct QueueList
    {
        size_t queueSize;
        size_t memSize;
        Node *head;
        Node *tail;

    }Queue;

    Node *Get_Node(Queue *queue, const void *data);
    int Queue_Init(Queue *queue, size_t memSize);
    int enqueue(Queue *queue, const void *data);
    void dequeue(Queue *queue, void *data);
    int Queue_Clear(Queue *queue);
    void Queue_Peek(Queue *queue, void *data);
    size_t Queue_Size(Queue *queue);
    
#endif