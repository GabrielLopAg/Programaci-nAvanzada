/*
	LOPEZ AGUIRRE GABRIEL
	1. Crear un programa que genere 2 hilos. El programa debe de recibir por parámetro el nombre del archivo
		- El primer hilo debe crear y abrir el archivo
		- El segundo hilo debe de escribir en el archivo que creo el Hilo 1 (lo que escriba el usuario o que se genere automáticamente)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

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
		int x = fprintf(archivo, "%s\n", text);
		if(x != 0)
			printf("Archivo modificado correctamente!\n");
	}
	fclose(archivo);
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	pthread_t hilo1, hilo2;
	int error, error2;
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
	 	error = pthread_create(&hilo2, NULL, escribirEnArchivo, (void *) nomArchivo); 
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
