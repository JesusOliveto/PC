#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20000

int *v;
int mayor=0;


void *buscar(void *arg) {

    int *id = (int *) arg;//id del hilo
    int inicio = (*id) * (N / 2);//inicio de la mitad del arreglo
    int fin = inicio + (N / 2);//fin de la mitad del arreglo
    for (long i = inicio; i < fin; i++)
    {
        if (v[i]>mayor)
        {
            mayor=v[i];
            printf("encontrado nuevo mayor en la posicion %d en el hilo %d , valor= %d\n",i,*id, v[i]);
        }
        
    }
    pthread_exit(NULL);
}

void rellenar(int* v){

    time_t t;
    srand((unsigned) time(&t));

    for (long i = 0; i < N; i++)
    {
            v[i]=rand() % 9999;
    }

    v[N-1] = 9999;

    
}

int main() {
    pthread_t hilo1, hilo2;//hilos

    int id1 = 0, id2 = 1;//id de los hilos (0, 1) para buscar en la mitad del arreglo
    v = calloc(N, sizeof(int));
    
    rellenar(v);
    pthread_create(&hilo1, NULL, buscar, (void *) &id1);//crea el hilo 1
    pthread_create(&hilo2, NULL, buscar, (void *) &id2);//crea el hilo 2

    pthread_join(hilo1, NULL);//espera a que el hilo 1 termine
    pthread_join(hilo2, NULL);//espera a que el hilo 2 termine

    free(v);//libera el arreglo
    printf("mayor valor: %d\n",mayor);
    return 0;
}