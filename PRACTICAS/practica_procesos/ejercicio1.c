/*
	LOPEZ AGUIRRE GABRIEL
	1. Crear 10 procesos que realice cada uno la tabla de multiplicar del 1 al 10.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROCESOS 10

void *codigoDelProceso(int id) {
	int temp = id;
	for(int i=1; i<=10; i++) {
		printf("%d x %d = %d\n", id, i, id*i);
	}	
	exit(id);
}

int main() {
	int i;
	int pid;
	int salida;
	int id[NUM_PROCESOS]={1,2,3,4,5,6,7,8,9,10};

	for(i=0; i<NUM_PROCESOS; i++) {
		pid = fork();
		if(pid == -1) {
			printf("El proceso no se pudo crear");
			exit(-1);
		} else if(pid == 0) {
			codigoDelProceso(id[i]);
		}
	}
	
	for(i=0; i<NUM_PROCESOS; i++) {
		pid = wait(&salida);
	}
	
	return 0;
}
