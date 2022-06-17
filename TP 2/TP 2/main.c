#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <signal.h>


#define TAMMSG 8192
#define tiempoJuego 20

int x = 0;

struct Juego{
	
	//Encargado a Cocinero
	mqd_t mensajes;
	//Cocinero a Delivery
	mqd_t mensajes2;
	
	//Semaforo's normales
	sem_t *semtiempoDeJuego;
	sem_t *telefono;
	sem_t *delivery;

	//Semaforos y valores Informativos
	sem_t *pedidosCocinados;
	sem_t *pedidosEntregados;
	sem_t *pedidosCobrados;
	int dineroRecaudado;
	int cierre;
	int opcion;
	
	//pipeline
	int fdTelefono[2];
	///Delivery a Encargado
	int fdFifo;
	//Contador de llamadas perdidas
	int llamadasPerdidas;
};

//Funciones
int Inicializar(struct Juego *juego);
int Borrar(struct Juego *juego);
int menu();

//Procesos
int Telefono(struct Juego *juego);
int Cocinero(struct Juego *juego);
int Delivery(struct Juego *juego);

//Threads
void *HiloCocinero(void *arg);
void *HiloDelivery(void *arg);
void* timer(void *arg);
void *interfazJuego(void *arg);
void *leerUsuario(void * arg);

// Funciones de texto especial
// Hacen que los textos se vean de colores
// diferentes

void textoRojo() {
  printf("\033[0;31m");
}
void textoAmarillo() {
  printf("\033[0;33m");
}
void textoVerde() {
  printf("\033[0;32m");
}
void textoDefecto() {
  printf("\033[0m");
}


