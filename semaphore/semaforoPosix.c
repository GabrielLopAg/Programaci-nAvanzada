#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

int main() {
	int i = 10;
	int pid;
	sem_t mutex;
	
	// Iniciamos el semaforo anonimo
	if((sem_init(&mutex, 1, 1)) == -1)
		printf("Error en la creacion del semaforo\n");
	
	// creamos el proceso hijo
	if((pid = fork()) == -1) {
		printf("No se creo el proceso hijo: (\n");
		exit(-1);
	} else if(pid == 0) {
		while(i) {
			sem_wait(&mutex);
			printf("PROCESO HIJO: %d\n", i--);
			sem_post(&mutex);		
		}
		sem_destroy(&mutex);
	} else {
		while(i) {
			sem_wait(&mutex);
			printf("PROCESO PADRE: %d\n", i--);
			sem_post(&mutex);
		}
	}
}

