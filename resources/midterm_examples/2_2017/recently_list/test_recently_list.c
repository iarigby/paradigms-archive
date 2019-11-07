#include "recently_list.h"

int cmpInt(void * e1, void * e2) {
	return (*(int *)e1)-(*(int *)e2);
}
int cmpStr(void * e1, void * e2) {
	return strcmp((char *)e1, (char *)e2);
}
int cmpCharPtr(void * e1, void * e2) {
	// printf("%s  %s\n", *(char **)e1, *(char **)e2);
	return strcmp(*(char **)e1, *(char **)e2);
}

int test1() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	int start = 101;
	int end = 104;
	for (int i=start; i<end; i++) {
		RecentlyListAdd(list, &i);	
	}

	int res;
	int passed = 1;
	for (int i=start; i<end; i++) {
		RecentlyListGet(list, i-start, &res);
		passed = passed && end - (i-start+1) == res;
	}

	return passed;
}


int test2() {
	RecentlyList * list = malloc(200);
	int len = 10025;
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	for (int i=0; i<len; i++) {
		RecentlyListAdd(list, &i);	
	}
	//10024, 10023, 10022 ... 2, 1, 0
	int res;
	int passed = 1;
	for (int i=0; i<len; i++) {
		RecentlyListGet(list, i, &res);
		passed = passed && len-i-1 == res;
	}
	return passed;
}

int test3() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	int i = 7;
	RecentlyListAdd(list, &i);	
	RecentlyListAdd(list, &i);	
	RecentlyListAdd(list, &i);	
	RecentlyListAdd(list, &i);	
	//0
	int res;
	int passed;
	RecentlyListGet(list, 0, &res);
	passed = RecentlyListSize(list) == 1 && res == i;
	return passed;
}

int test4() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	int len = 30;
	int e;
	for (int i=0; i<len; i++) {
		e = i;
		RecentlyListAdd(list, &e);
		e++;
		RecentlyListAdd(list, &e);		
	}
	//30, 29, 28 ... 1, 0
	int res;
	int passed;
	passed = RecentlyListSize(list) == len+1;
	for (int i=len; i>=0; i--) {
		RecentlyListGet(list, len-i, &res);
		passed = passed && i == res;
	}
	return passed;
}

int test5() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	int len = 1000;
	int e;
	for (int i=0; i<len; i++) {
		e = i;
		RecentlyListAdd(list, &e);
	}
	for (int i=0; i<len; i++) {
		e = len-i-1;
		RecentlyListAdd(list, &e);
	}
	//0, 1, 2 ... 9
	int res;
	int passed;
	passed = RecentlyListSize(list) == len;
	for (int i=0; i<len; i++) {
		RecentlyListGet(list, i, &res);
		passed = passed && i == res;
	}
	return passed;
}

int test6() {
	//სტრუქტურაში ვინახავ თზუსტად 13 სიმბოლოიან სიტყვებს, \0 იც ითვლება
	int strLen = 13;
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, strLen, cmpStr, NULL);
	char e[15];
	strcpy(e, "bbbbbbbbbbb?");
	int len = 10;
	for (int i=0; i<len; i++) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	
	//bbbbbbbbbbb9, bbbbbbbbbbb8 ... bbbbbbbbbbb0
	char res[15];
	int passed = RecentlyListSize(list) == len;
	for (int i=0; i<len; i++) {
		RecentlyListGet(list, i, res);
		e[strLen-2] = '0' + (len-1-i);
		passed = passed && !strcmp(res, e);
	}
	return passed;
}

int test7() {
	//სტრუქტურაში ვინახავ თზუსტად 11 სიმბოლოიან სიტყვებს 
	int strLen = 11;
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, strLen, cmpStr, NULL);
	char e[12];
	strcpy(e, "bbbbbbbbb?");
	int len = 27;
	for (int i=0; i<len; i++) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	
	//bbbbbbbbbM, bbbbbbbbbL ... bbbbbbbbb0
	char res[12];
	int passed = RecentlyListSize(list) == len;
	for (int i=0; i<len; i++) {
		RecentlyListGet(list, i, res);
		e[strLen-2] = '0' + (len-1-i);
		passed = passed && !strcmp(res, e);
	}
	return passed;
}

int test8() {
	//სტრუქტურაში ვინახავ თზუსტად 7 სიმბოლოიან სიტყვებს, \0 იც ითვლება
	int strLen = 3;
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, strLen, cmpStr, NULL);
	char e[12];
	strcpy(e, "b?");
	int len = 10;
	for (int i=0; i<len; i++) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	for (int i=len-1; i>=0; i--) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	
	//b0, b1 ... b9
	char res[12];
	int passed = RecentlyListSize(list) == len;
	for (int i=0; i<len; i++) {
		RecentlyListGet(list, i, res);
		e[strLen-2] = '0' + i;
		passed = passed && !strcmp(res, e);
	}
	return passed;
}

int test9() {
	//სტრუქტურაში ვინახავ თზუსტად 7 სიმბოლოიან სიტყვებს, \0 იც ითვლება
	int strLen = 5;
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, strLen, cmpStr, NULL);
	char e[12];
	strcpy(e, "bbb?");
	int len = 10;
	for (int i=0; i<len; i++) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	e[strLen-2] = '0';
	RecentlyListAdd(list, e);	
	
	//bbb0, bbb9, bbb8 ... 1
	char res[12];
	int passed = RecentlyListSize(list) == len;
	RecentlyListGet(list, 0, res);
	passed = passed && !strcmp(res, e);
	for (int i=1; i<len; i++) {
		RecentlyListGet(list, i, res);
		e[strLen-2] = '0' + (len-i);
		passed = passed && !strcmp(res, e);
	}
	return passed;
}

