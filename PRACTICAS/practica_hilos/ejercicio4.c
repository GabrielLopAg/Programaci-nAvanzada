/*
	LOPEZ AGUIRRE GABRIEL
	4. Crear un programa que genere 5 hilos. Cada hilo se debe estar ejecutando infinitamente con su contador propio (no debe de mostrarse por pantalla
	 	la ejecución de los hilos), debe existir una variable contador_global que es la variable que va almacenar el contador de cada hilo que vaya finalizando
	 	
		Al iniciar el programa :
		- Muestre el Id de cada hilo generado ( Ej. Hilo n tiene su identificador: 34234)
		- Solicitarle al usuario por mensaje que hilo desea matar y el usuario debe de escribir solo el Id del hilo a matar. 
			Cuando muera el hilo muestre (Hilo n su contador fue : 432).
		Al usuario se le seguirá mostrando el mensaje hasta que ya no existan hilos en ejecución.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 5
int contador_global = 0;

typedef struct _hilo {
	int numHilo;
	long iteraciones;
} hilo;

void  fin_de_calculo(void *arg){
    hilo *x = (hilo*) arg;
    printf("Hilo %d su contador fue : %ld\n\n", x->numHilo, x->iteraciones);
}

void *codigoDelHilo(void *id){
    int i=0;
    int error;
    int estado_ant, tipo_ant;
    int resultado = 0;
    printf("Hilo %d \t%ld\n", *(int *) id, pthread_self());
    hilo x;
    x.numHilo = *(int *) id;

    error = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &estado_ant);
    if(error)
    	printf("error, pthread_setcancelstate");

    pthread_cleanup_push(fin_de_calculo, &x);  //macro
    
    error = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &tipo_ant);
    if(error)
        printf("error, pthread_setcanceltype");
    
    error = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &estado_ant);
    if(error)
        printf("error, pthread_setcancelstate");

    for(;;) {
        pthread_testcancel(); 
        i++; contador_global++;
        x.iteraciones = resultado = i;
    }
    pthread_cleanup_pop(1); //macro-fin
}

int main() {
	int h;
	pthread_t hilos[NUM_THREADS];
	int num[NUM_THREADS] = {1,2,3,4,5};
	int error;
	int *salida;
	pthread_t tid;
	
	for(h=0; h<NUM_THREADS; h++) {
		error = pthread_create(&hilos[h], NULL, codigoDelHilo, (void *)&num[h]); 
 		if(error) {
 			printf("error\n");
 			exit(-1);
 		}
	}
	

	for(h=0; h<NUM_THREADS; h++) {
		sleep(1);
		printf("Escriba el id del hilo: ");
		scanf("%ld", &tid);
    	error = pthread_cancel(tid);
    	if(error)
        	printf("error, pthread_cancel");
	}
	
        
	for(h = 0; h<NUM_THREADS; h++) {
		error = pthread_join(hilos[h], (void **) &salida); 
		if(error) {
			printf("error\n");
		} 
	}
}
