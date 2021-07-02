/*
	LOPEZ AGUIRRE GABRIEL
	Problema de la cena de los filòsofos
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/sem.h>
#include <pthread.h>

#define N_FILOSOFOS 5
#define PENSANDO 0
#define COMIENDO 1
#define ESPERANDO 2

int estado[N_FILOSOFOS];
int idFil[N_FILOSOFOS] = {1,2,3,4,5};
sem_t mutex;
sem_t tenedores[5];

void *filosofos(void *id) {
	int x = *(int* ) id;
	
	sem_wait(&mutex);	
	estado[x] = ESPERANDO;
	printf("Filosofo %d tiene hambre\n", x);
	sem_wait(&tenedores[x]);
	sem_wait(&tenedores[(x+1)%5]);
	
	printf("Filosofo %d toma los tenedores %d y %d\n", x, ((x+4)%5), x);
	estado[x] = COMIENDO;
	printf("Filosofo %d esta comiendo\n", x);
	
	sleep(2);
	printf("Filosofo %d termino de comer\n", x);
	estado[x] = PENSANDO;
	sem_post(&tenedores[(x+1)%5]);
	sem_post(&tenedores[x]);
	sem_post(&mutex);	
}

int main() {
	int h;
	pthread_t hilos[N_FILOSOFOS];
	int error;
	int *salida;
	
	if((sem_init(&mutex, 0, 4)) == -1)
		printf("Error en la creacion del semaforo\n");
		
	for(int i=0; i<N_FILOSOFOS; i++) {
		if((sem_init(&tenedores[i], 0, 1)) == -1)
			printf("Error en la creacion del semaforo\n");
	}
	
	for(h=0; h<N_FILOSOFOS; h++) {
		error = pthread_create(&hilos[h], NULL, filosofos, &idFil[h]); 
 		if(error) {
 			printf("error\n");
 			exit(-1);
 		}
	}
	
	for(h=0; h<N_FILOSOFOS; h++) {
		error = pthread_join(hilos[h], (void **) &salida); 
		if(error) {
			printf("error\n");
		} 
	}

}

