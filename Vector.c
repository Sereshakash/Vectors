#include <stdio.h>
#include <stdlib.h>
#include "RingInfo.h"

void* GetNelement(struct VectorN* vect, int n)
{
	int datatype = vect->datatype;
	if (datatype == 1)
		return (vect->elements + n * vect->ringInfo->size);
	if (datatype == 2)
		return (vect->elements + n * vect->ringInfo->size);
	if (datatype == 3)
		return (vect->elements + n * vect->ringInfo->size);
}

void PrintVector(struct VectorN* vector)
{
	int i;
	int datatype = vector->datatype;
	for (i = 0; i < vector->N; i++)
	{
		if (datatype == 1)
			printf("%d ", *((int*) (GetNelement(vector, i))));
		if (datatype == 2)
			printf("%f ", *((float*) (GetNelement(vector, i))));
		if (datatype == 3)
			printf("%f + %f * i\n", ((float*) (GetNelement(vector, i)))[0], ((float*) (GetNelement(vector, i)))[1]);
	}
	printf("\n");
}

void DeleteVector(struct VectorN* vector)
{
	free(vector->elements);
	free(vector);
}

void * CreateElements(struct RingInfo* ringInfo, int N, int datatype)
{
	printf("Введите %d чисел, выбранного типа данных, в столбик(в случае числа вида x+iy введите x и y через пробел)\n", N);
	int i;
	void * numbers = malloc(N * ringInfo->size);
	for (i = 0; i < N; i++)
	{
		if (datatype == 1)
			scanf("%d", (int*) (numbers + i * ringInfo->size));
		if (datatype == 2)
			scanf("%f", (float*) (numbers + i * ringInfo->size));
		if (datatype == 3)
			scanf("%f%f", (float*) (numbers + i * ((int)ringInfo->size)), (float*) (numbers + i * ((int) ringInfo->size) + (((int) ringInfo->size) / 2)));
	}
	return (void *) (numbers);
}

struct VectorN* CreateVector (struct RingInfo* ringInfo, int N, int datatype, void * numbers) {
	struct VectorN* vector = malloc(sizeof(struct VectorN));
	vector->N = N;
	vector->ringInfo = ringInfo;
	vector->elements = numbers;
	vector->datatype = datatype;
	return vector;
}
