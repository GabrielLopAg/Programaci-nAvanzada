#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
	int proceso_id;
	proceso_id = fork();
	if(proceso_id == 0) {
		while(1) {
			printf("Hijo. PID = %d\n", getpid());
			sleep(1);
		}
	}
	sleep(10);
	printf("Padre. Terminacion del proceso %d\n", proceso_id);
	kill(proceso_id, SIGTERM);
	exit(0);
	
}
