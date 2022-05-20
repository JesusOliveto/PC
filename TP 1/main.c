#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "MonitorBuffer.h"
#include "MemoriaCompartida.h"

#define HILOS 9
#define PEDIDOS 10

void *telefono(void *arg);
void *cocinero(void *arg);
void *delivery(void *arg);
void *interfazJuego(void *arg);
void *leerUsuario(void *arg);
int menu();
int crearJuego(void *arg);
int borrarJuego(void *arg);



struct Juego
{
	// Monitores

	// Monitor de comunicacion entre encargado - cocinero
	struct Monitor *m1;
	// Monitor de comunicacion entre cocinero - encargado
	struct Monitor *m2;
	// Memoria compartida para informar al encargado de que puede cobrar
	struct Memoria *mem;

	// Semaforo que indica que el telefono esta sonando
	// Se utiliza en conjunto con la bandera telefono
	sem_t *llamada;
	int telefono;


	// Indica la opcion ingresada por el usuario
	int opcion;

	// Enteros acumulativos que indican valores a mostrar al final del juego
	int llamadasPerdidas;
	int pedidosTomados;
	int pedidosCocinados;
	int pedidosEntregados;
	int pedidosCobrados;
	int dineroTotal;

	// Bandera utilizada para mostrar si hay un pedido a cobrar o no
	int cobro;

	// Variable que indica a cada cocinero/delivery cual es su numero
	int id;

	// Banderas de estado de cocineros/deliverys
	int estadoCocineros[3];
	int estadoDelivery[2];

	// Bandera de estado que indica el cierre de el local
	int cierre;
};


int main()
{
	system("clear");
	if (menu() == 2)
	{
		return 0;
	}

	 int error;
	int dinero = 0;
	pthread_t *th;
	th = (pthread_t *)(calloc(HILOS, sizeof(pthread_t)));

	struct Juego *game = (struct Juego *)(calloc(1, sizeof(struct Juego)));

	error = crearJuego((void *)game);
	if (error)
		perror("crearJuego()");

	//	CREO LOS THREADS
	pthread_create(&th[0], NULL, telefono, (void *)(game));
	//	COCINEROS
	for (int i = 1; i < 4; i++)
	{
		pthread_create(&th[i], NULL, cocinero, (void *)(game));
		usleep(50000);
		game->id++;
	}
	game->id = 0;
	//	DELIVERY
	for (int i = 4; i < 6; i++)
	{
		pthread_create(&th[i], NULL, delivery, (void *)(game));
		usleep(50000);
		game->id++;
	}

	// EMPIEZA EL ENVIO DE DATOS
	time_t t;
	srand((unsigned)time(&t));
	pthread_create(&th[6], NULL, interfazJuego, (void *)(game));
	pthread_create(&th[7], NULL, leerUsuario, (void *)(game));
	int pedidoAleatorio = -1;
	while(game->cierre==0)
	{

		switch (game->opcion)
		{
		case 1:
			error = sem_trywait(game->llamada);
			if (!error)
			{
				game->pedidosTomados++;
				pedidoAleatorio = (rand() % 4);
				game->opcion = 0;
			}
			break;
		case 2:
			if (pedidoAleatorio > -1)
			{
				error = GuardarDato(game->m1, pedidoAleatorio);
			}
			pedidoAleatorio = -1;
			if (error)
				perror("GuardarDato()");
			game->opcion = 0;
			usleep(2000);
			break;
		case 3:
			error = LeerMemoria(game->mem, &dinero);
			if (error)
				perror("LeerMemoria()");
			if (dinero > 0)
			{
				switch (dinero)
				{
				case 0:
					game->dineroTotal += 1;
					break;
				case 1:
					game->dineroTotal += 2;
					break;
				case 2:
					game->dineroTotal += 3;
					break;
				case 3:
					game->dineroTotal += 4;
					break;
				case 4:
					//creo que este no se usa, pero porsi xd
					game->dineroTotal += 5;
					break;
				}
				game->pedidosCobrados++;
				game->cobro = 0;
				dinero = 0;
				game->opcion = 0;
			}
			usleep(2000);
			break;
		case 0:
			break;
		default:
			printf("Opcion invalida\n");
			break;
		}
	}

	// game->cierre = 1;
	// error = GuardarDato(game->m1, -1);
	// error = GuardarDato(game->m1, -1);
	// error = GuardarDato(game->m1, -2);

	// TERMINA EL ENVIO DE DATOS

	// Finaliza el juego

	printf("Cerrando local...\n");
	for (int i = 0; i < HILOS; i++)
	{
		pthread_join(th[i], NULL);
	}

	printf("Pedidos tomados: %d\n", game->pedidosTomados);
	printf("Pedidos cocinados: %d\n", game->pedidosCocinados);
	printf("Pedidos entregados: %d\n", game->pedidosEntregados);
	printf("Pedidos cobrados: %d\n", game->pedidosCobrados);
	printf("Llamadas perdidas: %d\n", game->llamadasPerdidas);
	printf("Dinero total: %d\n", game->dineroTotal);
	error = borrarJuego((void *)game);
	if (error)
		perror("borrarJuego()");

	free(th);
}


