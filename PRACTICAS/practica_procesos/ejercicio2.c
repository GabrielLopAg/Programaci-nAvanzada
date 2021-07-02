/*
	LOPEZ AGUIRRE GABRIEL
	2. Crear 3 procesos que realicen lo siguiente:
		Proceso 1. Ejecute la instrucción ls (listSort "lista directorios ") (Que muestre los directorios)
		Proceso 2. Ejecute la instrucción cd Documentos (ingresa a la carpeta Documentos)
		Proceso 3. Ejecute la sentencia pwd (imprime el directorio de trabajo actual)
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void proceso3(int id) {
	printf("Proceso: %d\n", getpid());
	char *args[] = {"ls", "-l", "/home/gabriel", NULL};
	execv("/bin/ls", args);
	printf("Se produce un error al ejecutar execv\n");
	
}

void proceso2(int id) {
	char s[100];
	chdir("/home/gabriel/Documents");
	printf("Proceso: %d\n%s\n", getpid(), getcwd(s, 100));
}

void proceso1(int id) {
	char s[100];
	printf("Proceso: %d\n%s\n", getpid(), getcwd(s, 100));
}


int main() {
	int pid1, pid2, pid3;
	int sal1, sal2, sal3;
	int id[]={1,2,3};
	
	if((pid1=fork()) == -1) { // primer proceso
		printf("El proceso no se pudo crear\n");
	} else if(pid1 == 0) { 
		printf("\nPrimer proceso hijo\n");
		proceso1(id[0]);
		
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
				printf("Soy el proceso Padre %d\n", getppid());
			}
		} else {
			pid2 = wait(&sal2);
		}
		
	} else {
		pid1 = wait(&sal1);
	}
	
	return 0;
}
