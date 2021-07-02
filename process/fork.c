#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int pid; // identificador del proceso hijo

int main() {
	
	if((pid = fork()) == -1){
		perror("No se creo el proceso: \n");
	} else if(pid == 0){
	// codigo que realiza el proceso hijo
		printf("\nSoy el proceso hijo XP PID(PADRE) = %d -- PID(HIJO) = %d\n", getppid(), getpid());
	} else {
	// codigo que realiza el proceso padre
		printf("Soy el proceso Padre PID(PADRE) = %d -- PID(HIJO) = %d\n", getppid(), getpid());
	}
	
	return 0;
}
