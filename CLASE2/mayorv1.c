#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 2000000


void buscar(int* daniel){
    int mayor=0;
    for (long i = 0; i < N; i++)
    {
        if (daniel[i]>mayor)
        {
            mayor=daniel[i];
            printf("encontrado nuevo mayor en la posicion %d , valor= %d\n",i, daniel[i]);
        }
        
    }
}

void rellenar(int* daniel){

    time_t t;
    srand((unsigned) time(&t));

    for (long i = 0; i < N; i++)
    {
            daniel[i]=rand() % 9999;
    }

    daniel[N-1] = 9999;

    
}

int main(int argc, char const *argv[])
{
    int* daniel= (int*)calloc(N, sizeof(int));
    rellenar(daniel);
    buscar(daniel);
    free(daniel);

    return 0;
}
