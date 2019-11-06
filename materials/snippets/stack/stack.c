#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#define INIT_SIZE 4

void StackNew(stack *s, int elemSize, void (*freefn)(void *)) {
    assert(elemSize > 0);
    s->elemSize = elemSize;
    s->logLen = 0;
    s->allocLen = INIT_SIZE;
    s->elems = malloc(elemSize * INIT_SIZE);
    s->freefn = freefn;
    assert(s->elems != NULL);
}

void StackDispose(stack *s) {
    if (s->freefn != NULL) {
        for (int i=0; i < s->logLen; i++)
            s->freefn((char*)s->elems + s->elemSize * i);
    }
    s->logLen = 0;
    free(s->elems);
}

int StackEmpty(stack *s) {
    return s->logLen == 0;
}

void StackPush(stack *s, const void *elemAddr) {
    assert(elemAddr != NULL);
    if (s->logLen == s->allocLen) {
        s->allocLen = s->allocLen * 2;
        s->elems = realloc(s->elems, s->allocLen * s->elemSize);
        assert(s->elems != NULL);
    }

    void *dstAddr = (char *)s->elems + (s->logLen * s->elemSize);
    memcpy(dstAddr, elemAddr, s->elemSize);
    s->logLen++;
}

void StackPop(stack *s, void *elemAddr) {
    assert(elemAddr != NULL);
    assert(!StackEmpty(s));
    s->logLen--;
    void *srcAddr = (char *)s->elems + (s->logLen * s->elemSize);
    memcpy(elemAddr, srcAddr, s->elemSize);
}