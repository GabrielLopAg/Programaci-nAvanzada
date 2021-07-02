// Atributos con hilos

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>


void *codigoDelHilo(void *arg) {
	pthread_attr_t *atributos = arg;
	int detachstate;
	size_t tam_pila;
	int error;
	error = pthread_attr_getdetachstate(atributos, &detachstate);
	
	if(error) {
		printf("Error, pthread_attr_getdetachstate \n");
	} else if(detachstate == PTHREAD_CREATE_DETACHED) {
		printf("Hilo separado\n");
	} else {
		printf("Hilo no separado\n");
	}
	
	error = pthread_attr_getstacksize(atributos, &tam_pila);
	if(error) {
		printf("Error, pthread_attr_getdetachstate \n");  
	} else {
		printf("Hilo. Tamanio de pila: %ld bytes = %ld x %d \n", tam_pila, tam_pila/PTHREAD_STACK_MIN, PTHREAD_STACK_MIN);
	}
	return NULL; // Equivalente a pthread_exit(NULL)
}


int main() {
	pthread_t hilo;
	pthread_attr_t atributos;
	size_t tam_pila;
	int error;
	//*** Inicializamos atributos
	error = pthread_attr_init(&atributos);
	if(error) {
		printf("Error, pthread_attr_init \n");
	}
	
	//*** Activamos el atributo PTHREAD_CREATE_DETACHED
	error = pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);
	if(error) {
		printf("Error, pthread_attr_setdetachstate \n");
	}
	
	/*** Manipulacion del tamaño de la pila ***/
	error = pthread_attr_getstacksize(&atributos, &tam_pila);
	if(error) {
		printf("Error, pthread_attr_getstacksize \n");
	} else {
		printf("El tamanio de la pila por defecto: %ld bytes\n", tam_pila);
		printf("Tamanio minimo de la pila: %d bytes\n", PTHREAD_STACK_MIN);
	}
	
	error = pthread_attr_setstacksize(&atributos, 3*PTHREAD_STACK_MIN);
	if(error) {
		printf("Error, pthread_attr_setstacksize \n");
	} 
	
	/** CREACION DEL HILO CON LOS ATRIBUTOS ANTERIORES **/
	error = pthread_create(&hilo, &atributos, codigoDelHilo, &atributos);
	if(error)
		printf("Error, pthread_create\n");
	printf("FIN DEL HILO PRINCIPAL\n");
	pthread_exit(NULL);
	return 0;
}














