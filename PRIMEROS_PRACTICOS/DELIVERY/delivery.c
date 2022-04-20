/* Se debe realizar el motor de un juego que denominaremos "Delivery". Este juego simulará la actividad de un local de comidas en el cual ingresan los pedidos por teléfono y los empleados tienen que preparar y entregar lo indicado.
En esta primer etapa se deberá trabajar sobre cuatro tipos de hilos:
encargado que da curso a los pedidos de los clientes y, luego de entregado el pedido, guarda el cobro en la caja,
telefono que genera los pedidos de los clientes,
cocinero que prepara la comida,
delivery que lleva los pedidos a los clientes,
El encargado atiende los pedidos que llegan por telefono separados un tiempo aleatorio. El cocinero prepara el pedido, demorando un tiempo diferente según la comida solicitada; solo puede preparar un pedido por vez. El delivery entrega los pedidos a los clientes (de a uno por vez), demorando un tiempo diferente (aleatorio) según la distancia, y al regresar entrega el monto del pedido al encargado.
Se debe sincronizar la interacción entre los hilos utilizando MUTEX según la necesidad. El delivery deberá esperar a que el cocinero termine el pedido antes de poder entregarlo.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

//cantidad de hilos
int cant_cocineros = 1;
int cant_delivery = 1;
int cant_telefonos = 1;
int cant_encargados = 1;

int limite_pedidos = 10;


void *cocinero(void *arg);

void *delivery(void *arg);

void *encargado(void *arg);

void *telefono(void *arg);

//semaforos
sem_t sem_cocinero;
sem_t sem_delivery;
sem_t sem_encargado;
sem_t sem_telefono;

//mutex
pthread_mutex_t mutex_cocinero;
pthread_mutex_t mutex_delivery;
pthread_mutex_t mutex_encargado;
pthread_mutex_t mutex_telefono;

//variables globales
int pedidos_totales = 0;
int pedidos_entregados = 0;
int pedidos_cocinados = 0;
int pedidos_atendidos = 0;
int pedidos_cocinando = 0;
int pedidos_entregando = 0;
int pedidos_atendiendo = 0;
int pedidos_telefono = 0;
int pedidos_caja = 0;

int main() {
    //inicializacion de semaforos
    sem_init(&sem_cocinero, 0, 0);
    sem_init(&sem_delivery, 0, 0);
    sem_init(&sem_encargado, 0, 0);
    sem_init(&sem_telefono, 0, 1);

    //inicializacion de mutex
    pthread_mutex_init(&mutex_cocinero, NULL);
    pthread_mutex_init(&mutex_delivery, NULL);
    pthread_mutex_init(&mutex_encargado, NULL);
    pthread_mutex_init(&mutex_telefono, NULL);

    //inicializacion de hilos
    pthread_t cocineros[cant_cocineros];
    pthread_t deliverys[cant_delivery];
    pthread_t encargados[cant_encargados];
    pthread_t telefonos[cant_telefonos];

    //creacion de hilos
    for (int i = 0; i < cant_cocineros; ++i) {
        pthread_create(&cocineros[i], NULL, cocinero, NULL);
    }
    for (int i = 0; i < cant_delivery; ++i) {
        pthread_create(&deliverys[i], NULL, delivery, NULL);
    }
    for (int i = 0; i < cant_encargados; ++i) {
        pthread_create(&encargados[i], NULL, encargado, NULL);
    }
    for (int i = 0; i < cant_telefonos; ++i) {
        pthread_create(&telefonos[i], NULL, telefono, NULL);
    }

    //espera de hilos
    for (int i = 0; i < cant_cocineros; ++i) {
        pthread_join(cocineros[i], NULL);
    }
    for (int i = 0; i < cant_delivery; ++i) {
        pthread_join(deliverys[i], NULL);
    }
    for (int i = 0; i < cant_encargados; ++i) {
        pthread_join(encargados[i], NULL);
    }
    for (int i = 0; i < cant_telefonos; ++i) {
        pthread_join(telefonos[i], NULL);
    }

    //destruccion de semaforos
    sem_destroy(&sem_cocinero);
    sem_destroy(&sem_delivery);
    sem_destroy(&sem_encargado);
    sem_destroy(&sem_telefono);

    //destruccion de mutex
    pthread_mutex_destroy(&mutex_cocinero);
    pthread_mutex_destroy(&mutex_delivery);
    pthread_mutex_destroy(&mutex_encargado);
    pthread_mutex_destroy(&mutex_telefono);

    return 0;
}

void *cocinero(void *arg) {
    while (pedidos_totales < limite_pedidos) {
        sem_wait(&sem_cocinero);
        pthread_mutex_lock(&mutex_cocinero);
        pedidos_cocinando++;
        printf("Cocinero %ld: Cocinando pedido %d\n", pthread_self(), pedidos_cocinados);
        pthread_mutex_unlock(&mutex_cocinero);
        sleep(rand() % 5);
        pthread_mutex_lock(&mutex_cocinero);
        pedidos_cocinando--;
        pedidos_cocinados++;
        printf("Cocinero %ld: Pedido %d cocinado\n", pthread_self(), pedidos_cocinados);
        pthread_mutex_unlock(&mutex_cocinero);
        sem_post(&sem_delivery);
    }
    pthread_exit(NULL);
}

void *delivery(void *arg) {
    while (pedidos_totales < limite_pedidos) {
        sem_wait(&sem_delivery);
        pthread_mutex_lock(&mutex_delivery);
        pedidos_entregando++;
        printf("Delivery %ld: Entregando pedido %d\n", pthread_self(), pedidos_entregados);
        pthread_mutex_unlock(&mutex_delivery);
        sleep(rand() % 5);
        pthread_mutex_lock(&mutex_delivery);
        pedidos_entregando--;
        pedidos_entregados++;
        printf("Delivery %ld: Pedido %d entregado\n", pthread_self(), pedidos_entregados);
        pthread_mutex_unlock(&mutex_delivery);
        sem_post(&sem_encargado);
    }
    pthread_exit(NULL);
}

void *encargado(void *arg) {
    while (pedidos_totales < limite_pedidos) {
        sem_wait(&sem_encargado);
        pthread_mutex_lock(&mutex_encargado);
        pedidos_atendiendo++;
        printf("Encargado %ld: Atendiendo pedido %d\n", pthread_self(), pedidos_atendidos);
        pthread_mutex_unlock(&mutex_encargado);
        //sleep(rand() % 5);
        pthread_mutex_lock(&mutex_encargado);
        pedidos_atendiendo--;
        pedidos_atendidos++;
        printf("Encargado %ld: Pedido %d atendido\n", pthread_self(), pedidos_atendidos);
        pthread_mutex_unlock(&mutex_encargado);
        sem_post(&sem_telefono);
    }
    pthread_exit(NULL);
}

void *telefono(void *arg) {
    while (pedidos_totales < limite_pedidos) {
        sem_wait(&sem_telefono);
        pthread_mutex_lock(&mutex_telefono);
        pedidos_telefono++;
        printf("Telefono %ld: Llamada %d\n", pthread_self(), pedidos_telefono);
        pthread_mutex_unlock(&mutex_telefono);
        sleep(rand() % 5);
        pthread_mutex_lock(&mutex_telefono);
        pedidos_telefono--;
        pedidos_totales++;
        printf("Telefono %ld: Pedido %d recibido\n", pthread_self(), pedidos_totales);
        pthread_mutex_unlock(&mutex_telefono);
        sem_post(&sem_cocinero);
    }
    pthread_exit(NULL);
}




