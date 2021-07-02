#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
int i = 10;
sem_t mutex;

void *codigoPrimerHilo() {
	putchar('\n');
	while(i!=10) {
		sem_wait(&mutex);
		printf("hilo 1: %d\n", i++);
		sem_post(&mutex);
	}
}

void *codigoSegundoHilo() {
	while(i) {
		sem_wait(&mutex);
		printf("hilo 2: %d\n", i--);
		sem_post(&mutex);
	}
}

int main() {
	// Iniciamos el semaforo anonimo
	if((sem_init(&mutex, 0, 1)) == -1)
		printf("Error en la creacion del semaforo\n");
	
	pthread_t hilo1, hilo2;
	int error, error2;
	int *salida;
	
	error = pthread_create(&hilo1, NULL, codigoPrimerHilo, NULL); 
	 if(error) {
	 	printf("error\n");
	 	exit(-1);
	 }
	 error2 = pthread_create(&hilo2, NULL, codigoSegundoHilo, NULL); 
	 if(error2) {
	 	printf("error\n");
	 	exit(-1);
	 }
		
	error = pthread_join(hilo1, (void **) &salida);
	if(error) {
		printf("error\n");
	} 
	error2 = pthread_join(hilo2, (void **) &salida); 
	if(error2) {
		printf("error\n");
	} 
	
	sem_destroy(&mutex);
}