void *telefono(void *arg)
{
	struct Juego *game = (struct Juego *)(arg);
	int estadoLlamada;
	time_t t2;
	srand((unsigned)time(&t2));
	int dormir = 1;
	while(game->cierre==0)
	{
		sleep(dormir);
		sem_post(game->llamada);
		sleep(3);
		sem_getvalue(game->llamada, &estadoLlamada);
		if (estadoLlamada > 0)
		{
			game->llamadasPerdidas++;
			sem_wait(game->llamada);
		}
		dormir = (rand() % 2) + 1;
	}
	pthread_exit(NULL);
}

void *cocinero(void *arg)
{
	struct Juego *game = (struct Juego *)(arg);
	int error, x;
	int id = game->id;
	int dormir = 2;

	while (1)
	{
		error = LeerDato(game->m1, &x);

		if (error)
			perror("LeerDato()");
		if (x == -1)
		{
			break;
		}
		else if (x == -2)
		{
			error = GuardarDato(game->m2, -1);
			if (error)
				perror("GuardarDato()");
			error = GuardarDato(game->m2, -1);
			if (error)
				perror("GuardarDato()");
			break;
		}
		else if (x > 0)
		{
			game->estadoCocineros[id] = 1;
			sleep(dormir);
			error = GuardarDato(game->m2, x);
			if (error)
				perror("GuardarDato()");
			game->pedidosCocinados++;
			game->estadoCocineros[id] = 0;
		}
	}
	pthread_exit(NULL);
}


void *delivery(void *arg)
{
	struct Juego *game = (struct Juego *)(arg);
	int error, x;
	int id = game->id;
	int dormir = 1;
	while (1)
	{
		error = LeerDato(game->m2, &x);
		if (error)
			perror("LeerDato()");
		if (x == -1)
		{
			break;
		}
		else if (x > 0)
		{
			game->estadoDelivery[id] = 1;
			sleep(dormir);
			error = GuardarMemoria(game->mem, x);
			if (error)
				perror("GuardarMemoria()");
			game->cobro = 1;
			game->pedidosEntregados++;
			game->estadoDelivery[id] = 0;
		}
	}
	pthread_exit(NULL);
}

int menu()
{
	int exit = 0;
	char ch;
	printf("1 - Jugar\n");
	printf("2 - Salir\n");

	do
	{
		printf("Ingrese la opcion: ");
		fflush(stdin);
		ch = getchar();
		switch (ch)
		{
		case 49:
			system("clear");
			printf("INICIANDO...\n");
			return 1;
			break;
		case 50:
			return 2;
			break;
		default:
			printf("Dato Incorrecto!\n");
			break;
		}
	} while (!exit);
	return 0;
}

