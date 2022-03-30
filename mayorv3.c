#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 200000
#define hilos 20 //cantidad de hilos
int *v;
int mayor=0;


void *buscar(void *arg);

void rellenar(int* v);

int main() {
    pthread_t hilo[hilos];
    int id[hilos];
    for (int i =0;i<hilos;i++){
        id[i]=i;
    }
    v = calloc(N, sizeof(int));
    
    rellenar(v);

    for (int i =0;i<hilos;i++){
        pthread_create(&hilo[i], NULL, buscar, (void *) &id[i]);
    }
    for (int i = 0; i < hilos; i++)
    {
        pthread_join(hilo[i], NULL);
    }
    
    printf("mayor valor: %d\n",mayor);
    free(v);//libera el arreglo
    return 0;
}


void *buscar(void *arg) {

    int *id = (int *) arg;//id del hilo
    int inicio = (*id) * (N / hilos);//inicio de la mitad del arreglo
    int fin = inicio + (N / hilos);//fin de la mitad del arreglo
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

    v[N-1] = 99999;

    
}
