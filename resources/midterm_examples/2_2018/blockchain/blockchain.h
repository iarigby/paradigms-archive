#ifndef _blockchain_
#define  _blockchain_
#include "vector.h"
//#include "hashset.h"
#include <ctype.h>

typedef struct {
	char * from;
	char * to;
	int amount;
} Transaction;

typedef struct{
	vector * transactions;
	int previousHash;
} Block;



typedef vector BlockChain;

void mapfn(void *elem, void *auxData);
static int cmpr(const void* s1, const void* s2);
void mapfnct(void* elem, void* aux);

void addBlock(BlockChain *bc, Block *b);
int isValid(BlockChain *bc);
char * getMaxBalance(BlockChain *bc);

#endif