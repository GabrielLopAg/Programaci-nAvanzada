// primer programa usando fork
/*
Desde un punto funcional, un proceso en Unix es una entidad creada tras la llamada fork();


El proceso que llama fork() se conoce como proceso padre y el proceso creado es el proceso hijo.
Todos los procesos tienen un unico proceso padre y puede tener varios hijos.
El proceso se identifica mediante PID -Process identification- es un numer que se asocia a cada
 proceso cuando es creado y dura en el tiempo de vida del mismo.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	int proceso_id;
	
	printf("Bienvenido\n");
	proceso_id = fork(); // creamos un proceso
	if(proceso_id == -1)
		printf("No se creo el proceso \n");
	else
		printf("Me acabo de crear como proceso \n");
	return 0;
}

//  gcc Primer_proceso.c -o Primer_proceso
// ./Primer_proceso