void *interfazJuego(void *arg)
{
	struct Juego *game = (struct Juego *)(arg);


	while(game->cierre==0)
	{
		// fflush(stdin);

		sem_getvalue(game->llamada, &game->telefono);
		if (game->telefono == 1)
		{
			printf("Llamada entrante\n");
		}
		else
		{
			printf("Telefono apagado\n");
		}

		if (game->cobro == 1)
		{
			printf("Delivery en puerta\n");
		}
		else
		{
			printf("nada que cobrar\n");
		}

		for (int i = 0; i < 3; i++)
		{
			printf("Estado del Cocinero %d: ", i + 1);
			if (game->estadoCocineros[i] == 0)
			{
				printf("Desocupado\n");
			}
			else
			{
				printf("Cocinando\n");
			}
		}

		for (int i = 0; i < 2; i++)
		{
			printf("Estado del Delivery %d: ", i + 1);
			if (game->estadoDelivery[i] == 0)
			{
				printf("Desocupado\n");
			}
			else
			{
				printf("Realizando Entrega\n");
			}
		}

		if (game->cierre == 1)
		{
			printf("\nJuego terminado!!\n");
		}
		else
		{
			printf("\nDelivery activo\n\n");
		}

		printf("1 - Contestar telefono\n");
		printf("2 - Activar cocinero\n");
		printf("3 - Cobrar pedido/hacer que termine de entregar (known issue)\n");
		printf("4 - Actualizar delivery en puerta (known issue)\n");
		printf("5 - Cerrar el local\n");
		printf("Ingrese la opcion: \n");
		sleep(1);

		if (game->cierre==0)
		{
			system("clear");
		}
	}
	pthread_exit(NULL);
}



void *leerUsuario(void *arg)
{
	int error;
	struct Juego *game = (struct Juego *)(arg);
	int opcion;
	do
	{
		fflush(stdin);
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1:
			game->opcion = 1;
			break;
		case 2:
			game->opcion = 2;
			break;
		case 3:
			game->opcion = 3;
			break;
		case 4:
			printf("Pantalla actualizada\n");
			break;
		case 5:
			game->cierre = 1;
			error = GuardarDato(game->m1, -1);
			error = GuardarDato(game->m1, -1);
			error = GuardarDato(game->m1, -2);
			break;
		}
		opcion = 0;
	} while (game->cierre == 0);
	pthread_exit(NULL);
}


int crearJuego(void *arg)
{
	struct Juego *game = (struct Juego *)(arg);
	int error = 0;
	game->m1 = NULL;
	game->m2 = NULL;
	game->opcion = 0;
	game->id = 0;
	game->dineroTotal = 0;
	game->telefono = 0;
	game->cierre = 0;
	game->cobro = 0;
	game->pedidosTomados = 0;
	game->llamadasPerdidas = 0;
	game->pedidosCocinados = 0;
	game->pedidosEntregados = 0;
	game->pedidosCobrados = 0;

	for (int i = 0; i < 3; i++)
	{
		game->estadoCocineros[i] = 0;
		if (i != 2)
		{
			game->estadoDelivery[i] = 0;
		}
	}

	game->llamada = sem_open("/semBinario2", O_CREAT, O_RDWR, 0);
	if (game->llamada == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}
	if (!error)
	{
		// printf("Semaforo creado!\n");
	}
	// CREAR MONITORES
	game->m1 = CrearMonitor();
	if (game->m1 != NULL)
	{
		// printf("Monitor creado!\n");
	}
	else
	{
		perror("CrearMonitor()");
		error = -1;
	}

	game->m2 = CrearMonitor();

	if (game->m2 != NULL)
	{
		// printf("Monitor creado!\n\n");
	}
	else
	{
		perror("CrearMonitor()");
		error = -1;
	}
	// TERMINO CREAR MONITORES
	// CREO MEMORIA COMPARTIDA
	game->mem = CrearMemoria();
	if (game->mem != NULL)
	{
		// printf("Memoria creada!\n");
	}
	else
	{
		perror("CrearMemoria()");
		error = -1;
	}
	// TERMINO CREAR MEMORIA COMPARTIDA
	return error;
}

int borrarJuego(void *arg)
{
	struct Juego *game = (struct Juego *)(arg);
	int error = 0;
	if (!error)
	{
		error = sem_close(game->llamada);
		if (error)
		{
			perror("sem_close()");
		}
	}

	if (!error)
	{
		error = sem_unlink("/semBinario2");
		if (error)
		{
			perror("sem_unlink()");
		}
	}

	BorrarMemoria(game->mem);
	BorrarMonitor(game->m1);
	BorrarMonitor(game->m2);
	free(game);
	return error;
}