int test10() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(char *), cmpCharPtr, NULL);
	char ** e = malloc(sizeof(char *));
	*e = strdup("1");
	RecentlyListAdd(list, e);	
	*e = strdup("2");
	RecentlyListAdd(list, e);	
	*e = strdup("3");
	RecentlyListAdd(list, e);	
	*e = strdup("4");
	RecentlyListAdd(list, e);	
	*e = strdup("2");
	RecentlyListAdd(list, e);

	int passed = RecentlyListSize(list) == 4;
	RecentlyListGet(list, 0, e);
	passed = passed && !strcmp(*e, "2");
	RecentlyListGet(list, 1, e);
	passed = passed && !strcmp(*e, "4");
	RecentlyListGet(list, 2, e);
	passed = passed && !strcmp(*e, "3");
	RecentlyListGet(list, 3, e);
	passed = passed && !strcmp(*e, "1");

	return passed;
}

int test11() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	int start = 101;
	int end = 104;
	for (int i=start; i<end; i++) {
		RecentlyListAdd(list, &i);	
	}

	RecentlyListRemove(list, (end-start-1));
	
	int res;
	int passed = 1;
	for (int i=start; i<end-1; i++) {
		RecentlyListGet(list, i-start, &res);
		passed = passed && end - (i-start+1) == res;
	}

	return passed;
}

int test12() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(int), cmpInt, NULL);
	int start = 101;
	int end = 1004;
	for (int i=start; i<end; i++) {
		RecentlyListAdd(list, &i);	
	}

	for (int i=0; i<end-start; i++) {
		int ind = rand()%RecentlyListSize(list);
		RecentlyListRemove(list, ind);
	}
	int passed = RecentlyListSize(list) == 0;
	return passed;
}

int test13() {
	//სტრუქტურაში ვინახავ თზუსტად 7 სიმბოლოიან სიტყვებს, \0 იც ითვლება
	int strLen = 7;
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, strLen, cmpStr, NULL);
	char e[12];
	strcpy(e, "bbbbb?");
	int len = 10;
	for (int i=0; i<len; i++) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	RecentlyListRemove(list, 0);
	RecentlyListRemove(list, 0);
	RecentlyListRemove(list, RecentlyListSize(list)-1);
	RecentlyListRemove(list, RecentlyListSize(list)-1);
	
	//bbbbb7, bbbbb6 ... bbbbb2
	char res[12];
	int passed = RecentlyListSize(list) == len-4;
	for (int i=0; i<len-4; i++) {
		RecentlyListGet(list, i, res);
		e[strLen-2] = '0' + (len-i-3);
		passed = passed && !strcmp(res, e);
	}
	return passed;
}

int test14() {
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, sizeof(char *), cmpCharPtr, NULL);
	char ** e = malloc(sizeof(char *));
	*e = strdup("1");
	RecentlyListAdd(list, e);	
	*e = strdup("2");
	RecentlyListAdd(list, e);	
	*e = strdup("3");
	RecentlyListAdd(list, e);	
	*e = strdup("4");
	RecentlyListAdd(list, e);	
	*e = strdup("2");
	RecentlyListAdd(list, e);

	RecentlyListRemove(list, 3);
	int passed = RecentlyListSize(list) == 3;
	RecentlyListGet(list, 0, e);
	passed = passed && !strcmp(*e, "2");
	RecentlyListGet(list, 1, e);
	passed = passed && !strcmp(*e, "4");
	RecentlyListGet(list, 2, e);
	passed = passed && !strcmp(*e, "3");
	RecentlyListGet(list, 3, e);

	return passed;
}

int test15() {
	//სტრუქტურაში ვინახავ თზუსტად 7 სიმბოლოიან სიტყვებს, \0 იც ითვლება
	int strLen = 3;
	RecentlyList * list = malloc(200);
	RecentlyListNew(list, strLen, cmpStr, NULL);
	char e[12];
	strcpy(e, "b?");
	int len = 10;
	for (int i=0; i<len; i++) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	for (int i=len-1; i>=0; i--) {
		e[strLen-2] = '0' + i;
		RecentlyListAdd(list, e);	
	}
	
	RecentlyListRemove(list, 0);
	RecentlyListRemove(list, 1);
	RecentlyListRemove(list, 2);
	RecentlyListRemove(list, 3);
	RecentlyListRemove(list, 4);
	len = len - 5;
	//b0, b1 ... b9
	char res[12];
	int passed = RecentlyListSize(list) == len;
	for (int i=0; i<len; i++) {
		RecentlyListGet(list, i, res);
		e[strLen-2] = '0' + i*2+1;
		passed = passed && !strcmp(res, e);
	}
	return passed;
}


int main(int argc, char * args[]) {
	int num = atoi(args[1]);
	int testNum = num;
	int res = 0;
	switch (testNum) {
			case 1:
				res = test1();
				break;
			case 2:
				res = test2();
				break;
			case 3:
				res = test3();
				break;
			case 4:
				res = test4();
				break;
			case 5:
				res = test5();
				break;
			case 6:
				res = test6();
				break;
			case 7:
				res = test7();
				break;
			case 8:
				res = test8();
				break;
			case 9:
				res = test9();
				break;
			case 10:
				res = test10();
				break;
			case 11:
				res = test11();
				break;
			case 12:
				res = test12();
				break;
			case 13:
				res = test13();	
				break;
			case 14:
				res = test14();	
				break;
			case 15:
				res = test15();	
				break;
	}
	char * outputFile = "out.txt";
	FILE * fp = fopen(outputFile, "w+");
	if (res) {
		fprintf(fp, "t\n");
	} else {
		fprintf(fp, "f\n");
	}

	fclose(fp);
	return 0;
}
