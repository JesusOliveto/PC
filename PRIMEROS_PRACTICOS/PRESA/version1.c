#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 2000000


void buscar(int* daniel){
    for (long i = 0; i < N; i++)
    {
        if (daniel[i]==1)
        {
            printf("encontrado en posicion %d \n",i);
            return;
        }
        else if (i==N-1)
        {
            printf("no ta");
        }
        
    }
}

void rellenar(int* daniel){

    time_t t;
    srand((unsigned) time(&t));

    for (long i = 0; i < N; i++)
    {
        daniel[i]=0;
    }

    daniel[rand() % N] = 1;

    
}

int main(int argc, char const *argv[])
{
    int* daniel= (int*)calloc(N, sizeof(int));
    rellenar(daniel);
    buscar(daniel);
    free(daniel);

    return 0;
}
