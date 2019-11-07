#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "hash.h"
#define INIT_ALLOC 4

BlockChain * newBlockChain() {
    BlockChain *bc = malloc(sizeof(BlockChain));
    VectorNew(bc, sizeof(Block), NULL, 4);
    return bc;
}

Transaction * newTransaction(int amount, char * from, char * to) {
    Transaction *t = malloc(sizeof(Transaction));
    t->amount = amount;
    t->from = strdup(from);
    t->to = strdup(to);
    return t;    
}

Block * newBlock(int hash) {
    Block *b = malloc(sizeof(Block));
    b->previousHash = hash;
    b->transactions = malloc(sizeof(vector));
    VectorNew(b->transactions, sizeof(Transaction), NULL, INIT_ALLOC);
    return b;
}

void addTransactions(Block *b, int num){
    for(int i=0; i<num; i++) {
        VectorAppend(b->transactions, newTransaction(i, "acc1", "acc2"));
    }
}
// 1 transaction 1 block; 
// check for validity
int test1() {
	BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t = newTransaction(11, "acc1", "acc2");
    // put transaction in a block
    Block *b = newBlock(0);
    VectorAppend(b->transactions, t);
    // add block to chain
    addBlock(bc, b);
    return isValid(bc) &&
            VectorLength(b->transactions) == 1 
            && VectorLength(bc) == 1;
}

// 1 transaction 1 block; 
// check for max account name
int test2() {
	BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t = newTransaction(12, "acc1", "acc2");
    // put transaction in a block
    Block *b = newBlock(0);
    VectorAppend(b->transactions, t);
    // add block to chain
    addBlock(bc, b);
    char *name = getMaxBalance(bc);
    return !strcmp(name, t->to);
}

// 2 transaction 1 block; 
// check for validity
int test3() {
	BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(10, "acc1", "acc2");
    // put transaction in a block
    Block *b = newBlock(0);
    VectorAppend(b->transactions, t1);
    VectorAppend(b->transactions, t2);
    // add block to chain
    addBlock(bc, b);
    return  isValid(bc) && 
            VectorLength(b->transactions) == 2 && 
            VectorLength(bc) == 1;
}

// 2 transaction 1 block; 
// check for max account name
int test4() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(11, "acc3", "acc4");
    // put transaction in a block
    Block *b = newBlock(0);
    VectorAppend(b->transactions, t1);
    VectorAppend(b->transactions, t2);
    // add block to chain
    addBlock(bc, b);
    char *name = getMaxBalance(bc);
    return !strcmp(name, t2->to);
}

// 2 block 1 transaction pre block ; 
// check for validity
int test5() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(110, "acc3", "acc4");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create a block 2
    Block *b2 = newBlock(BlockHash(b1));
    VectorAppend(b2->transactions, t2);
    addBlock(bc, b2);
    int validBefore = isValid(bc);
    Block * bb = VectorNth(bc, 1);
    bb->previousHash = 0;    

    return !isValid(bc) && validBefore &&
            VectorLength(bc) == 2 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 1;
}

// 2 block 1 transaction pre block ; check for validity
// invalid blockchain
int test6() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(110, "acc3", "acc4");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create a block 2
    Block *b2 = newBlock(0);
    VectorAppend(b2->transactions, t2);
    addBlock(bc, b2);
    return !isValid(bc) &&
            VectorLength(bc) == 2 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 1;
}

// 2 block 1 transaction pre block; money is transferred back!
// check for max account
int test7() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(11, "acc2", "acc1");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create a block 2
    Block *b2 = newBlock(BlockHash(b1));
    VectorAppend(b2->transactions, t2);
    addBlock(bc, b2);
    char *name = getMaxBalance(bc);
    return !strcmp(name, t1->from); 
}

// 3 block 1 transaction pre block; second block has no transactions
// check for validity
int test8() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t3 = newTransaction(110, "acc2", "acc1");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create a block 2
    Block *b2 = newBlock(BlockHash(b1));
    addBlock(bc, b2);
    // create a block 3
    Block *b3 = newBlock(BlockHash(b2));
    VectorAppend(b3->transactions, t3);
    addBlock(bc, b3);
    int validBefore = isValid(bc);
    Block * bb = VectorNth(bc, 2);
    bb->previousHash = 0; 

    return !isValid(bc) && validBefore &&
            VectorLength(bc) == 3 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 0 && 
            VectorLength(b3->transactions) == 1;
}

