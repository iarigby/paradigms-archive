int intcmp(void *vp1, void *vp2);
int dblcmp(void *vp1, void *vp2);
int cmpstr(void *vp1, void *vp2);
void swap(void *vp1, void *vp2, int size);
void ssort(void *base, int size, int elemSize,
           int (*cmpfn)(void *, void *));