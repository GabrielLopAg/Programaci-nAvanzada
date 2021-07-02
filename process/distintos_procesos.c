#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 5
int I = 0;

void codigo_del_proceso1(int id) { // multiplicacion
	int i;
	printf("multiplicar\n");
	for(i = 0 ; i<3 ; i++) {
		printf("%d * 3 = %d\n",i, i*3);
		//printf("Proceso %d: i = %d, I = %d\n", id, i, I++);
	}
	exit(id);
}

void codigo_del_proceso2(int id) { // division
	int i;
	printf("division\n");
	for(i = 0 ; i<3 ; i++) {
		printf("%d / 3 = %d\n",i, i/3);
	}
	exit(id);
}

void codigo_del_proceso3(int id) { // sumar
	int i;
	printf("sumar\n");
	for(i = 0 ; i<3 ; i++) {
		printf("%d + 3 = %d\n",i, i+3);
	}
	exit(id);
}

int main() {
	int p;
	int id [NUM_PROCESOS] = {1,2,3,4,5};
	int pid;
	int salida;
	
	for(p = 0; p < NUM_PROCESOS; p++) {
		pid = fork();
	}
	
	if(pid == -1) {
		perror("No se puede crear el proceso");
		exit(-1);
	} else if(pid == 0) {
		// codigo del proceso hijo
		printf("Codigo del proceso HIJO\n");
		codigo_del_proceso1(id[p]);
		codigo_del_proceso2(id[p]);
		codigo_del_proceso3(id[p]);
	} 
	
	// codigo del proceso Padre
	printf("Codigo del proceso PADRE\n");
	for(p = 0; p < NUM_PROCESOS; p++) {
		pid = wait(&salida);
	}
	printf("Proceso %d: con id = %x, terminado\n", pid, salida >> 8);
	
	return 0;
}
