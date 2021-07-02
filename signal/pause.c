#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void manejador_SIGUSR1();
void manejador_SIGTERM();

int main() {
	
	signal(SIGTERM, manejador_SIGTERM); // SIGTERM termina el proceso
	signal(SIGUSR1, manejador_SIGUSR1); // SIGUSR1 la accion por defecto es terminar el proceso
	while(1)
		pause(); // el proceso se pone de espera de una señal
}

void manejador_SIGUSR1(int sig) {
	signal(sig, SIG_IGN); // indica que la señal se debe de ignorar
	printf("%d\n", rand());
	signal(sig, manejador_SIGUSR1); 
}

void manejador_SIGTERM(int sig) {
	printf("Terminacion del proceso %d a peticion del usuario\n", getpid());
	exit(-1);
}

// ./ejecutable &
// KILL -SIGUSR1 num_del_proceso
