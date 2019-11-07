#include "vector.h"

void VectorNew(vector *v, int elemSize, VectorFreeFunction freefn, int initialAllocation){
	assert(elemSize > 0);
	assert(initialAllocation >= 0);


	if (initialAllocation == 0)
		v-> initialAllocationSize = 10; else
		v-> initialAllocationSize = initialAllocation;
	
	v-> elemSize = elemSize;
	v-> logLen = 0;
	v-> allocLen = v->initialAllocationSize;

	v-> freefn = freefn;

	v-> base = malloc(elemSize * v->allocLen);

	assert(v->base != NULL);
}


void VectorDispose(vector *v){
	
	
	if (v->freefn != NULL){
		for (int i = 0; i < v->logLen; ++i)
		{
			void* pt = (char*)v->base + i * v->elemSize;
			v->freefn(pt);
		}
	}	

	free(v->base);
}

int VectorLength(const vector *v) {
	return v->logLen;
}

void *VectorNth(const vector *v, int position)
{ 
	assert(position >= 0 && position < v->logLen);

	void* pt = (char*)v->base + position * v->elemSize;

	return pt;
}

void VectorReplace(vector *v, const void *elemAddr, int position){
	assert(elemAddr != NULL);
	assert(position >= 0 && position < v->logLen);

	void* pt = VectorNth(v, position);
	if (v->freefn != NULL) v->freefn(pt);
	memcpy(pt,elemAddr, v->elemSize);	
}


void grow(vector* v){

	v->allocLen += v->initialAllocationSize;
	
	void* res =  realloc(v->base, v->allocLen * v->elemSize);
	
	assert(res != NULL);

	v->base = res;
}

void VectorInsert(vector *v, const void *elemAddr, int position)
{	
	
	assert(elemAddr != NULL);
	assert(position >= 0 && position <= v->logLen);

	if (v->logLen == v->allocLen) grow(v);

	for (int i = v->logLen; i>position; i--){
		
		void* pt1 = (char*)v->base + (i-1)*v->elemSize;
		void* pt2 = (char*)v->base + i*v->elemSize;
		
		memcpy(pt2, pt1, v->elemSize);
	}

	void* pt = (char*)v->base + position * v->elemSize;
	memcpy (pt, elemAddr, v->elemSize);

	v->logLen++;


}

void VectorAppend(vector *v, const void *elemAddr){
	VectorInsert(v, elemAddr, v->logLen);
}

void VectorDelete(vector *v, int position){
	
	assert (position >= 0 && position < v->logLen);

	void* pt = VectorNth(v, position);
	if (v->freefn != NULL) v->freefn(pt);

	v->logLen--;

	for (int i=position; i<v->logLen; i++){
		void* pt1 = (char*)v->base + i*v->elemSize;
		void* pt2 = (char*)v->base + (i+1)*v->elemSize;
		memcpy(pt1, pt2, v->elemSize);
	}
}

void VectorSort(vector *v, VectorCompareFunction compare){
	assert(compare != NULL);

	//base
	void* base = v->base;
	//n
	size_t n = v->logLen;
	//elemSize
	size_t elemSize = v->elemSize;

	qsort(base, n, elemSize, compare);

}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData){
	assert (mapFn != NULL);

	for (int i = 0; i < v->logLen; ++i)
	{
		void* pt = VectorNth(v,i);
		mapFn(pt, auxData);
	}

	
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted){

	assert (startIndex>=0 && startIndex <= v->logLen);
	assert (searchFn != NULL);
	assert (key != NULL);

	//base
	void* base = (char*)v->base + startIndex * v->elemSize;

	//n
	size_t totalNum;
	size_t* p = &totalNum;
	*p = v->logLen - startIndex;

	//elemSize
	size_t elemSize = v->elemSize;

	int ret;
	void* pt;

	if (isSorted)
		pt = bsearch(key, base, totalNum, elemSize, searchFn); else
		pt = lfind(key, base, (void *)p, elemSize, searchFn);

	if (pt == NULL) ret = kNotFound; else
					ret = ((size_t)pt - (size_t)base) / v->elemSize;
 
	return ret; 
}
