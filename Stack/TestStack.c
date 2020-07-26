#include<stddef.h>
#include "Stack.h"
#include<stdio.h>

int main(int argc, char const *argv[])
{
    int data;
    Stack *stack;
    Stack_Init(stack, sizeof(data));
    fprintf(stdout, "Size of stack is -> %lu\n\n", Stack_Size(stack));

    for(data=2; data<=10; data+=2){
        push(stack, &data);

        fprintf(stdout, "Size of stack is -> %lu\n", Stack_Size(stack));
        top(stack, &data);
        fprintf(stdout, "Top of the of stack is -> %lu\n\n", data); 
    }

    pop(stack, &data);
    fprintf(stdout, "\nPopped value is -> %lu\n", data);
    top(stack, &data);
    fprintf(stdout, "Top of the of stack is -> %lu\n", data);
    fprintf(stdout, "Size of stack is -> %lu\n\n", Stack_Size(stack));

    pop(stack, &data);
    fprintf(stdout, "Popped value is -> %lu\n", data);
    top(stack, &data);
    fprintf(stdout, "Top of the of stack is -> %lu\n", data);
    fprintf(stdout, "Size of stack is -> %lu\n\n", Stack_Size(stack));   //TODO:File implementation of logger;
    return 0;
}
