/*
LOPEZ AGUIRRE GABRIEL

Hacer una multiplicación de una matriz por un escalar dentro de un hilo.
Un hilo muestre los datos de la matriz antes de la multiplicación
Un hilo imprima el resultado de la matriz
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct matriz{
	int *apt;
	int escalar;
	int orden;
} estructura;

void *resultado(void *arg) {
	estructura *x = ((estructura *) (arg));
	int esc = x -> escalar;
	int ord = x -> orden;
	int *apt = x -> apt;
	int r,c;
	r = c = ord;
	printf("\nResultado de la matriz: \n");
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			printf("%d ", esc*(*apt++));
		}
		printf("\n");
	}
}

void *codigoHilo(void *arg) {
	estructura *x = ((estructura *) (arg));
	int ord = x -> orden;
	int *apt = x -> apt;
	int r,c;
	r = c = ord;
		
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			printf("%d ", *apt++);
		}
		printf("\n");
	}
	
	pthread_t hilo;
	int error;

	error = pthread_create(&hilo, NULL, resultado, x);
	if(error)
        printf("error, pthread_create");
    error = pthread_join(hilo, NULL);
    if(error)
        printf("error, pthread_join");
        
    printf("Primer hilo terminado...\n");
	pthread_exit(0);
}

int main() {
	pthread_t hilo;
    int error;
    int escalar;
    int orden;
    estructura x;
    printf("Ingrese el orden de la matriz: ");
	scanf("%d", &orden);
	printf("Ingrese un escalar: ");
	scanf("%d", &escalar);
	int r,c;
	r = c = orden;
	int matriz[r][c];
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			matriz[i][j] = rand() % 50;			
		}
	}
	x.apt = matriz[0];
    x.orden = orden;
    x.escalar = escalar;
    error = pthread_create(&hilo, NULL, codigoHilo, (void *) &x);
	if(error)
        printf("error, pthread_create");
        
    error = pthread_join(hilo, NULL);
    if(error)
        printf("error, pthread_join");
    printf("Segundo hilo terminado...\n");
}
