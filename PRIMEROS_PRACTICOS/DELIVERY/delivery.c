/* Se debe realizar el motor de un juego que denominaremos "Delivery". Este juego simulará la actividad de un local de comidas en el cual ingresan los pedidos por teléfono y los empleados tienen que preparar y entregar lo indicado.

En esta primer etapa se deberá trabajar sobre cuatro tipos de hilos:

    encargado que da curso a los pedidos de los clientes y, luego de entregado el pedido, guarda el cobro en la caja,
    telefono que genera los pedidos de los clientes,
    cocinero que prepara la comida,
    delivery que lleva los pedidos a los clientes,


El encargado atiende los pedidos que llegan por telefono separados un tiempo aleatorio. El cocinero prepara el pedido, demorando un tiempo diferente según la comida solicitada; solo puede preparar un pedido por vez. El delivery entrega los pedidos a los clientes (de a uno por vez), demorando un tiempo diferente (aleatorio) según la distancia, y al regresar entrega el monto del pedido al encargado.

Se debe sincronizar la interacción entre los hilos utilizando MUTEXES según la necesidad (revisar Split Mutex). */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int noExplotesPorFavor=20;

#define CANTIDAD_COCINEROS 1
#define CANTIDAD_DELIVERY 1 

void *encargado(void *arg);
void *telefono(void *arg);
void *cocinero(void *arg);
void *delivery(void *arg);
//AGREGAR UN MUTEX POR HILO
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char const *argv[])
{
    pthread_t encargados,telefonos,cocineros[CANTIDAD_COCINEROS],deliverys[CANTIDAD_DELIVERY];
    pthread_mutex_init(&mutex, NULL);

    //creacion de hilos
    pthread_create(&encargados,NULL,encargado,NULL);
    pthread_create(&telefonos,NULL,telefono,NULL);
    for (int i = 0; i < CANTIDAD_COCINEROS; i++)
    {
        pthread_create(&cocineros[i], NULL, cocinero, (void *) i);
    }
    for (int i = 0; i < CANTIDAD_DELIVERY; i++)
    {
        pthread_create(&deliverys[i], NULL, delivery, (void *) i);
    }


    //espera de hilos
    for (int i = 0; i < CANTIDAD_DELIVERY; i++)
    {
        pthread_join(deliverys[i], NULL);
    }
    for (int i = 0; i < CANTIDAD_COCINEROS; i++)
    {
        pthread_join(cocineros[i], NULL);
    }
    pthread_join(encargados, NULL);
    pthread_join(telefonos, NULL);

    pthread_mutex_destroy(&mutex);

    
    
    
    return 0;
}


void *encargado(void *arg){
    while(noExplotesPorFavor>0){

        pthread_mutex_lock(&mutex);
        printf("Encargado: Pedido recibido\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Encargado: Pedido entregado\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Encargado: Pedido cobrado\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);

        noExplotesPorFavor--;
    }
}
void *telefono(void *arg){
    while(noExplotesPorFavor>0){
        sleep(rand()%500);
        pthread_mutex_lock(&mutex);
        printf("Telefono: Pedido recibido\n");
        pthread_mutex_unlock(&mutex);
        noExplotesPorFavor--;
    }
}
void *cocinero(void *arg){
    while(noExplotesPorFavor>0){
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Cocinero: Pedido recibido\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Cocinero: Pedido preparado\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Cocinero: Pedido entregado\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        noExplotesPorFavor--;
    }
}
void *delivery(void *arg){
    while(noExplotesPorFavor>0){
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Delivery: Pedido recibido\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Delivery: Pedido entregado\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        pthread_mutex_lock(&mutex);
        printf("Delivery: Pedido cobrado\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
        noExplotesPorFavor--;
    }
}