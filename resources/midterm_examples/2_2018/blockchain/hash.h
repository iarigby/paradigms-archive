#ifndef _hash_
#define _hash_

#include "blockchain.h"

// static int StringHash(const void *elem, int numBuckets);
unsigned int BlockHash(Block *b);

#endif