// 
int main(int argc, char *argv[])
{
	system("clear");
	if(menu() == 2){
		return 0;
	}
	int pid1, pid2, pid3,error = 0;
	struct Juego *juego = NULL;
	juego = (struct Juego *)(calloc(1, sizeof(struct Juego)));
	Inicializar(juego);
	error = pipe(juego->fdTelefono);
	pid1 = fork();
	if (pid1 == 0)
	{
		//Proceso Telefono
		//fprintf(stdout,"TELEFONO => El proceso Telefono fue creado!\n");
		Telefono(juego);
		return 0;
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		//Proceso Cocinero
		//fprintf(stdout,"COCINERO => El proceso Cocinero fue creado!\n");
		Cocinero(juego);
		return 0;
	}
	pid3 = fork();
	if (pid3 == 0)
	{
		//Proceso Delivery
		//fprintf(stdout,"DELIVERY => El proceso Delivery fue creado!\n");
		Delivery(juego);
		return 0;
	}

	if (pid1 != 0 && pid2 != 0 && pid3 != 0)
	{
		//Proceso Encargado
		//fprintf(stdout,"ENCARGADO => El proceso Encargado fue creado!\n");
		int enviado=0,cantidad,estado = 0,estado2 = 0,entregado = 0,tiempoDeJuego;
		char *remaining;
		char texto[3];

		pthread_t *th;
		th = (pthread_t *)(calloc(1, sizeof(pthread_t)));
		
		time_t t;
		srand((unsigned)time(&t));
		
		pthread_create(&th[0],NULL,timer,(void *)(juego));
		pthread_create(&th[1],NULL,interfazJuego,(void *)(juego));
		pthread_create(&th[2],NULL,leerUsuario,(void *)(juego));
		

		juego->fdFifo=open("./fifoDelivery",O_RDONLY);
		sem_getvalue(juego->semtiempoDeJuego,&tiempoDeJuego);
		while(tiempoDeJuego > 0){
			if(juego->opcion == 1){
				sem_getvalue(juego->telefono,&estado);
				if(estado == 1){
					//Atender telefono
					sem_wait(juego->telefono);
					cantidad = read(juego->fdTelefono[0],texto,3);
				}else if(estado > 1){
					juego->llamadasPerdidas++;
					sem_wait(juego->telefono);
					sem_wait(juego->telefono);
				}
			}else if(juego->opcion == 2){
				//Mandar a cocinar
				if(cantidad > 0){
					//fprintf(stdout,"ENCARGADO => Lei el numero %s\n",texto);
					enviado = mq_send(juego->mensajes,texto,3,0);
					cantidad = 0;
					if(enviado == -1){
						perror("Error en enviar mensaje");
						error = enviado;
					}else{
						//fprintf(stdout,"ENCARGADO => Escribi en la queue\n");
					}
				}
			}else if(juego->opcion == 3){
				//Indiferentemente si lo lee o no, checkea si hay delivery a cobrar
				sem_getvalue(juego->delivery,&estado2);
				if(estado2 >= 1){
					cantidad=read(juego->fdFifo,texto,3);
					// String to long int
					entregado = strtol(texto,&remaining,10);
					//fprintf(stdout,"ENCARGADO => Hay un pedido a cobrar!\n");
					sem_post(juego->pedidosCobrados);
					juego->dineroRecaudado += entregado * 100;
					sem_wait(juego->delivery);
				}
			}
			sem_getvalue(juego->semtiempoDeJuego,&tiempoDeJuego);
		}
		estado = 1;
		while(estado != 0){
			sem_getvalue(juego->telefono,&estado);
			if(estado == 1){
				//Atender telefono
				sem_wait(juego->telefono);
				cantidad = read(juego->fdTelefono[0],texto,3);
			}else if(estado > 1){
				juego->llamadasPerdidas++;
				sem_wait(juego->telefono);
				sem_wait(juego->telefono);
			}
		}

		close(juego->fdFifo);

		enviado = mq_send(juego->mensajes,"-1",3,0);
		enviado = mq_send(juego->mensajes,"-1",3,0);
		enviado = mq_send(juego->mensajes,"-2",3,0);

		juego->cierre = 1;
		//fprintf(stdout,"ENCARGADO => El main process salio del while\n");
		// Esperar todos mis hijos
		while(wait(NULL) != -1 || errno != ECHILD){
			//fprintf(stdout,"ENCARGADO => Un hijo mio termino su ejecucion\n");
		}
		//fprintf(stdout,"ENCARGADO => Todos mis hijos terminaron su ejecucion!\n");

		fprintf(stdout,"ENCARGADO => ======= INFORMACION DE JUEGO ======= \n");

		int pedidosCobrados,pedidosCocinados,pedidosEntregados;

		sem_getvalue(juego->pedidosCobrados,&pedidosCobrados);
		sem_getvalue(juego->pedidosCocinados,&pedidosCocinados);
		sem_getvalue(juego->pedidosEntregados,&pedidosEntregados);

		fprintf(stdout,"ENCARGADO => Llamadas Perdidas: %d\n",juego->llamadasPerdidas);
		fprintf(stdout,"ENCARGADO => Pedidos Cocinados: %d\n",pedidosCocinados);
		fprintf(stdout,"ENCARGADO => Pedidos Entregados: %d\n",pedidosEntregados);
		fprintf(stdout,"ENCARGADO => Pedidos Cobrados: %d\n",pedidosCobrados);
		fprintf(stdout,"ENCARGADO => Dinero Recaudado: $%d\n",juego->dineroRecaudado);

		free(th);
		Borrar(juego);
	}

	return 0;
}

// Esta funcion es la primera que ejecuta encargado para la interfaz
// de usuario
int menu(){
	int exit = 0;
	char ch;
	printf("======================================\n");
	printf("=            1 - Jugar               =\n");
	printf("=            2 - Salir               =\n");
	printf("======================================\n");
	
	do{
		printf("Ingrese la opcion: ");
		fflush(stdin);
		ch = getchar();
		switch(ch){
			case 49:
				system("clear");
				printf("A jugar!!\n");
				return 1;
				break;
			case 50:
				system("clear");
				printf("Adios!\n");
				return 2;
				break;
			default:
				printf("Dato Incorrecto!\n");
				break;
		}
	}while(!exit);
	return 0;
}

