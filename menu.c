#include <stdio.h>
#include <stdlib.h>
#include "RingInfo.h"

struct Status
{
    int N;
    struct VectorN* vector1;
    struct VectorN* vector2;
    int key;
    int datatype; /// 1 - int; 2 - float; 3 - comlex number
};
void NewVectorElem(int datatype, void * elements, void * elem, struct RingInfo* ringInfo, int i) {
    if (datatype == 1) {
        ((int*) (elements))[i] = *((int *) elem); 
        free(elem);
    }
	if (datatype == 2) {
		((float*) (elements))[i] = *((float *) elem); 
        free(elem);
    }
	if (datatype == 3) {
        ((float*) (elements))[2 * i] = ((float *) elem)[0]; 
        ((float*) (elements))[2 * i + 1] = ((float *) elem)[1];
        free(elem); 
    }
    elements = (void*) elements;
}

struct RingInfo* Datatype (int choice, int * datatype) 
{
    struct RingInfo* ringInfo;
    switch (choice)
    {
    case 1: 
    {
        *datatype = choice;
        int *the_zero, *the_one;
        the_zero = malloc(sizeof(int *));
        the_one = malloc(sizeof(int *));
        *the_zero = 0;
        *the_one = 1;
        ringInfo = Create(sizeof(int), &sumInt, (void *) (the_zero), &minusInt, &multInt, (void *) (the_one));
        break;
    }
    case 2: 
    {
        *datatype = choice;
        float *the_zero, *the_one;
        the_zero = malloc(sizeof(float *));
        the_one = malloc(sizeof(float *));
        *the_zero = 0.0;
        *the_one = 1.0;
        ringInfo = Create(sizeof(float), &sumFloat, (void *) (the_zero), &minusFloat, &multFloat, (void *) (the_one));
        break;
    }
    case 3: 
    {
        *datatype = choice;
        float *the_zero, *the_one;
        the_zero = malloc(sizeof(float *) * 2);
        the_one = malloc(sizeof(float *) * 2);
        the_one[0] = 1.0;
        the_one[1] = 0.0;
        the_zero[0] = 0.0;
        the_zero[1] = 0.0;
        ringInfo = Create(sizeof(float) * 2, &sumComplex, (void *) (the_zero), &minusComplex, &multComplex,(void *) (the_one));
        break;
    }
    default:
        printf("Некорректный выбор\n");
        break;
    }
    return ringInfo;
}

