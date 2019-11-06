#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void sort_strings(char** strings, int n);



int test1(){
  char * x[] = {"one", "two", "three"};
  sort_strings(x, 3);
  return strcmp(x[0],"one")==0 && strcmp(x[1],"three")==0 && strcmp(x[2], "two")==0;
}


int test2(){
  char * x[] = {"blu", "blablabl", "blere", "bla"};
  sort_strings(x, 4);
  return strcmp(x[0],"bla")==0 && strcmp(x[1],"blablabl")==0 && strcmp(x[2], "blere")==0 && strcmp(x[3], "blu")==0;
}



int test3(){
  char * x[] = {"z", "y", "x", "w"};
  sort_strings(x, 4);
  return strcmp(x[0],"w")==0 && strcmp(x[1],"x")==0 && strcmp(x[2], "y")==0 && strcmp(x[3], "z")==0;
}


int test4(){
  char * x[] = {"bluwer23rdwe2"};
  sort_strings(x, 1);
  return strcmp(x[0],"bluwer23rdwe2")==0;
}


int runTest(int testNum) {
  switch(testNum) {
  case 1: return test1();
  case 2: return test2();
  case 3: return test3();
  case 4: return test4();
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
  int numTests = 4;
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
