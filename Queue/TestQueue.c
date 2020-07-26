#include<stddef.h>
#include "Queue.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    int value;
    Queue *queue;
    Queue_Init(queue, sizeof(int));
    for(value=1; value<=10; value++){
        enqueue(queue, &value);
        fprintf(stdout, "Value %d has been enqueued.\n", value);
    }
    printf("\n");
    Queue_Peek(queue, &value);
    fprintf(stdout, "Size of queue is %d\n", Queue_Size(queue));
    fprintf(stdout, "Value on the front is %d\n\n", value);

    while (Queue_Size(queue) > 0)
    {
        dequeue(queue, &value);
        fprintf(stdout, "Value %d has been dequeued.\n", value);
    }
    printf("\n");
    Queue_Peek(queue, &value);
    fprintf(stdout, "Size of queue is %d\n\n", Queue_Size(queue));
    fprintf(stdout, "Value on the front is %d\n\n", value);     //TODO: Resetting value of value pointer here.
    dequeue(queue, &value);
    return 0;
}
