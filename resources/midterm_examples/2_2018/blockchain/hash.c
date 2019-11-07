#include "hash.h"
#include "blockchain.h"

unsigned int BlockHash(Block *b)
{
    unsigned long hash = 5381;
    int c;
    int length = b->transactions->logLen * b->transactions->elemSize;

    for (int i=0; i < length; i++) {
        c = ((char*)b->transactions->base)[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    hash = hash + b->previousHash;

    return hash;
}