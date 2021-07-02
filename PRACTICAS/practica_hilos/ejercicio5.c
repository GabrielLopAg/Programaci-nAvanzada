/*
	LOPEZ AGUIRRE GABRIEL
	5. Crear un programa que genere 3 hilos y una variable compartida de tipo int arreglo[] de tamaño 10
		1. Hilo genere números aleatorios del 1 al 100 y los almacene en el arreglo (variable compartida)
		2. Hilo ordene los números aleatorios que se almacenaron en el arreglo (variable compartida)
		3. Hilo imprima los números aleatorios ya ordenados leyendo del arreglo (variable compartida)
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define TAM_ARRAY 10
int arreglo[TAM_ARRAY];

static pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER; // mutex: exclusion mutua
static pthread_cond_t condition_var1 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t condition_var2 = PTHREAD_COND_INITIALIZER;


void *codigoPrimerHilo() {
	pthread_mutex_lock(&count_mutex);
	printf("Numeros generados:\n");
	for(int i=0; i<TAM_ARRAY; i++) {
		arreglo[i] = 1 + rand() % (100);
		printf("%d ", arreglo[i]);
	}
	pthread_cond_signal(&condition_var1);
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(0);
}

void *codigoSegundoHilo() {
	
	pthread_mutex_lock(&count_mutex);
	pthread_cond_wait(&condition_var1, &count_mutex);
	sleep(2);
	int i, j, aux;
	for(i=1; i<10; i++) {
		j = i;
		aux = arreglo[i];
		while(j>0 && aux<arreglo[j-1]) {
			arreglo[j] = arreglo[j-1];
			j=j-1;
		}
		arreglo[j] = aux;
	}
	printf("\n\nNumeros ordenados!\n");
	pthread_cond_signal(&condition_var2);
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(0);
}

void *codigoTercerHilo() {
	
	pthread_mutex_lock(&count_mutex);
	pthread_cond_wait(&condition_var2, &count_mutex);
	sleep(2);
	printf("\nLos elementos ordenados del arreglo son: \n");
	for(int i=0; i<10; i++) {
		printf("Elemento [%d]: %d\n", i, arreglo[i]);
	}
	
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(0);
}

int main() {
	pthread_t hilo1,hilo2,hilo3;
	int error, error2, error3;
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

}


