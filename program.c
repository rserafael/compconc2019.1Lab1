/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 1 */
/* Codigo: "Hello World" usando threads em C e a funcao join*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NThreads 2

typedef struct
{
    int idThread, startIndex, endIndex;
    int *array;
} t_Args;

void *incrementArray(void *arg)
{
    t_Args *args = (t_Args *)arg;

    printf("Sou a thread %d\n", args->idThread);
    printf("E incrementarei os elementos de indice %d até %d incluso.\n", args->startIndex, args->endIndex);
    for (int i = args->startIndex; i <= args->endIndex; i++)
    {
        // printf("i = %d\n", i);
        args->array[i] = args->array[i] + 1;
        printf("thread %d: array[%d] = %d\n", args->idThread, i, args->array[i]);
    }
    free(arg);
    pthread_exit(NULL);
}

void setSize(int *size)
{
    scanf("%d", size);
    printf("size = %d\n", *size);
}

void setArray(int *array, int size)
{
    for (int t = 0; t < size; t++)
    {
        scanf("%d", &array[t]);
        printf("array[%d] = %d\n", t, array[t]);
    }
}

//funcao principal do programa
int main()
{
    int size;
    setSize(&size);
    int array[size];
    setArray(array, size);
    
    int startIndex = 0, endIndex = (endIndex % 2 == 0) ? (size / 2) - 1 : ((size - 1) / 2);
    printf("startIndex = %d, endIndex = %d\n", startIndex, endIndex);

    for (int i = 0; i < size; i++)
    {
        printf("array[%d] = %d\n", i + 1, array[i]);
    }

    pthread_t threads[NThreads];
    t_Args *arg;

    for (int j = 0; j < NThreads; j++)
    {
        arg = malloc(sizeof(t_Args));
        if (arg == NULL)
        {
            printf("--ERRO: malloc()\n");
            printf("j = %d\n", j);
            exit(-1);
        }

        arg->idThread = j + 1;
        arg->startIndex = startIndex;
        arg->endIndex = endIndex;
        arg->array = array;

        startIndex = endIndex + 1;
        endIndex = size - 1;

        printf("--Cria a thread %d\n", j + 1);
        if (pthread_create(&threads[j], NULL, incrementArray, (void *)arg))
        {
            printf("--ERRO: pthread_create()\n");
            exit(-1);
        }
    }

    for (int t = 0; t < NThreads; t++)
    {
        if (pthread_join(threads[t], NULL))
        {
            printf("--ERRO: pthread_join() \n");
            exit(-1);
        }
    }

    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}
