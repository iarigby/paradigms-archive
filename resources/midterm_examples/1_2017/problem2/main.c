#include "fix_text.h"
#include <assert.h>
#define WORD_NUM 43

void checkIfAllocWorks();
void printTestResults(int passed, int * testNum, int * passedCounter);
int isInLex(char * w, char ** lex, int n);
int checkSentSpell(char * origSent, char * resSent);

char * lex[] = {"a", "am", "an", "and", "are", "back", "call", "can", "cheese", "dwarf", 
				"gonna", "he", "here", "him", "hookers", "i", "in", "is", "it", "just", 
				"make", "manky", "me", "my", "nobody", "not", "offer", "out", "perfect", 
				"precious", "pull", "racist", "refuse", "room", "royale", "they", "thought", 
				"two", "was", "we", "well", "when", "with"};


void testSpellCorrect() {
	printf("### Run Spell Correct ###\n");
	int passedCounter = 0;
	int testNum = 0;
	char * sentCopy;
	char * sentToFix;
	//#1
	sentToFix = strdup("ii am gonna make himq a offerc hez can not refuse");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#2
	sentToFix = strdup("welll heree we are in a room with two manky hookers and a racist dwarf");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#3 
	sentToFix = strdup("theyy calll itt a royale witht cheeset");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#4 
	sentToFix = strdup("just whenn i thought i wass out theyy pull me back ina");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#5
	sentToFix = strdup("nobody iss perfect");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#6
	sentToFix = strdup("my preciouss");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#7
	sentToFix = strdup("aa ia");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#8
	sentToFix = strdup("a");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#9
	sentToFix = strdup("aa");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);

	//#10
	sentToFix = strdup("a1 am1 an1 and1 are1 back1 call1 can1 cheese1 dwarf1 gonna1 he1 here1 him1 hookers1 i1 in1 is1 it1 just1 make1 manky1 me1 my1 nobody1 not1 offer1 out1 perfect1 precious1 pull1 racist1 refuse1 room1 royale1 they1 thought1 two1 was1 we1 well1 when1 with1");
	sentCopy = strdup(sentToFix);
	spellCorrect(lex, WORD_NUM, &sentToFix);
	printTestResults(checkSentSpell(sentCopy, sentToFix), &testNum, &passedCounter);
	
	printf("###### passed (%d/%d) tests ######\n", passedCounter, testNum);
}


int main() {
	checkIfAllocWorks();
	char * lexicon[WORD_NUM];
	testSpellCorrect();
	return 0;
}















void checkIfAllocWorks() {
	printf("Checking if allocation works properly\n");
	void * tmp = malloc(1000);
	assert("Allocation failed" && tmp);
	printf("Allocation works!\n");
	tmp = realloc(tmp, 1001);
	assert("Reallocation failed" && tmp);	
	free(tmp);
	printf("Reallocation works!\n");
}

void printTestResults(int passed, int * testNum, int * passedCounter) {
	(*testNum)++;
	if (passed) {
		printf("test %d  passed\n", *testNum);
		(*passedCounter)++;
	} else {
		printf("test %d  failed\n", *testNum);
	}
}

int isInLex(char * w, char ** lex, int n) {
	for (int i=0; i<n; i++) {
		if (!strcmp(w, lex[i]))
			return 1;
	}
	return 0;
}

int checkSentSpell(char * origSent, char * resSent) {
	int from = 0;
	int i = 0;

	while (i < strlen(resSent)) {
		if (resSent[i] == ' ' || i == strlen(resSent)-1) {
			if (i == strlen(resSent)-1) {
				i++;
			}
			int len = i-from;
			char * w = malloc(len+1);
			memcpy(w, resSent+from, len);
			w[len] = '\0';
			if (!isInLex(w, lex, WORD_NUM)) {
				free(w);
				return 0;
			}
			from = i+1;
			free(w);
		}
		i++;
	}

	int j = 0;
	i = 0;
	while (i < strlen(resSent) && j < strlen(origSent)) {
		if (resSent[i] != origSent[j]) {
			if (resSent[i] != ' ') {
				return 0;
			} else {
				j++;
			}
		} else {
			i++;
			j++;
		}
	}
	return 1;
}
