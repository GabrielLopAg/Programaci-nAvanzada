/*
	LOPEZ AGUIRRE GABRIEL
	Algoritmo de Peterson
*/
#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int turno;
int flag[2];

void escribirEnArchivo(char const *cadena) {
	printf("Creando archivo txt\n");
	FILE *archivo;
	archivo = fopen("archivo.txt", "a");
	if(archivo) {
		fprintf(archivo, "%s\n", cadena);
	}
	fclose(archivo);
}

void* hilo2(void* arg) {
    flag[0] = 1;
    turno = 1;
    printf("Segundo hilo\n");
    escribirEnArchivo("PRUEBA DOS");
    flag[0] = 0;
    sleep(1);
}

void* hilo1(void* arg) {
    flag[1] = 1;
    turno = 0;
    escribirEnArchivo("PRUEBA UNO");
    printf("Primer hilo\n");
    flag[1] = 0;
    sleep(1);
}

int main() {
  pthread_t t0, t1;
  int error;
  int *salida;

  error = pthread_create(&t0, NULL, hilo1, NULL); 
	 if(error) {
	 	printf("error\n");
	 	exit(-1);
	 }
  error = pthread_create(&t1, NULL, hilo2, NULL); 
	 if(error) {
	 	printf("error\n");
	 	exit(-1);
	 }
  
  error = pthread_join(t0, (void **) &salida);
	if(error) {
		printf("error\n");
	} 
	error = pthread_join(t1, (void **) &salida); 
	if(error) {
		printf("error\n");
	} 

  //while(1);
}


