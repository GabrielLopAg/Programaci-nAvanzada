/*
	LOPEZ AGUIRRE GABRIEL
	3. Crear 3 procesos que realicen lo siguiente:
		Proceso 1. Que cree una carpeta
		Proceso 2. Que genere un documento dentro de la carpeta creada
		Proceso 3. Que escriba en el documento creado por el Proceso 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void proceso1() {
	int check;
	check = mkdir("CARPETA", 0700);
	if(!check)
        printf("Directorio creado\n");
}

void proceso2(int id) {
	printf("Creando archivo txt\n");
	FILE *archivo;
	archivo = fopen("CARPETA/archivo.txt", "w");
	if(archivo) {
		fprintf(archivo, "Archivo creado!\n");
	}
	fclose(archivo);
}

void proceso3(int id) {
	printf("Escribiendo en el archivo txt\n");
	FILE *archivo;
	archivo = fopen("CARPETA/archivo.txt", "a");
	if(archivo) {
		fprintf(archivo, "Proceso 3!\n");
	}
	fclose(archivo);
}
	
int main() {
	int pid1, pid2, pid3;
	int sal1, sal2, sal3;
	int id[]={1, 2, 3};
	
	if((pid1=fork()) == -1) { // primer proceso
		printf("El proceso no se pudo crear\n");
	} else if(pid1 == 0) { 
		printf("\nPrimer proceso hijo\n");
		proceso1();
		
		if((pid2=fork()) == -1) { // segundo proceso
			printf("El proceso no se pudo crear\n");
		} else if(pid2 == 0) {
			printf("\nSegundo proceso hijo\n");
			proceso2(id[1]);
			
			if((pid3=fork()) == -1) { // tercer proceso
				printf("El proceso no se pudo crear\n");
			} else if(pid3 == 0) {
				printf("\nTercer proceso hijo\n");
				proceso3(id[2]);
			} else {
				pid3 = wait(&sal3);
				printf("\nSoy el proceso Padre %d\n", getppid());
			}
		} else {
			pid2 = wait(&sal2);
		}
		
	} else {
		pid1 = wait(&sal1);
	}
	
	return 0;
}
