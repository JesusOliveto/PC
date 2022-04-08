/* Se debe realizar el motor de un juego que denominaremos "Delivery". Este juego simulará la actividad de un local de comidas en el cual ingresan los pedidos por teléfono y los empleados tienen que preparar y entregar lo indicado.
En esta primer etapa se deberá trabajar sobre cuatro tipos de hilos:
encargado que da curso a los pedidos de los clientes y, luego de entregado el pedido, guarda el cobro en la caja,
telefono que genera los pedidos de los clientes,
cocinero que prepara la comida,
delivery que lleva los pedidos a los clientes,
El encargado atiende los pedidos que llegan por telefono separados un tiempo aleatorio. El cocinero prepara el pedido, demorando un tiempo diferente según la comida solicitada; solo puede preparar un pedido por vez. El delivery entrega los pedidos a los clientes (de a uno por vez), demorando un tiempo diferente (aleatorio) según la distancia, y al regresar entrega el monto del pedido al encargado.
Se debe sincronizar la interacción entre los hilos utilizando MUTEX según la necesidad (revisar Split Mutex).
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

//structs
typedef struct pedido
{
    int numero;
    int tiempo_preparacion;
    int tiempo_delivery;
} pedido_t;

typedef struct cocinero
{
    int numero;
    int tiempo_preparacion;
    int tiempo_delivery;
} cocinero_t;

typedef struct delivery
{
    int numero;
    int tiempo_preparacion;
    int tiempo_delivery;
} delivery_t;

typedef struct encargado
{
    int numero;
    int tiempo_preparacion;
    int tiempo_delivery;
} encargado_t;

typedef struct telefono
{
    int numero;
    int tiempo_preparacion;
    int tiempo_delivery;
} telefono_t;

//mutex

pthread_mutex_t mutex_cocinero = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_delivery = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_encargado = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_telefono = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond_cocinero = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_delivery = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_encargado = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_telefono = PTHREAD_COND_INITIALIZER;

//contadores
int pedidos_totales = 0;
int pedidos_preparados = 0;
int pedidos_entregados = 0;
int pedidos_cobrados = 0;

//prototipos de funciones

void *cocinero(void *arg);

void *delivery(void *arg);

void *encargado(void *arg);

void *telefono(void *arg);

//MAIN
int main(int argc, char *argv[])
{

//dinamico
    //threads
    pthread_t t_cocinero[cant_cocineros], t_delivery[cant_delivery], t_encargado[cant_encargados], t_telefono[cant_telefonos];
    //structs
    cocinero_t cocinero_[cant_cocineros];
    delivery_t delivery_[cant_delivery];
    encargado_t encargado_[cant_encargados];
    telefono_t telefono_[cant_telefonos];


    //creacion de structs
    for (int i = 0; i < cant_cocineros; i++)
    {
       cocinero_[i] = (cocinero_t) {i+1, rand() % 2 + 2, rand() % 2 + 2};
    }

    for (int i = 0; i < cant_delivery; i++)
    {
        delivery_[i] = (delivery_t){i+1, rand() % 2 + 2, rand() % 2 + 2};
    }

    for (int i = 0; i < cant_encargados; i++)
    {
        encargado_[i] = (encargado_t) {i+1, rand() % 2, rand() % 2};
    }

    for (int i = 0; i < cant_cocineros; i++)
    {
        telefono_[i] = (telefono_t) {i+1, rand() % 2 + 2, rand() % 2 + 2};
    }


    printf("STATS:  \n ");

    printf("COCINEROS:  \n ");
    for (int i = 0; i < cant_cocineros; i++)
    {
        printf("cocinero %d : velocidad: %d \n cooldown: %d \n ", cocinero_[i].numero, cocinero_[i].tiempo_preparacion, cocinero_[i].tiempo_delivery);
    }
    sleep(1);
    printf("DELIVERYS:  \n ");
    for (int i = 0; i < cant_delivery; i++)
    {
        printf("delivery %d : velocidad: %d \n cooldown: %d \n ", delivery_[i].numero, delivery_[i].tiempo_preparacion, delivery_[i].tiempo_delivery);
    }
    sleep(1);
    printf("ENCARGADOS:  \n ");
    for (int i = 0; i < cant_encargados; i++)
    {
        printf("encargado %d : velocidad: %d \n cooldown: %d \n ", encargado_[i].numero, encargado_[i].tiempo_preparacion, encargado_[i].tiempo_delivery);
    }
    
    sleep(5);
    printf("INICIO DE SIMULACION:  \n ");

    
    //creacion de threads
    for (int i = 0; i < cant_cocineros; i++)
    {
        pthread_create(&t_cocinero[i], NULL, cocinero, &cocinero_[i]);
    }

    for (int i = 0; i < cant_delivery; i++)
    {
        pthread_create(&t_delivery[i], NULL, delivery, &delivery_[i]);
    }

    for (int i = 0; i < cant_encargados; i++)
    {
        pthread_create(&t_encargado[i], NULL, encargado, &encargado_[i]);
    }

    for (int i = 0; i < cant_telefonos; i++)
    {
        pthread_create(&t_telefono[i], NULL, telefono, &telefono_[i]);
    }

    //espera de threads

    for (int i = 0; i < cant_cocineros; i++)
    {
        pthread_join(t_cocinero[i], NULL);
    }

    for (int i = 0; i < cant_delivery; i++)
    {
        pthread_join(t_delivery[i], NULL);
    }

    for (int i = 0; i < cant_encargados; i++)
    {
        pthread_join(t_encargado[i], NULL);
    }

    for (int i = 0; i < cant_telefonos; i++)
    {
        pthread_join(t_telefono[i], NULL);
    }

    

    return 0;
}


//FUNCIONES
void *cocinero(void *arg)
{
    cocinero_t *cocinero = (cocinero_t *)arg;
    while (1)
    {   
        sleep(cocinero->tiempo_delivery);
        pthread_mutex_lock(&mutex_cocinero);
        while (pedidos_preparados == pedidos_totales)
        {
            pthread_cond_wait(&cond_cocinero, &mutex_cocinero);
        }
        printf("Cocinero %d preparando pedido %d\n", cocinero->numero, pedidos_preparados + 1);
        pthread_mutex_unlock(&mutex_cocinero);
        sleep(cocinero->tiempo_preparacion);
        pthread_mutex_lock(&mutex_cocinero);       
        printf("Cocinero %d termino de preparar pedido %d\n", cocinero->numero, pedidos_preparados + 1);
        pedidos_preparados++;
        pthread_cond_signal(&cond_delivery);
        if (pedidos_preparados>=limite_pedidos)
        {
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex_cocinero);
        
    }
    pthread_exit(NULL);
}

void *delivery(void *arg)
{
    delivery_t *delivery = (delivery_t *)arg;
    while (1)
    {
        sleep(delivery->tiempo_delivery);
        pthread_mutex_lock(&mutex_delivery);
        while (pedidos_entregados == pedidos_totales)
        {
            pthread_cond_wait(&cond_delivery, &mutex_delivery);
        }
        printf("Delivery %d entregando pedido %d\n", delivery->numero, pedidos_entregados + 1);
        pthread_mutex_unlock(&mutex_delivery);
        sleep(delivery->tiempo_delivery);
        pthread_mutex_lock(&mutex_delivery);
        printf("Delivery %d termino de entregar pedido %d\n", delivery->numero, pedidos_entregados + 1);
        pedidos_entregados++;
        pthread_cond_signal(&cond_encargado);
        if (pedidos_entregados>=limite_pedidos)
        {
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex_delivery);
        
    }
    pthread_exit(NULL);
}

void *encargado(void *arg)
{
    encargado_t *encargado = (encargado_t *)arg;
    while (1)
    {
        sleep(encargado->tiempo_delivery);
        pthread_mutex_lock(&mutex_encargado);
        while (pedidos_cobrados == pedidos_totales)
        {
            pthread_cond_wait(&cond_encargado, &mutex_encargado);
        }
        printf("Encargado %d cobrando pedido %d\n", encargado->numero, pedidos_cobrados + 1);
        pthread_mutex_unlock(&mutex_encargado);
        sleep(encargado->tiempo_preparacion);
        pthread_mutex_lock(&mutex_encargado);
        printf("Encargado %d termino de cobrar pedido %d\n", encargado->numero, pedidos_cobrados + 1);
        pedidos_cobrados++;
        pthread_cond_signal(&cond_telefono);
        if (pedidos_cobrados>=limite_pedidos)
        {
            exit(EXIT_SUCCESS);
        }
        pthread_mutex_unlock(&mutex_encargado);


    }
    pthread_exit(NULL);
}

void *telefono(void *arg)
{
    telefono_t *telefono = (telefono_t *)arg;
    while (1)
    {
        if (telefono->numero ==0)
        {
            telefono->numero = cant_telefonos-1;
        }
        
        pthread_mutex_lock(&mutex_telefono);
        sleep(rand() % 2);
        while (pedidos_totales >= 10)
        {
            pthread_cond_wait(&cond_telefono, &mutex_telefono);
        }
        printf("Telefono %d recibiendo pedido %d\n", telefono->numero, pedidos_totales + 1);
        pthread_mutex_unlock(&mutex_telefono);
        sleep(telefono->tiempo_preparacion);
        pthread_mutex_lock(&mutex_telefono);
        printf("Telefono %d termino de recibir pedido %d\n", telefono->numero, pedidos_totales + 1);
        pedidos_totales++;
        pthread_cond_signal(&cond_cocinero);
        if (pedidos_totales>=limite_pedidos)
        {
            pthread_exit(NULL);
        }

        
        pthread_mutex_unlock(&mutex_telefono);

    }

    pthread_exit(NULL);
}