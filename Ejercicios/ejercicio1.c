/*
	LOPEZ AGUIRRE GABRIEL

a) Explica la tarea que realiza cada uno de los hilos subordinados. 
	Se crean 4 hilos
	Se crean 4 join para esperar a que termine la ejecucion de los 4 hilos hechos anteriormente

	Se hace un arreglo de la estructura, la primera posicion del arreglo contendra la iter=0, ini=al primer valor que doy en la consola o sea 1,
	elem = ((fin-ini)+1)/NUMTHREADS; esta linea me da igual a dos, por lo tanto fin=2
	Se ejecuta la funciòn hilo que se encarga de imprimir el numero de iteraciones que esta almacenada en la estructura
	y de sumar cada posicion del arreglo de la estructura t_interval
	Primero se ejecuta el printf de la linea 63 y despues se ejecuta la funcion del hilo donde nos muestra el numero de iteracion y la suma del inicio y el fin
	Al terminar los 4 hilos se ejecuta por ultimo la linea 69 la cual se hace la suma de los 4 valores que se hallaron en los hilos
¿Donde se almacena el resultado que calcula cada hilo? 
En el vector de enteros suma_parcial[]

b) Cada hilo modifica un elemento del vector suma parcial. ¿Ven estas modificaciones el resto de hilos y la hebra principal? 
Si porque la diferencia entre los hilos y los procesos es que los hilos si se pueden comunicar entre si

c) ¿Que resultado muestra por pantalla el programa?

	Introduce inicio intervalo: 1
	Introduce fin intervalo: 5
	hilo 1 iter = 0, ini = 1, fin = 2
	hilo 1 iter = 1, ini = 3, fin = 4
	hilo 1 iter = 2, ini = 5, fin = 6
	hilo 1 iter = 3, ini = 7, fin = 5
	HIlo i=3, suma = 0
	HIlo i=2, suma = 11
	HIlo i=1, suma = 7
	HIlo i=0, suma = 3
	Suma = 21


*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define NUMTHREADS 4


typedef struct interval{
	int iter;
	int ini;
	int fin;
} t_interval;


int suma_parcial[NUMTHREADS];
int suma = 0;


void *hilo(void *arg) { 
	int i;
	int ini1, fin1, itera;
	t_interval *inter;
	inter = ((t_interval *) (arg));
	itera = inter -> iter;
	ini1 = inter -> ini;
	fin1 = inter -> fin;
	suma_parcial[itera] = 0;
	
	for(i=ini1; i<=fin1; i++){
		suma_parcial[itera] = suma_parcial[itera] + i;
	}
	
	printf("Hilo i=%d, suma = %d\n", itera, suma_parcial[itera]);
	pthread_exit(0);
}


int main() {
	pthread_t thread[NUMTHREADS];
	int ini, fin;
	int i, elem, inicio;
	t_interval param[NUMTHREADS]; // estructura

	printf("Introduce inicio intervalo: ");
	scanf("%d", &ini);
	printf("Introduce fin intervalo: ");
	scanf("%d", &fin);
	elem = ((fin-ini)+1)/NUMTHREADS;
	inicio = ini;

	for (i=0; i<NUMTHREADS; i++) {
		param[i].iter = i;
		param[i].ini = inicio;
		
		if (i == (NUMTHREADS-1)) 
	   		param[i].fin = fin;
		else 
	   		param[i].fin = param[i].ini + elem;
	   		
		pthread_create(&thread[i], NULL, hilo, (void *) &param[i]);

		printf("hilo 1 iter = %d, ini = %d, fin = %d\n", param[i].iter, param[i].ini, param[i].fin);
	   	inicio = param[i].fin+1;
	}
	for (i=0; i<NUMTHREADS; i++) 
		pthread_join(thread[i], NULL);
		
	for (i=0; i<NUMTHREADS; i++) 
		suma = suma + suma_parcial[i];
		
	printf("Suma = %d\n ",suma);
	pthread_exit (0);
}


