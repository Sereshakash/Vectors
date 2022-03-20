#include <stdio.h>
#include <stdlib.h>

void* sumInt(void* a1, void* a2) {
	int* ia1 = (int*)a1;
	int* ia2 = (int*)a2;
	int* res = malloc(sizeof(int));
	*res = *ia1 + *ia2;
	return (void*)res;
}

void* sumFloat(void* a1, void* a2) {
	float* ia1 = (float*)a1;
	float* ia2 = (float*)a2;
	float* res = malloc(sizeof(float));
	*res = *ia1 + *ia2;
	return (void*)res;
}

void* sumComplex(void* a1, void* a2) {
	float* ia1 = (float*)a1;
	float* ia2 = (float*)a2;
	float* res = malloc(sizeof(float) * 2);
	res[0] = ia1[0] + ia2[0];
	res[1] = ia1[1] + ia2[1];
	return (void*)res;
}

void* multInt(void* a1, void* a2) {
	int* ia1 = (int*)a1;
	int* ia2 = (int*)a2;
	int* res = malloc(sizeof(int));
	*res = (*ia1) * (*ia2);
	return (void*)res;
}

void* multFloat(void* a1, void* a2) {
	float* ia1 = (float*)a1;
	float* ia2 = (float*)a2;
	float* res = malloc(sizeof(float));
	*res = (*ia1) * (*ia2);
	return (void*)res;
}

void* multComplex(void* a1, void* a2) {
	float* ia1 = (float*)a1;
	float* ia2 = (float*)a2;
	float* res = malloc(sizeof(float) * 2);
	res[0] = ia1[0] * ia2[0] - ia1[1] * ia2[1];
	res[1] = ia1[0] * ia2[1] + ia1[1] * ia2[0];
	return (void*)res;
}

void* minusInt(void* a1) {
	int* ia1 = (int*)a1;
	int* res = malloc(sizeof(int));
	*res = - (*ia1);
	return (void*)res;
}

void* minusFloat(void* a1) {
	float* ia1 = (float*)a1;
	float* res = malloc(sizeof(float));
	*res = - (*ia1);
	return (void*)res;
}

void* minusComplex(void* a1) {
	float* ia1 = (float*)a1;
	float* res = malloc(sizeof(float) * 2);
	res[0] = - ia1[0];
	res[1] = - ia1[1];
	return (void*)res;
}

struct RingInfo {
	size_t size;
	void* (*sum)(void*, void*);
	void* zero;
	void* (*minus)(void*);
	void* (*mult)(void*, void*);
	void* one;
};

struct RingInfo* Create(	
	size_t size,
	void* (*sum)(void*, void*),
	void* zero,
	void* (*minus)(void*),
	void* (*mult)(void*, void*),
	void* one)
{
    struct RingInfo* ringInfo = malloc(sizeof(struct RingInfo));
	ringInfo->size = size;
	ringInfo->sum = sum;
	ringInfo->zero = zero;
	ringInfo->minus = minus;
	ringInfo->mult = mult;
	ringInfo->one = one;
	return ringInfo;
}


