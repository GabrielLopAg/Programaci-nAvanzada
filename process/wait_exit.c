#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int pid; // identificador del proceso
	int estado;
	if((pid = fork()) == -1){
		perror("No se creo el proceso\n");
	} else if(pid == 0){
		//codigo del hijo
		printf("Soy el hijo\n");
		exit(10);
	} else{
		// codigo del padre
		pid = wait(&estado);
		printf("Soy el padre y recibo: %d\n", pid);
		/*
		Cuando el proceso hijo llame a exit, le pasara al padre el valor 10, 
		que este puede recibir a traves del estado (estado = 10)
		*/
	}

	return 0;
}
