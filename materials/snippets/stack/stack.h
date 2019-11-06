#ifndef STACK
#define STACK

typedef struct {
    void* elems;
    int elemSize;
    int allocLen;
    int logLen;
    void (*freefn)(void*);
} stack;

void StackNew(stack *s, int elemSize, void (*freefn)(void *));
void StackDispose(stack *s);
int StackEmpty(stack *s);
void StackPush(stack *s, const void *elemAddr);
void StackPop(stack *s, void *elemAddr);

#endif