// 3 block 1 transaction pre block; second block has no transactions
// check for validity: before and After!
int test9() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t3 = newTransaction(110, "acc2", "acc1");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create and add empty 2nd block
    Block *b2 = newBlock(BlockHash(b1));
    addBlock(bc, b2);  
    // create a block 3
    Block *b3 = newBlock(BlockHash(b2));
    VectorAppend(b3->transactions, t3);
    addBlock(bc, b3);
    int wasValid = isValid(bc); 
    b2 = VectorNth(bc, 1);
    Block * bb = VectorNth(bc, 1);
    bb->previousHash = 0; 

    return wasValid && !isValid(bc) && 
            VectorLength(bc) == 3 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 0 && 
            VectorLength(b3->transactions) == 1;    
}

// 3 block 1 transaction pre block; second block has no transactions
// check for validity: before and After!
int test10() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(10, "acc2", "acc3");
    Transaction *t3 = newTransaction(9, "acc3", "acc1");
    Transaction *t4 = newTransaction(1, "acc3", "acc2");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create and add empty 2nd block
    Block *b2 = newBlock(BlockHash(b1));
    VectorAppend(b2->transactions, t2);
    addBlock(bc, b2);  
    // create a block 3
    Block *b3 = newBlock(BlockHash(b2));
    VectorAppend(b3->transactions, t3);
    VectorAppend(b3->transactions, t4);
    addBlock(bc, b3);
    int validBefore = isValid(bc);
    Block * bb = VectorNth(bc, 2);
    bb->previousHash = 0; 

    return !isValid(bc) && validBefore &&
            VectorLength(bc) == 3 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 1 && 
            VectorLength(b3->transactions) == 2 &&
            !strcmp(getMaxBalance(bc), t4->to);    
}

int test11() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(10, "acc2", "acc3");
    Transaction *t3 = newTransaction(9, "acc3", "acc1");
    Transaction *t4 = newTransaction(1, "acc3", "acc2");
    Transaction *t5 = newTransaction(5, "acc3", "acc1");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create and add empty 2nd block
    Block *b2 = newBlock(BlockHash(b1));
    VectorAppend(b2->transactions, t2);
    addBlock(bc, b2);  
    // create a block 3
    Block *b3 = newBlock(BlockHash(b2));
    VectorAppend(b3->transactions, t3);
    VectorAppend(b3->transactions, t4);
    VectorAppend(b3->transactions, t5);
    addBlock(bc, b3);
    int validBefore = isValid(bc);
    Block * bb = VectorNth(bc, 1);
    bb->previousHash = 0; 
    return !isValid(bc) && validBefore &&
            VectorLength(bc) == 3 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 1 && 
            VectorLength(b3->transactions) == 3 &&
            !strcmp(getMaxBalance(bc), t1->from);    
}

int test12() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(10, "acc2", "acc3");
    Transaction *t3 = newTransaction(9, "acc3", "acc1");
    Transaction *t4 = newTransaction(1, "acc3", "acc2");
    Transaction *t5 = newTransaction(5, "acc3", "acc1");
    Transaction *t6 = newTransaction(5, "acc1", "acc6");
    Transaction *t7 = newTransaction(4, "acc1", "acc4");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    addBlock(bc, b1);
    // create and add empty 2nd block
    Block *b2 = newBlock(BlockHash(b1));
    VectorAppend(b2->transactions, t2);
    addBlock(bc, b2);  
    // create a block 3
    Block *b3 = newBlock(BlockHash(b2));
    VectorAppend(b3->transactions, t3);
    VectorAppend(b3->transactions, t4);
    VectorAppend(b3->transactions, t5);
    addBlock(bc, b3);
    Block *b4 = newBlock(BlockHash(b3));
    addBlock(bc, b4);
    Block *b5 = newBlock(BlockHash(b4));
    VectorAppend(b5->transactions, t6);
    VectorAppend(b5->transactions, t7);   
    addBlock(bc, b5);
    int validBefore = isValid(bc);
    Block * bb = VectorNth(bc, 4);
    bb->previousHash = 0; 

    return !isValid(bc) && validBefore &&
            VectorLength(bc) == 5 &&
            VectorLength(b1->transactions) == 1 && 
            VectorLength(b2->transactions) == 1 && 
            VectorLength(b3->transactions) == 3 &&
            VectorLength(b4->transactions) == 0 &&
            VectorLength(b5->transactions) == 2 &&
            !strcmp(getMaxBalance(bc), "acc6");    
}

