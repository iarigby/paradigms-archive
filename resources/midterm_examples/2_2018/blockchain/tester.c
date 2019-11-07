#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>


#define RESULTS_FILE "results.txt"
#define WORKS_ROOT_FOLDER "../works/"
#define TESTS_OUTPUT_FOLDER "output"
#define TESTS_OUTPUT_FILE "out.txt"


/*****************README******************
1. define one you want to test
2. compile tester, using gcc tester.c -o tester command
3. copy your folder into \work folder
4. run tester using command - ./tester
5. find test results in results.txt file
*/
#define TEST_BLOCKCHAIN


#ifdef TEST_BLOCKCHAIN
#define NUM_TESTS 15
#define PROBLEM_SUBFOLDER_PATH "paradigms-midterm2/blockchain/"
#define PROBLEM_FILE_C "blockchain.c"
#define PROBLEM_FILE_H "blockchain.h"
#define PROBLEM_TESTER_FILE "blockchain_test.c vector.c hashset.c hash.c"
#define ADDITIONAL_FILES ""
#endif




int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int runTests(char * executableName) {
	char * outputFile = TESTS_OUTPUT_FILE;
	int counter = 0;

	char executableFullPath[100];
	sprintf(executableFullPath, "%s/%s", TESTS_OUTPUT_FOLDER, executableName);

	if( access( executableFullPath, F_OK ) == -1 ) {
		return -1;
	}

	for (int i=1; i<=NUM_TESTS; i++) {
		char buff[100];
		remove(outputFile);
		sprintf(buff, "./%s %d", executableFullPath, i);
		int ret = system(buff);
		FILE * fp = fopen(outputFile, "r+");
		if (fp == NULL)
			continue;
		fscanf(fp, "%s", buff);
		if (buff[0] == 't') {
			counter++;
		}

		fclose(fp);

	}
	return counter;
}


void generateExecutableFiles() {
	FILE * results = fopen(RESULTS_FILE, "w+");
	char * rootFolder = WORKS_ROOT_FOLDER;

	DIR *dp;
	struct dirent *ep;
	dp = opendir (rootFolder);

	if (dp != NULL) {
		while (ep = readdir (dp)) {
      		char studentWorkFolderPath[1000];
      		char studentFiles[2000];
      		char listH[1000];
			if (!strcmp(ep->d_name, ".") || !strcmp(ep->d_name, "..")) {
				continue;
			}
      		sprintf(studentWorkFolderPath, "%s%s", rootFolder, ep->d_name);
      		sprintf(studentFiles, "\"%s/%s%s\" \"%s/%s%s\"", 
      			studentWorkFolderPath, PROBLEM_SUBFOLDER_PATH, PROBLEM_FILE_C, 
      			studentWorkFolderPath, PROBLEM_SUBFOLDER_PATH, PROBLEM_FILE_H);

      		//compile student files and generate separate executor file
      		char compileCommand[1000];
     		sprintf(compileCommand, "gcc -I \"%s/%s\" %s %s -o %s/%s", 
     			studentWorkFolderPath, PROBLEM_SUBFOLDER_PATH, PROBLEM_TESTER_FILE, 
     			studentFiles, TESTS_OUTPUT_FOLDER, ep->d_name);
			printf("%s\n", compileCommand);
			int ret = system(compileCommand);
     		//printf(">>>>  %s\n", compileCommand);
			printf("run tests for %s\n", studentWorkFolderPath);
      		//if file doesn't exists log folder
      		//run tests and write scores in result file
      		int acceptedTests = runTests(ep->d_name);
      		fprintf(results, "%s\t%d\n", ep->d_name, acceptedTests);

      		if (!is_regular_file(studentWorkFolderPath))
      			printf ("%s\n", studentWorkFolderPath);
      		fflush(results);
		}
        
		(void) closedir (dp);
    } else
    	perror ("Couldn't open the directory");

    fclose(results);
}



int main() {
	generateExecutableFiles();
/*
	int counter = 0;
	for (int i=1; i<=18; i++) {
		char buff[100];
		sprintf(buff, "./a.out %d > out.txt", i);
		int ret = system(buff);
		FILE * fp = fopen("out.txt", "r+");
		fscanf(fp, "%s", buff);
		if (buff[0] == 't')
			counter++;
	}
	printf("passed - %d testes\n", counter);
*/	
	return 0;
}

