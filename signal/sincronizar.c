#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX 256

int pid_emisor, pid_receptor;

void enviar(int sig) {
	char str[MAX];
	FILE *archivo;
	
	printf("PROCESO EMISOR. MENSAJE: ");
	
	if(fgets(str, MAX, stdin) != NULL) {
		if((archivo = fopen("buzon", "a")) == NULL) {
			printf("ERROR AL ESCRIBIR (ENVIAR)\n");
			kill(pid_receptor, SIGTERM);
		}
		fputs(str, archivo);
		fclose(archivo);
		signal(SIGUSR1, enviar);
		kill(pid_receptor, SIGUSR1);
	} else {
		printf("\n");
		kill(pid_receptor, SIGTERM);
		exit(0);
	}
}

void recibir(int sig){
    char str[MAX];
    FILE *archivo;

     if((archivo = fopen("buzon","r"))==NULL){
          printf("ERROR AL ESCRIBIR (ENVIAR)");
          kill(pid_receptor, SIGTERM);
       }

     fgets (str,MAX, archivo);
     fclose(archivo);

     printf("PROCESO RECEPTOR. MENSAJE: %s\n", str);
     signal(SIGUSR1, recibir);

    kill(pid_emisor, SIGUSR1);    
}

int main() {
	pid_emisor = getpid();
	if((pid_receptor = fork()) == -1) {
		printf("ERROR AL CREAR PROCESO (RECEPTOR)\n");
		exit(-1);
	} else if (pid_receptor == 0) {
		signal(SIGUSR1, recibir);
		while(!0)
			pause();
	} else {
		printf("INICIALIZANDO...\n");
		sleep(2);
		enviar(SIGUSR1);
		while(!0)
			pause();
	}
	exit(0);
}


