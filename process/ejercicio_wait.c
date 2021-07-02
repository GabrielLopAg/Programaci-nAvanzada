#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 5
int I = 0;

void codigo_del_proceso(int id) {
	int i;
	for(i = 0 ; i<10 ; i++) {
		printf("Proceso %d: i = %d, I = %d\n", id, i, I++);
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
		codigo_del_proceso(id[p]);
	} 
	
	// codigo del proceso Padre
	printf("Codigo del proceso PADRE\n");
	for(p = 0; p < NUM_PROCESOS; p++) {
		pid = wait(&salida);
		printf("Proceso %d: con id = %x, terminado\n", pid, salida >> 8);
	}
	
	return 0;
}
