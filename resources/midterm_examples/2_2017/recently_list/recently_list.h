#ifndef recently_list
#define recently_list

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_ALLOC_LEN 4

typedef struct {

} RecentlyList;

void RecentlyListNew(RecentlyList * list, size_t elemSize, int (*cmp)(void *, void *), void(*freeFn)(void *));
void RecentlyListAdd(RecentlyList * list, void * elem);
void RecentlyListGet(RecentlyList * list, size_t indx, void * elem);
void RecentlyListRemove(RecentlyList * list, size_t indx);
size_t RecentlyListSize(RecentlyList * list);
void RecentlyListDispose(RecentlyList * list);

#endif 
