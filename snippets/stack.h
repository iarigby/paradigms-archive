#ifndef __STACK_H_
#define __STACK_H_

typedef struct {
  int *elems;
  int loglength;
  int alloclength;
} stack;

void StackNew(stack *s);
void StackDispose(stack *s);
void stackPush(stack *s, int elem);
int StackPop(stack *s);

#endif // __STACK_H_