int test13() {
    BlockChain *bc = newBlockChain();
    // create a transaction
    Transaction *t1 = newTransaction(10, "acc1", "acc2");
    Transaction *t2 = newTransaction(10, "acc2", "acc3");
    Transaction *t3 = newTransaction(9, "acc3", "acc1");
    Transaction *t4 = newTransaction(1, "acc3", "acc2");
    Transaction *t5 = newTransaction(5, "acc3", "acc1");
    Transaction *t6 = newTransaction(10, "acc3", "acc2");
    // put transaction in a block
    Block *b1 = newBlock(0);
    VectorAppend(b1->transactions, t1);
    VectorAppend(b1->transactions, t2);
    VectorAppend(b1->transactions, t3);
    VectorAppend(b1->transactions, t4);
    VectorAppend(b1->transactions, t5);
    addBlock(bc, b1);
    // create and add empty 2nd block
    Block *b2 = newBlock(BlockHash(b1));
    addBlock(bc, b2);  
    Block *b3 = newBlock(BlockHash(b2));
    addBlock(bc, b3);  
    Block *b4 = newBlock(BlockHash(b3));
    addBlock(bc, b4);  
    Block *b5 = newBlock(BlockHash(b4));
    VectorAppend(b5->transactions, t6);
    addBlock(bc, b5);
    Block *b6 = newBlock(BlockHash(b5));
    addBlock(bc, b6);  
    int validBefore = isValid(bc);
    Block * bb = VectorNth(bc, 4);
    bb->previousHash = 0; 
    return !isValid(bc) && validBefore &&
            VectorLength(bc) == 6 &&
            VectorLength(b1->transactions) == 5 && 
            VectorLength(b2->transactions) == 0 && 
            VectorLength(b5->transactions) == 1 &&
            !strcmp(getMaxBalance(bc), "acc2");    
}
// stress test code
// check for validity
int test14() {
    BlockChain *bc = newBlockChain();
    int numBlocks = 100;
    Block ** blocks = malloc(numBlocks * sizeof(Block *));

    // generate and add blocks to blockchain
    int previousHash = 0;
    for (int i=0; i < numBlocks; i++) {
        blocks[i] = newBlock(previousHash);
        addTransactions(blocks[i], i);
        addBlock(bc, blocks[i]);
        previousHash = BlockHash(blocks[i]);
        if (VectorLength(blocks[i]->transactions) != i) {
            return 0;
        }
    }

    int wasValid = isValid(bc);
    Block * b = VectorNth(bc, 45);
    b->previousHash = 0;
    return wasValid && !isValid(bc) && VectorLength(bc) == numBlocks;
}

int test15() {
    BlockChain *bc = newBlockChain();
    int numBlocks = 100;
    Block ** blocks = malloc(numBlocks * sizeof(Block *));

    // generate and add blocks to blockchain
    int previousHash = 0;
    for (int i=0; i < numBlocks; i++) {
        blocks[i] = newBlock(previousHash);
        addTransactions(blocks[i], i);
        addBlock(bc, blocks[i]);
        previousHash = BlockHash(blocks[i]);
        if (VectorLength(blocks[i]->transactions) != i) {
            return 0;
        }
    }

    int wasValid = isValid(bc);
    Block * b = VectorNth(bc, 45);
    b->previousHash = 0;
    return wasValid && !isValid(bc) && VectorLength(bc) == numBlocks;
}

int runTest(int testNum) {
  switch(testNum) {
    case 1: return test1();
    case 2: return test2();
    case 3: return test3();
    case 4: return test4();
    case 5: return test5();
    case 6: return test6();
    case 7: return test7();
    case 8: return test8();
    case 9: return test9();
    case 10: return test10();
    case 11: return test11();
    case 12: return test12();
    case 13: return test13();
    case 14: return test14();
    case 15: return test15();
  }
  return 0;
}

int main(int argc, char * args[]) {
  int num = atoi(args[1]);
  int testNum = num;
  int res = runTest(testNum);

  // for (int i=1; i<=15; i++) {
  //   printf("%d - %d\n", i, runTest(i));
  // }

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
