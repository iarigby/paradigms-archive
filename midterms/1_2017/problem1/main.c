#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "find_score.h"



int test1(){
	char m[9];
	m[0] = 'A';
	m[1] = 'N';
	m[2] = 'A';
	m[3] = 228;
	m[4] = 'G';
	m[5] = 'E';
	m[6] = 'L';
	m[7] = 'A';
	m[8] = 208;

	int result = find_score(m, 2, "GELA");
	return (result == 80);
}

int test2(){
	char m[17];
	strcpy(m,"JONDI");
	m[5] = 200;
	strcpy(m+6, "A");
	m[7] = 128;
	strcpy(m+8, "AGRAFINA");
	m[16] = 178;

	int result = find_score(m, 3, "A");
	return (result == 0);
}

int test3(){
	char m[10];
	strcpy(m,"A");
	m[1] = 200;
	strcpy(m+2,"B");
	m[3] = 201;	
	strcpy(m+4,"C");
	m[5] = 202;	
	strcpy(m+6,"D");
	m[7] = 203;	
	strcpy(m+8,"E");
	m[9] = 204;

	int result = find_score(m, 5, "E");
	return (result == 76);

}

int test4(){
	char m[300];
	for (int i=0; i<100; i++){
		m[3*i] = 65 + i % 26;
		m[3*i+1] = 65 + i % 26;
		m[3*i+2] = i+128;
	}
	int result = find_score(m, 100, "ZZ");
	return (result == 25);
}

int test5(){
	char m[300];
	for (int i=0; i<100; i++){
		m[3*i] = 65 + i % 26;
		m[3*i+1] = 65 + i % 26;
		m[3*i+2] = i+128;
	}
	int result = find_score(m, 100, "AZ");
	return (result == -1);
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