int main() {
    struct Status status = {0, NULL, NULL, 0, 0};
    while (!(status.key)) {
        printf("Выберите действие. 1) Сменить число N (степень вектора) и тип данных, ввести вектора ");
        printf("2) Выполнить действие над векторами 3) Закончить работу\n");  
        int choice1;
        scanf("%d", &choice1);
        switch (choice1)
        {
        case 1:
        {
            if (status.vector1 != NULL) 
                DeleteVector(status.vector1);

            if (status.vector2 != NULL) 
            {
                free((status.vector2)->ringInfo->one);
                free((status.vector2)->ringInfo->zero);
                free((status.vector2)->ringInfo);
                DeleteVector(status.vector2);
            }
            printf("Введите N\n");
            scanf("%d", &(status.N));
            printf("Выберите тип данных: 1) Целые 2) Вещественные 3) Комплексные числа\n");
            int choice2;
            scanf("%d", &choice2);
            struct RingInfo* ringInfo;
            ringInfo = Datatype(choice2, &(status.datatype)); 
            struct VectorN* vector1;
            void * elements1;
            elements1 = CreateElements(ringInfo, status.N, status.datatype);
            vector1 = CreateVector(ringInfo, status.N, status.datatype, elements1);
            struct VectorN* vector2;
            void * elements2;
            elements2 = CreateElements(ringInfo, status.N, status.datatype);
            vector2 = CreateVector(ringInfo, status.N, status.datatype, elements2);
            status.vector1 = vector1;
            status.vector2 = vector2;       
            printf("Вектора:\n");   
            PrintVector(status.vector1);
            PrintVector(status.vector2);
            break;
        }
        case 2:
        {
            printf("Выберите действие: 1) Сложить вектора 2) Посчитать скалярное произведение \n");
            printf("3) Напечатать вектора 4) Умножить вектор на число\n");
            int choice3;
            scanf("%d", &choice3);
            switch (choice3)
            {
            case 1:
            {
                int i;
                void * elements = malloc(status.vector1->ringInfo->size * status.N);
                for (i = 0; i < status.N; i++)
                {
                    void * elI;
                    elI = status.vector1->ringInfo->sum(GetNelement(status.vector1, i), GetNelement(status.vector2, i));
                    NewVectorElem(status.datatype, elements, elI, status.vector2->ringInfo, i);
                }
                struct VectorN* vector;
                vector = CreateVector(status.vector1->ringInfo, status.N, status.datatype, elements);
                printf("Суммарный вектор:\n");
                PrintVector(vector);
                DeleteVector(vector);
                break;
            }
            case 2:
            {
                int i;
                void * ScMult;
                void * ScMult1;
                ScMult = status.vector1->ringInfo->zero;
                for (i = 0; i < status.N; i++)
                {
                    void * elI;
                    elI = status.vector1->ringInfo->mult(GetNelement(status.vector1, i), GetNelement(status.vector2, i));
                    ScMult1 = status.vector1->ringInfo->sum(ScMult, elI);
                    if (i != 0)
                        free(ScMult);
                    free(elI);
                    ScMult = ScMult1;
                }
                printf("Скалярное произведение векторов:\n");
                if (status.datatype == 1)
			        printf("%d\n", *((int*) (ScMult)));
	        	if (status.datatype == 2)
		        	printf("%f\n", *((float*) (ScMult)));
	        	if (status.datatype == 3)
		        	printf("%f + %f * i\n", ((float*) (ScMult))[0], ((float*)  (ScMult))[1]);
                free(ScMult1);
                break;
            }
            case 3:
            {
                printf("Вектор 1:\n");
                PrintVector(status.vector1);
                printf("Вектор 2:\n");
                PrintVector(status.vector2);
                break;
            }
            case 4:
            {
                void * A = malloc(status.vector1->ringInfo->size);
                printf("Введите число A, выбранного типа данных (в случае числа вида x+iy введите x и y через пробел)\n");
                if (status.datatype == 1)
		        	scanf("%d", (int*) (A));
	        	if (status.datatype == 2)
	        		scanf("%f", (float*) (A));
	        	if (status.datatype == 3)
		        	scanf("%f%f", &(((float*) (A))[0]), &(((float*) (A))[1]));
                int i;
                A = (void*) (A);
                
                printf("Выберете вектор, который умножим на число А(1 или 2)\n");
                int choice4;
                scanf("%d", &choice4);
                struct VectorN* vector;
                if (choice4 == 1)
                    vector = status.vector1;
                if (choice4 == 2)
                    vector = status.vector2;
                if (!(choice4 == 1 || choice4 == 2)) {
                    printf("Некорректный выбор\n");
                    free(A);
                    break;
                }
                void * elements = malloc(status.vector1->ringInfo->size * status.N);
                for (i = 0; i < status.N; i++)
                {
                    void * elI;
                    elI = status.vector1->ringInfo->mult(GetNelement(vector, i), A);
                    NewVectorElem(status.datatype, elements, elI, status.vector2->ringInfo, i);
                }
                struct VectorN* vector_rez;
                vector_rez = CreateVector(status.vector1->ringInfo, status.N, status.datatype, elements);
                printf("Полученнный вектор:\n");
                PrintVector(vector_rez);
                DeleteVector(vector_rez);
                free(A);
                break;
            }
            default:
                printf("Некорректный выбор\n");
                break;
            }
            break;
        }
        case 3:
        {
            if (status.vector1 != NULL) 
                DeleteVector(status.vector1);

            if (status.vector2 != NULL) 
            {
                free((status.vector2)->ringInfo->one);
                free((status.vector2)->ringInfo->zero);
                free((status.vector2)->ringInfo);
                DeleteVector(status.vector2);
            }
            status.key = 1;
            printf("Хорошего дня!\n");
            break;
        }
        default:
            printf("Некорректный выбор\n");
            break;
        }
    }
    return 0;
}