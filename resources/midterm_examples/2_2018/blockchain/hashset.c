#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn)
{
	h->elemSize = elemSize;
	h->numBuckets = numBuckets;
	h->hashfn = hashfn;
	h->freefn = freefn;
	h->comparefn = comparefn;
	h->logLen = 0;

	h->base = malloc (numBuckets * sizeof(vector));
	assert(h->base != NULL);

	for (int i = 0; i < numBuckets; ++i)
	{
		vector* vectorBase = (vector*)((char*)h->base + sizeof(vector) * i);

		VectorNew(vectorBase, elemSize, freefn, 0);
	}
}

void HashSetDispose(hashset *h){


	for (int i = 0; i < h->numBuckets; ++i)
	{
		vector* vectorBase = (vector*)((char*)h->base + sizeof(vector) * i);
		VectorDispose(vectorBase);
	}

	free(h->base);
}

int HashSetCount(const hashset *h)
{ return h->logLen; }

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData){
	assert(mapfn != NULL);

	for (int i = 0; i < h->numBuckets; ++i)
	{
		vector* vectorBase = (vector*)((char*)h->base + sizeof(vector) * i);
		VectorMap(vectorBase, mapfn, auxData);	
	}

}

void HashSetEnter(hashset *h, const void *elemAddr){
	assert(elemAddr != NULL);
	
	int hash = h->hashfn(elemAddr, h->numBuckets);
	assert(hash >=0 && hash < h->numBuckets);

	vector* vectorBase = (vector*)((char*)h->base + sizeof(vector) * hash);
	
	int pos = VectorSearch(vectorBase, elemAddr, h->comparefn, 0, false);		

	if (pos == -1){
		VectorAppend(vectorBase, elemAddr);
		h->logLen++;
	} else
		VectorReplace(vectorBase, elemAddr, pos);

}

void *HashSetLookup(const hashset *h, const void *elemAddr){

	assert(elemAddr != NULL);
	int hash = h->hashfn(elemAddr, h->numBuckets);
	assert(hash >=0 && hash < h->numBuckets);

	vector* vectorBase = (vector*)((char*)h->base + sizeof(vector) * hash);
	
	int pos = VectorSearch(vectorBase, elemAddr, h->comparefn, 0, false);		
	
	if (pos == -1) return NULL; 

	return VectorNth(vectorBase, pos);

}
