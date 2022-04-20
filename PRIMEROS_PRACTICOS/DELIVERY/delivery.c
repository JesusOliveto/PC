/*Se debe realizar el motor de un juego que denominaremos "Delivery". Este juego simulará la actividad de un local de comidas en el cual ingresan los pedidos por teléfono y los empleados tienen que preparar y entregar lo indicado.

En esta primer etapa se deberá trabajar sobre cuatro tipos de hilos:
encargado que da curso a los pedidos de los clientes y, luego de entregado el pedido, guarda el cobro en la caja,
telefono que genera los pedidos de los clientes,
cocinero que prepara la comida,
delivery que lleva los pedidos a los clientes,

El encargado atiende los pedidos que llegan por telefono separados un tiempo aleatorio. El cocinero prepara el pedido, demorando un tiempo diferente según la comida solicitada; solo puede preparar un pedido por vez. El delivery entrega los pedidos a los clientes (de a uno por vez), demorando un tiempo diferente (aleatorio) según la distancia, y al regresar entrega el monto del pedido al encargado.

Esta versión tendrá 3 cocineros y 2 delivery.

Se debe sincronizar la interacción entre los hilos utilizando SEMÁFOROS según la necesidad (revisar Split Binary Semaphore).
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

//cantidad de hilos
int cant_cocineros = 3;
int cant_delivery = 2;
int cant_telefonos = 1;
int cant_encargados = 1;

const int limite_pedidos = 10;


void *cocinero(void *arg);

void *delivery(void *arg);

void *encargado(void *arg);

void *telefono(void *arg);

//semaforos
sem_t sem_cocineros;
sem_t sem_delivery;
sem_t sem_encargados;
sem_t sem_telefonos;

//semaforos para proteger recurso compartido
sem_t sem_bandeja;

//recurso compartido
int bandeja[limite_pedidos];

int contador_pedidos = 0;
int contador_pedidos_cocineros = 0;
int contador_pedidos_delivery = 0;

int main() {
    pthread_t cocineros;
    pthread_t delivery;
    pthread_t encargados;
    pthread_t telefonos;

    int i, j;

    srand(time(NULL));

    sem_init(&sem_cocineros, 0, 0); // 0 inicialmente, cuenta cuantos cocineros pueden usar el recurso
    sem_init(&sem_delivery, 0, 0); // 0 inicialmente, cuenta cuantos delivery pueden usar el recurso
    sem_init(&sem_encargados, 0, 0); // 0 inicialmente, cuenta cuantos encargados pueden usar el recurso
    sem_init(&sem_telefonos, 0, 0); // 0 inicialmente, cuenta cuantos telefonos pueden usar el recurso

    sem_init(&sem_bandeja, 0, 1); // 1 inicialmente, protege el recurso compartido

    for (i = 0; i < cant_cocineros; i++) {
        // creamos hilos cocineros
        pthread_create(&cocineros, NULL, cocinero, (void *) i);
    }

    for (i = 0; i < cant_delivery; i++) {
        // creamos hilos delivery
        pthread_create(&delivery, NULL, delivery, (void *) i);
    }

    for (i = 0; i < cant_encargados; i++) {
        // creamos hilos encargados
        pthread_create(&encargados, NULL, encargado, (void *) i);
    }

    for (i = 0; i < cant_telefonos; i++) {
        // creamos hilos telefonos
        pthread_create(&telefonos, NULL, telefono, (void *) i);
    }

    //pthread_exit(NULL);
}

void *cocinero(void *arg) {
    int id = (int) arg;

    sem_wait(&sem_cocineros); // resta 1 al semaforo para proteger el recurso compartido
    sem_wait(&sem_bandeja); // espera a que haya pedidos

    contador_pedidos_cocineros++;

    printf("El cocinero %d esta preparando la comida. El pedido es %d.\n", id, bandeja[contador_pedidos_cocineros]);

    int tiempo_preparacion = rand() % 10;
    sleep(tiempo_preparacion);
    printf("El cocinero %d termino de preparar la comida. El pedido fue %d.\n", id, bandeja[contador_pedidos_cocineros]);

    sem_post(&sem_cocineros); // agrega 1 al semaforo para indicar que otro cocinero puede usar el recurso compartido
    sem_post(&sem_delivery); // avisa que un delivery esta listo para ir a entregar un pedido
    pthread_exit(NULL);
}

void *delivery(void *arg) {
    int id = (int) arg;

    sem_wait(&sem_delivery); // resta 1 al semaforo para proteger el recurso compartido

    contador_pedidos_delivery++;

    printf("El delivery %d esta listo para llevar el pedido %d.\n", id, bandeja[contador_pedidos_delivery]);

    int tiempo_entrega = rand() % 10;
    sleep(tiempo_entrega);
    printf("El delivery %d termino de llevar el pedido %d.\n", id, bandeja[contador_pedidos_delivery]);

    sem_post(&sem_encargados); // avisa que un encargado puede recibir un pedido
    pthread_exit(NULL);
}

void *encargado(void *arg) {
    int id = (int) arg;

    sem_wait(&sem_encargados); // resta 1 al semaforo para proteger el recurso compartido

    printf("El encargado %d esta cobrando el pedido %d.\n", id, bandeja[contador_pedidos_delivery]);

    int tiempo_cobro = rand() % 10;
    sleep(tiempo_cobro);
    printf("El encargado %d termino de cobrar el pedido %d.\n", id, bandeja[contador_pedidos_delivery]);

    sem_post(&sem_bandeja); // avisa que un cocinero puede preparar un nuevo pedido
    pthread_exit(NULL);
}

void *telefono(void *arg) {
    int id = (int) arg;

    sem_wait(&sem_telefonos); // resta 1 al semaforo para proteger el recurso compartido

    printf("El telefono %d recibio un pedido.\n", id);

    int tiempo_cobro = rand() % 10;
    sleep(tiempo_cobro);

    if (contador_pedidos < limite_pedidos) {
        contador_pedidos++;

        bandeja[contador_pedidos] = contador_pedidos;
        printf("El telefono %d asigno el pedido %d.\n", id, bandeja[contador_pedidos]);
        sem_post(&sem_cocineros); // avisa que un cocinero puede preparar un nuevo pedido
    } else {
        printf("No puede atenderse más pedidos.\n");
    }

    sem_post(&sem_telefonos); // avisa que un telefono puede recibir un nuevo pedido
    pthread_exit(NULL);
}