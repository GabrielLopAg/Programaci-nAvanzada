#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_HILOS 2
int I = 0;

void *codigoDelHilo(void *id) {
	 int i;
     for(i =0; i< 10; i++)
        I++;
        
     pthread_exit(id);  
	
}

int main() {
	int h;
	pthread_t hilos[NUM_HILOS];
	int id[NUM_HILOS] = {1,2};
	int error;
	int *salida;
	
	
	for(h=0; h<NUM_HILOS; h++) {
		error = pthread_create(&hilos[h], NULL, codigoDelHilo, &id[h]); // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *() )
 		if(error) {
 			printf("error\n");
 			exit(-1);
 		}
	}
	
	for(h = 0; h<NUM_HILOS; h++) {
		error = pthread_join(hilos[h], (void **) &salida); // pthread_join (pthread_t thread, void **value_ptr);
		if(error) {
			printf("error\n");
		} else {
			printf("Hilo %d terminado\n", *salida);
			printf("Contador: %d\n", I);
		}
	}
	return 0;
}

