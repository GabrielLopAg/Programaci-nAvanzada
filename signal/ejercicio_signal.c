/*
	LOPEZ AGUIRRE GABRIEL
	Crear un programa que utilice las siguientes señales SIGTERM y SIGUSR1
	- El programa debe incrementar una variable entera de forma infinita
	- Cada vez que reciba una señal SIGUSR1 deberá de mostrar el valor actual de la variable que va incrementando el for Cuando reciba SIGTERM
	- Concluye el programa pero que me muestre cuantas veces consulte el resultado (use  SIGUSR1)
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void manejador_SIGUSR1();
void manejador_SIGTERM();
long i=0;
int j=0;

int main() {

	signal(SIGTERM, manejador_SIGTERM); 
	signal(SIGUSR1, manejador_SIGUSR1); 
	
	while(1) {
		i++;
	}
}

void manejador_SIGUSR1(int sig) {
	signal(sig, SIG_IGN); 
		
	printf("%ld\n", i);
	j++;
	signal(sig, manejador_SIGUSR1); 
}

void manejador_SIGTERM(int sig) {
	printf("\nTerminacion del proceso %d\nConsulto el resultado [%d] veces\n", getpid(), j);
	exit(-1);
}