// Esta funcion la ejecuta el proceso main
// Se encarga de mostrar en pantalla el estado actual del juego
// utilizando banderas
void *interfazJuego(void *arg){
	struct Juego *juego = (struct Juego *)(arg);

	int pedidosCobrados,pedidosCocinados,pedidosEntregados,tiempoDeJuego,estadoTelefono,estadoDelivery;

	sem_getvalue(juego->semtiempoDeJuego,&tiempoDeJuego);
	while(tiempoDeJuego > 0){
		if(tiempoDeJuego >= 20) textoVerde();
		else if (tiempoDeJuego >= 10 && tiempoDeJuego < 20) textoAmarillo();
		else textoRojo();
		
		printf("Tiempo de Juego restante: %d\n\n",tiempoDeJuego);
		textoDefecto();
		sem_getvalue(juego->telefono,&estadoTelefono);
		if(estadoTelefono % 2 == 1){
			textoAmarillo();
			printf("Telefono sonando...\n");
		}else{
			printf("Telefono inactivo\n");
		}

		sem_getvalue(juego->delivery,&estadoDelivery);
		if(estadoDelivery >= 1){
			textoVerde();
			printf("Hay un delivery para cobrar...\n");
		}else{
			textoDefecto();
			printf("No hay dinero a cobrar\n");
		}

		if(tiempoDeJuego < 5){
			textoRojo();
			printf("\nEstamos por cerrar el local!\n");
		}else{
			textoVerde();
			printf("\nLocal abierto\n\n");
		}
		textoDefecto();

		printf("1 - Contestar telefono\n");
		printf("2 - Dar pedido a cocinero\n");
		printf("3 - Cobrar delivery\n");
		printf("Ingrese la opcion: \n");
		sleep(1);

		sem_getvalue(juego->semtiempoDeJuego,&tiempoDeJuego);
		if(tiempoDeJuego > 0){
			system("clear");
		}
	}
	pthread_exit(NULL);
}

// Esta funcion la ejecuta el proceso main
// Se encarga de tomar los datos ingresados por el usuario
// y lo guarda en un valor en el struct Juego, con el objetivo
// de que el encargado ejecute la accion segun la opcion que eligamos
void *leerUsuario(void *arg){

	struct Juego *juego = (struct Juego *)(arg);
	int opcion,tiempoDeJuego;
	sem_getvalue(juego->semtiempoDeJuego,&tiempoDeJuego);
	do{
		fflush(stdin);
		scanf("%d",&opcion);
		switch(opcion){
			case 1:
				juego->opcion=1;
				break;
			case 2:
				juego->opcion=2;
				break;
			case 3:
				juego->opcion=3;
				break;
			default:
				printf("Dato Incorrecto!\n");
				break;
		}
		opcion = 0;
		sem_getvalue(juego->semtiempoDeJuego,&tiempoDeJuego);
	}while(tiempoDeJuego > 0);

	pthread_exit(NULL);
}

// Esta funcion la ejecuta el proceso main
// Se encarga de restar el tiempo de juego cada un segundo
void *timer(void *arg){
	struct Juego *juego = (struct Juego *)(arg);
	int tiempo;
	sem_getvalue(juego->semtiempoDeJuego,&tiempo);
	while(tiempo > 0){
		sem_wait(juego->semtiempoDeJuego);
		sem_getvalue(juego->semtiempoDeJuego,&tiempo);
		sleep(1);
	}
	//fprintf(stdout,"TIMER => Termine\n");
	pthread_exit(NULL);
}

// Esta funcion la ejecuta el proceso Telefono
// Se encarga de simular llamadas a las cuales
// si contesta prosigue con su ejecucion, en caso contrario
// de que no conteste, envia en el pipeline un mensaje mas
// que indica que no contesto alguna llamada
int Telefono(struct Juego *juego){
	time_t t;
	srand((unsigned)time(&t));
	int estado,error = 0, esperaAleatoria = 1,tiempo ,aleatorio;
	char texto[3];
	sem_getvalue(juego->semtiempoDeJuego,&tiempo);
	while(tiempo > 0){
		usleep(esperaAleatoria);
		esperaAleatoria = ((rand() % 2) + 1) * 50000;
		
		aleatorio = (rand() % 5) + 1;

		snprintf(texto,3,"%d",aleatorio);
		
		write(juego->fdTelefono[1],texto,strlen(texto)+1);
		sem_post(juego->telefono);
		//fprintf(stdout,"TELEFONO => Escribi %s\n",texto);
		
		sleep(3);
		//Implementar semaforo telefono

		sem_getvalue(juego->telefono,&estado);
		if(estado > 0){
			sem_post(juego->telefono);
		}

		sem_getvalue(juego->semtiempoDeJuego,&tiempo);
		if(tiempo <= 0){
			//Enviar senal ipc para cerrar todo
			sem_post(juego->telefono);
			write(juego->fdTelefono[1],"-1",3);
			//fprintf(stdout,"TELEFONO => VAMOS A CERRAR!\n");
			break;
		}
	}
	//fprintf(stdout,"TELEFONO => Termine\n");
	return error;
}


