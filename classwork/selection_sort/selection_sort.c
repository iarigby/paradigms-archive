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

int intcmp(void *vp1, void *vp2)
{
    int a = *((int *)vp1);
    int b = *((int *)vp2);
    if (a == b)
        return 0;
    return a < b ? -1 : 1;
}

int dblcmp(void *vp1, void *vp2)
{
    double epsilon = 0.00001;
    double a = *((double *)vp1);
    double b = *((double *)vp2);
    if ((a - b < epsilon) && (b - a < epsilon))
    // if (a == b)
        return 0;
    return a < b ? -1 : 1;
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

int main()
{
    double a[] = {5., 4., 3., 2., 1.};
    int size = sizeof(a) / sizeof(double);
    ssort(&a, size, sizeof(double), dblcmp);
    for (int i = 0; i < size; i++)
        printf("%f ", a[i]);
    printf("\n");

    char *s[] = {"Bob", "Al", "All", "Curl"};
    size = sizeof(s) / sizeof(char *);
    ssort(s, size, sizeof(char *), cmpstr);
    for (int i = 0; i < size; i++)
        printf("%s ", s[i]);
    printf("\n");

    return 0;
}
