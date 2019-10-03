#include <string.h>
#include <stdio.h>
#include "selection_sort.h"
void swap(void *vp1, void *vp2, int size)
{
    char buffer[size];
    memcpy(buffer, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, buffer, size);
}



void ssort(void *base, int size, int elemSize,
           int (*cmpfn)(void *, void *))
{

    for (int j = 0; j < size - 1; j++)
    {
        int iMin = j;
        char *minptr = (char *)base + iMin * elemSize;
        for (int i = j + 1; i < size; i++)
        {
            char *ptr = (char *)base + i * elemSize;
            if (cmpfn(ptr, minptr) < 0) {
                iMin = i;
                minptr = (char *)base + iMin * elemSize;
            }
        }

        if (iMin != j)
            swap(minptr, (char *)base + j * elemSize, elemSize);
    }
}

int cmpstr(void *vp1, void *vp2)
{
    char *s1 = *(char **)vp1;
    char *s2 = *(char **)vp2;
    // int r = strcmp(s1, s2);
    // return r;
    while (*s1 && (*s1 == *s2))
        s1++, s2++;

    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int main() {
    int size;
    char *s[] = {"Bob", "Al", "All", "Curl"};
    size = sizeof(s) / sizeof(char *);
    ssort(s, size, sizeof(char *), cmpstr);
    for (int i = 0; i < size; i++)
        printf("%s ", s[i]);
    printf("\n");
}
