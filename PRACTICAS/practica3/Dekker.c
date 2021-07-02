/*
	LOPEZ AGUIRRE GABRIEL
	Algoritmo de Dekker
*/
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define TAM_ARRAY 10

int arreglo[TAM_ARRAY];
bool proceso1_puede_entrar;
bool proceso2_puede_entrar;
int turno;

void hilo1() {

        proceso1_puede_entrar = true;

        while (proceso2_puede_entrar) {
            if (turno == 2) {
                proceso1_puede_entrar = false;
                while (turno == 2) {
                    printf("\nESPERANDO...\n");
                }
                proceso1_puede_entrar = true;
            }
        }

        printf("\n -- SECCION CRITICA DEL PROCESO 2 -- \n");
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
        for(int i=0; i<10; i++) {
			printf("Elemento [%d]: %d\n", i, arreglo[i]);
		}
        printf("   -- HA TERMINADO EL PROCESO 2 --\n");

        turno = 2;
        proceso1_puede_entrar = false;
}

void hilo2() {
	
        proceso2_puede_entrar = true;

        while (proceso1_puede_entrar) {
            if (turno == 1) {
                proceso2_puede_entrar = false;
                while (turno == 1) {
                    printf("\nESPERANDO...\n");
                }
                proceso2_puede_entrar = true;
            }
        }

        printf("\n -- SECCION CRITICA DEL PROCESO 1 -- \n");
        printf("Numeros generados:\n");
		for(int i=0; i<TAM_ARRAY; i++) {
			arreglo[i] = 1 + rand() % (150);
			printf("%d ", arreglo[i]);
		}
        printf("\n   -- HA TERMINADO EL PROCESO 1 --\n");

        turno = 1;
        proceso2_puede_entrar = false;
}

int main() {
	int error;
	int *salida;
	pthread_t p1, p2;
    turno = 1;
    proceso1_puede_entrar = false;
    proceso2_puede_entrar = false;	        

    
    if( pthread_create(&p1, NULL, (void *)hilo1, NULL) ){
        perror("\nError\n"); exit(1);
    }
    if( pthread_create(&p2, NULL, (void *)hilo2, NULL) ){
        perror("\nError\n"); exit(1);
    }


	error = pthread_join(p1, (void **) &salida);
	if(error) {
		printf("error\n");
	} 
	error = pthread_join(p2, (void **) &salida); 
	if(error) {
		printf("error\n");
	} 
    return 0;
}

