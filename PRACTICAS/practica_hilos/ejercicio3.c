/*
	LOPEZ AGUIRRE GABRIEL
	3. Crear un programa que realice el problema del productor y consumidor (Pueden compartir un arreglo, archivo o una variable) es libre a su criterio.
	
	El programa describe dos procesos, productor y consumidor, ambos comparten un buffer de tamaño finito. La tarea del productor es generar un producto, 
	almacenarlo y comenzar nuevamente; mientras que el consumidor toma (simultáneamente) productos uno a uno. El problema consiste en que el productor no 
	añada más productos que la capacidad del buffer y que el consumidor no intente tomar un producto si el buffer está vacío. 
*/
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

#define TAM_BUFFER 10
int arreglo[TAM_BUFFER];
int contador = 0;

pthread_mutex_t lleno, vacio;

void *productor() {
	for(int i=0; i<TAM_BUFFER; i++) {
		pthread_mutex_lock(&vacio);
		contador++;
		printf("Producto generado. Hay: %d\n",contador);
		pthread_mutex_unlock(&lleno);
		sleep(1);
	}
}

void *consumidor() {
	for(int i=0; i<TAM_BUFFER; i++) {
		pthread_mutex_lock(&lleno);
		if(contador > 0) {
			contador--;
			printf("Producto consumido. Quedan: %d\n", contador);
		} else i--;
		pthread_mutex_unlock(&vacio);
	}
}

int main() {

	pthread_t hilo1, hilo2;
	int error;
	int *salida;

	pthread_mutex_init(&lleno, NULL);
	pthread_mutex_init(&vacio, NULL);
	
	error = pthread_create(&hilo1, NULL, productor, NULL);
	if(error) {
		printf("error al crear el hilo1\n");
	}
	error = pthread_create(&hilo2, NULL, consumidor, NULL);
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
