#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

  typedef struct Node_LL
  {
    void *data;
    struct Node_LL* next;
  }Node;
  

  typedef struct StackList
  {
    size_t memSize;
    size_t sizeOfStack;
    Node *head;
  }Stack;
  
  Node *Get_Node(Stack *stack, void *data);
  int Stack_Init(Stack *stack, size_t memSize);
  int push(Stack *stack, void *data);  
  int pop(Stack *stack, void *data);
  int top(Stack *stack, void *data);
  int Stack_Clear(Stack *stack);
  size_t Stack_Size(Stack *stack);
#endif