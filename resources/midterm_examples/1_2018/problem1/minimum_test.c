#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void* minimum(void *base, int n, int size, int(*cmp)(const void *, const void *));

int intcmp(const void *x, const void *y){
  int a = *(int *)x;
  int b = *(int *)y;
  if (a>b){
    return 1;
  } else if (a<b){
    return -1;
  }
  return 0;
}


int test1(){
  int x[] = {1,2,3,4};
  void*res = minimum(x, 4, sizeof(int), intcmp);
  return res==x;
}


int test2(){
  int x[] = {6,2,3,4,5};
  void*res = minimum(x, 5, sizeof(int), intcmp);
  return res==x+1;
}



int test3(){
  int x[] = {6,2,3,4,1};
  void*res = minimum(x, 5, sizeof(int), intcmp);
  return res==x+4;
}


int test4(){
  int x[] = {1,2,3,4,-1,-2};
  void*res = minimum(x, 6, sizeof(int), intcmp);
  return res==x+5;
}


int test5(){
  int x[] = {1,2,-3,4};
  void*res = minimum(x, 4, sizeof(int), intcmp);
  return res==x+2;
}


int runTest(int testNum) {
  switch(testNum) {
  case 1: return test1();
  case 2: return test2();
  case 3: return test3();
  case 4: return test4();
  case 5: return test5();
  }
  return 0;
}


void checkIfAllocWorks() {
  printf("Checking if allocation works properly\n");
  void * tmp = malloc(1000);
  assert("Allocation failed!! CALL INSTRUCTOR!" && tmp);
  printf("Allocation works!\n");
  tmp = realloc(tmp, 1001);
  assert("Reallocation failed!! CALL INSTRUCTOR!" && tmp);
  free(tmp);
  printf("Reallocation works!\n");
}


int main() {
  checkIfAllocWorks();
  int numTests = 5;
  for (int i=1; i<=numTests; i++) {
    int res = runTest(i);
    if (res) {
      printf("passed test %d/%d\n", i, numTests);
    } else {
      printf("failed test %d/%d\n", i, numTests);
    }
  }
  return 0;
}