int Cocinero(struct Juego *juego){
	int recibido = 0;
	char mensaje[TAMMSG];

	pthread_t *th2;
	th2 = (pthread_t *)(calloc(2, sizeof(pthread_t)));;

	pthread_create(&th2[0],NULL,HiloCocinero,(void *)(juego));
	pthread_create(&th2[1],NULL,HiloCocinero,(void *)(juego));

	while(1){
		recibido = mq_receive(juego->mensajes,mensaje,TAMMSG,NULL);
		if(recibido == -1){
			perror("Error en recibir mensaje");
		}else{
			if(strcmp(mensaje,"-2") == 0){
				// dejar de cocinar, avisar delivery y cerrar
				//fprintf(stdout,"Proceso Cocinero => Soy el encargado y cerre\n");
				mq_send(juego->mensajes2,"-1",3,0);
				mq_send(juego->mensajes2,"-1",3,0);
				break;
			}else if(strcmp(mensaje,"-1") == 0){
				//salir
				//fprintf(stdout,"Proceso Cocinero => Cerre\n");
				break;
			}else{
				//fprintf(stdout,"COCINERO => Numero recibido es: %s\n",mensaje);
				sleep(2);
				//fprintf(stdout,"COCINERO => Termine de cocinar\n");
				sem_post(juego->pedidosCocinados);
				mq_send(juego->mensajes2,mensaje,3,0);
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		pthread_join(th2[i], NULL);
	}
	//fprintf(stdout,"COCINERO => Termine\n");
	return 0;
}

void *HiloCocinero(void *arg){
	struct Juego *juego = (struct Juego *)(arg);
	int recibido;
	char mensaje[TAMMSG];
	while(1){
		recibido=mq_receive(juego->mensajes,mensaje,TAMMSG,NULL);
		if(recibido == -1){
			perror("Error en recibir mensaje");
		}else{
			if(strcmp(mensaje,"-2") == 0){
				// dejar de cocinar, avisar delivery y cerrar
				//fprintf(stdout,"Hilo Cocinero => Soy el encargado y cerre\n");
				mq_send(juego->mensajes2,"-1",3,0);
				mq_send(juego->mensajes2,"-1",3,0);
				break;
			}
			if(strcmp(mensaje,"-1") == 0){
				//salir
				//fprintf(stdout,"Hilo Cocinero => Cerre\n");
				break;
			}else{
				//fprintf(stdout,"COCINERO => Numero recibido es: %s\n",mensaje);
				sleep(2);
				//fprintf(stdout,"COCINERO => Termine de cocinar\n");
				sem_post(juego->pedidosCocinados);
				mq_send(juego->mensajes2,mensaje,3,0);
			}
		}
	}
	pthread_exit(NULL);
}

int Delivery(struct Juego *juego){
	int recibido = 0;
	char mensaje[TAMMSG];

	pthread_t *th3;
	th3 = (pthread_t *)(calloc(1, sizeof(pthread_t)));;

	juego->fdFifo = open("./fifoDelivery",O_WRONLY);
	pthread_create(&th3[0],NULL,HiloDelivery,(void *)(juego));

	while(1){
		recibido=mq_receive(juego->mensajes2,mensaje,TAMMSG,NULL);
		if(recibido == -1){
			perror("Error en recibir mensaje");
		}else{
			if(strcmp(mensaje,"-1") == 0){
				//salir
				//fprintf(stdout,"Proceso Delivery => Cerre\n");
				break;
			}else{
				//fprintf(stdout,"DELIVERY => Numero recibido es: %s\n",mensaje);
				sleep(2);
				//fprintf(stdout,"DELIVERY => Entrege\n");
				if(juego->fdFifo < 0){
					perror("While opening Fifo");
				}else{
					sem_post(juego->delivery);
					sem_post(juego->pedidosEntregados);
					write(juego->fdFifo,mensaje,strlen(mensaje)); 
				}
			}
		}
	}
	close(juego->fdFifo);
	pthread_join(th3[0], NULL);
	//fprintf(stdout,"DELIVERY => Termine\n");
	return 0;
}

void *HiloDelivery(void *arg){
	struct Juego *juego = (struct Juego *)(arg);
	int recibido;
	char mensaje[TAMMSG];
	juego->fdFifo = open("./fifoDelivery",O_WRONLY);
	while(1){
		recibido=mq_receive(juego->mensajes2,mensaje,TAMMSG,NULL);
		if(recibido == -1){
			perror("Error en recibir mensaje");
		}else{
			if(strcmp(mensaje,"-1") == 0){
				//salir
				//fprintf(stdout,"Hilo Delivery => Cerre\n");
				break;
			}else{
				//fprintf(stdout,"DELIVERY => Numero recibido es: %s\n",mensaje);
				sleep(2);
				//fprintf(stdout,"DELIVERY => Entrege\n");
				if(juego->fdFifo < 0){
					perror("While opening Fifo");
				}else{
					sem_post(juego->delivery);
					sem_post(juego->pedidosEntregados);
					write(juego->fdFifo,mensaje,strlen(mensaje));
					
				}
			}
		}
	}
	close(juego->fdFifo);
	pthread_exit(NULL);
}

int Inicializar(struct Juego *juego)
{
	int error = 0;
	juego->semtiempoDeJuego = sem_open("/semTiempo", O_CREAT, O_RDWR, tiempoJuego);
	juego->llamadasPerdidas=0;
	juego->dineroRecaudado=0;
	juego->cierre = 0;
	if (juego->semtiempoDeJuego == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}
	juego->telefono = sem_open("/semTelefono", O_CREAT, O_RDWR, 0);
	if (juego->telefono == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}
	juego->delivery = sem_open("/semDelivery", O_CREAT, O_RDWR, 0);
	if (juego->delivery == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}

	juego->pedidosCocinados = sem_open("/semCocinados", O_CREAT, O_RDWR, 0);
	if (juego->pedidosCocinados == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}

	juego->pedidosEntregados = sem_open("/semEntregados", O_CREAT, O_RDWR, 0);
	if (juego->pedidosEntregados == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}

	juego->pedidosCobrados = sem_open("/semCobrados", O_CREAT, O_RDWR, 0);
	if (juego->pedidosCobrados == SEM_FAILED)
	{
		perror("sem_open()");
		error = -1;
	}

	juego->mensajes = mq_open("/mensajes", O_RDWR | O_CREAT, 0666, NULL);
	juego->mensajes2 = mq_open("/mensajes2", O_RDWR | O_CREAT, 0666, NULL);


	error= mkfifo("./fifoDelivery",0666);
	if ((error<0) && (errno!=EEXIST)) {
      perror("mkfifo");
	}else{
		error=0;
		//printf("Fifo creada!\n");
	}
	return error;
}

int Borrar(struct Juego *juego)
{
	int error = 0;

	error = sem_close(juego->semtiempoDeJuego);
	error = sem_unlink("/semTiempo");

	error = sem_close(juego->telefono);
	error = sem_unlink("/semTelefono");

	error = sem_close(juego->delivery);
	error = sem_unlink("/semDelivery");

	error = sem_close(juego->pedidosCobrados);
	error = sem_unlink("/semCobrados");

	error = sem_close(juego->pedidosCocinados);
	error = sem_unlink("/semCocinados");

	error = sem_close(juego->pedidosEntregados);
	error = sem_unlink("/semEntregados");

	//Cerrar cola de mensaje
	juego->mensajes = mq_close(juego->mensajes);
	if (juego->mensajes)
	{
		perror("mq_close");
		error = juego->mensajes;
	}
	juego->mensajes = mq_unlink("/mensajes");
	if (juego->mensajes)
	{
		perror("mq_close");
		error = juego->mensajes;
	}


	juego->mensajes2 = mq_close(juego->mensajes2);
	if (juego->mensajes2)
	{
		perror("mq_close");
		error = juego->mensajes2;
	}
	juego->mensajes2 = mq_unlink("/mensajes2");
	if (juego->mensajes2)
	{
		perror("mq_close");
		error = juego->mensajes2;
	}


	error = unlink("./fifoDelivery");
	//fprintf(stdout,"FIFO borrada!\n");

	return error;
}