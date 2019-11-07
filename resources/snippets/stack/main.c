#include <stdio.h>
#include "stack.h"

int main() {
    stack intStack;
    StackNew(&intStack, sizeof(int), NULL);

    for (int i=0; i < 99999; i++) {
        StackPush(&intStack, &i);
        // printf("Push to stack: %d\n", i);
    }


    int val;
    while(!StackEmpty(&intStack)){
        StackPop(&intStack, &val);
        printf("Pop from stack: %d\n", val);
    }
    StackDispose(&intStack);
}