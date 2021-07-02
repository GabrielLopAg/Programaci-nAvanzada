/*

LOPEZ AGUIRRE GABRIEL

Crear un programa que cree 2 hilos. 
El primer hilo cree un archivo
El segundo hilo escriba en el archivo

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *crearArchivo(void *arg) {
	char *nomArchivo = (char *) arg;
	FILE *archivo;
	archivo = fopen(nomArchivo, "w");
	if(archivo!=NULL){
		printf("Archivo creado!\n");
	}
	fclose(archivo);
	pthread_exit(0);
}

void *escribirEnArchivo(void *arg) {
	char *nomArchivo = (char *) arg;
	char text[100];
	FILE *archivo;
	sleep(2);
	archivo = fopen(nomArchivo, "a");
	if(archivo!=NULL){
		printf("Ingrese el enunciado que quiera escribir en el archivo: \n");
		fgets(text, 100, stdin);
		fprintf(archivo, "%s\n", text);
	}
	fclose(archivo);
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	int h;
	pthread_t hilo1,hilo2;
	int error,error2;
	int *salida;
	char *nomArchivo;
	
	if(argc !=3){
		printf("Forma de uso: %s x NombreDelArchivo.txt\n", argv [0]);  
        exit(-1);
    } else {
    	nomArchivo = argv[2];
    
		error = pthread_create(&hilo1, NULL, crearArchivo, (void *) nomArchivo); 
	 	if(error) {
	 		printf("error\n");
	 		exit(-1);
	 	}
	 	error2 = pthread_create(&hilo2, NULL, escribirEnArchivo, (void *) nomArchivo); 
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
	return 0;
}
