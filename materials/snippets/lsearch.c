int IntCmp(void *elem1,
           void *elem2) {
  int *ip1 = elem1;
  int *ip2 = elem2;
  return *ip1 - *ip2;
}

void *lsearch(void *key, void *base,
              int n, int elemSize,
              int (*cmpFn)(void*, void*)) {
  for (int i = 0; i < n; i++) {
    void *elemAddr = (char*) base + i * elemSize;
    if (cmpFn(key, elemAddr) == 0)
      return elemAddr;
  }
  return 0;
}
