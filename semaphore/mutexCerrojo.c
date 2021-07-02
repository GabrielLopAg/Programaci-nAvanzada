// incrementar y decrementar

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

int indice = 10;
//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;

void *codigoHilo1() {	
	while(indice!=10) {
		pthread_mutex_lock(&mutex);
		printf("hilo 1: %d\n", ++indice);
		pthread_mutex_unlock(&mutex);
	}		
}

void *codigoHilo2() {
	while(indice) {
		pthread_mutex_lock(&mutex);
		printf("hilo 2: %d\n", --indice);
		pthread_mutex_unlock(&mutex);
	}
}

int main() {
	// creamos los hilos	
	pthread_t hilo1, hilo2;
	int error;
	int *salida;
	error = pthread_mutex_init(&mutex, NULL); // inicializacion del semaforo
	
	error = pthread_create(&hilo1, NULL, codigoHilo1, NULL);
	if(error) {
		printf("error al crear el hilo1\n");
	}
	error = pthread_create(&hilo2, NULL, codigoHilo2, NULL);
	if(error) {
		printf("error al crear el hilo2\n");
	}
	
	error = pthread_join(hilo1, (void **) &salida);
	if(error) {
		printf("error\n");
	} 
	error = pthread_join(hilo2, (void **) &salida); 
	if(error) {
		printf("error\n");
	} 
	
	
	return 0;
}
