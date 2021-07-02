// Uso de getpid y getppid
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	if(fork() == 0) {
		// codigo del proceso hijo
		printf("Proceso hijo. PID = %d, PPID = %d, ID de grupo = %d\n", getpid(), getppid(), getpgrp());
		sleep(10);
		// Como el proceso padre ya ha terminado, el proceso hijo es adoptado por el proceso con PID = 1
		printf("Hjo. PID = %d, PPID = %d, ID de grupo = %d\n", getpid(), getppid(), getpgrp());
		// El proceso hijo se va a convertir en el lider de un nuevo grupo de procesos
		setpgrp();
		printf("Hijo. PID = %d, PPID = %d, ID de grupo = %d\n", getpid(), getppid(), getpgrp());
		exit(0);
	}
	// codigo del padre
	printf("Proceso padre. PID = %d, PPID = %d, ID de grupo = %d\n", getpid(), getppid(), getpgrp());
	sleep(5);
	printf("PROCESO PADRE TERMINADO\n");
	exit(0);

	return 0;
}

