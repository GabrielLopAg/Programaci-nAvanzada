/*
	LOPEZ AGUIRRE GABRIEL
	Del código realizado en clase.
	Crear un menú el que me permita elegir como deseo que me presente el contenido el receptor

	a) Que muestre todo el contenido del buzón
	b) Que muestre solo el ultimo contenido escrito en el buzón
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define MAX 255

int pid_emisor, pid_receptorTodo, pid_receptorUltimo, pid_menu;

void enviar(int sig) {
	char str[MAX];
	FILE *archivo;
	
	printf("PROCESO EMISOR. MENSAJE: ");
	
	if(fgets(str, MAX, stdin) != NULL) {
		if((archivo = fopen("buzon", "a")) == NULL) {
			printf("ERROR AL ESCRIBIR (ENVIAR)\n");
			kill(pid_receptorUltimo, SIGTERM);
			kill(pid_receptorTodo, SIGTERM);
			kill(pid_menu, SIGTERM);
		}
		fputs(str, archivo);
		fclose(archivo);
		signal(SIGUSR1, enviar);
		kill(pid_menu, SIGUSR1); 
	} else {
		printf("\n");
		kill(pid_receptorUltimo, SIGTERM);
		kill(pid_receptorTodo, SIGTERM);
		kill(pid_menu, SIGTERM);
		exit(0);
	}
}

void recibirUltimo(int sig){
    char str[MAX];
    FILE *archivo;

    if((archivo = fopen("buzon", "r"))==NULL){
         printf("ERROR AL ESCRIBIR (ENVIAR)");
         kill(pid_receptorUltimo, SIGTERM);
    }
	while(!feof(archivo)) {
		fscanf(archivo, "%s", str);
	}
    fclose(archivo);

    printf("PROCESO RECEPTOR. MENSAJE: %s\n", str);
    signal(SIGUSR1, recibirUltimo); 

    kill(pid_menu, SIGUSR1); 
}

void recibirTodo(int sig){
    char str[MAX], ch;
    FILE *archivo;

    if((archivo = fopen("buzon","r"))==NULL){
         printf("ERROR AL ESCRIBIR (ENVIAR)");
         kill(pid_receptorTodo, SIGTERM);
    }
	while((fgets(str, MAX, archivo)) != NULL) {
		//fputs(str, stdout);
		printf("PROCESO RECEPTOR. MENSAJE: %s", str);
	}

    fclose(archivo);
    signal(SIGUSR1, recibirTodo); 

    kill(pid_menu, SIGUSR1);  
}

void menu(int sig) {
	int resp;
	sleep(1);
	printf("\n1. Enviar mensaje\n");
	printf("2. Mostrar el contenido del buzon\n");
	printf("3. Mostrar ultimo mensaje\n");
	printf("4. Terminar programa\n");
	scanf("%d", &resp);
		
	switch(resp) {
		case 1:
			kill(pid_emisor, SIGUSR1);
			break;
		case 2:
			kill(pid_receptorTodo, SIGUSR1);
			break;
		case 3:
			kill(pid_receptorUltimo, SIGUSR1);
			break;
		case 4:
			kill(pid_receptorUltimo, SIGTERM);
			kill(pid_receptorTodo, SIGTERM);
			kill(pid_menu, SIGTERM);
			exit(0);
		default:
			printf("Ingrese otra opcion...");		
	}
	signal(SIGUSR1, menu); 
	
}

int main() {
	pid_menu = getpid();
	if((pid_emisor = fork()) == -1) {
		printf("ERROR AL CREAR PROCESO (EMISOR)\n");
		exit(-1);
	} else if (pid_emisor == 0) {
		signal(SIGUSR1, enviar);
		while(!0)
			pause();
	} 
	if((pid_receptorUltimo = fork()) == -1) {
		printf("ERROR AL CREAR PROCESO (RECEPTOR1)\n");
		exit(-1);
	} else if (pid_receptorUltimo == 0) {
		signal(SIGUSR1, recibirUltimo);
		while(!0)
			pause();
	} 
	if((pid_receptorTodo = fork()) == -1) {
		printf("ERROR AL CREAR PROCESO (RECEPTOR2)\n");
		exit(-1);
	} else if (pid_receptorTodo == 0) {
		signal(SIGUSR1, recibirTodo);
		while(!0)
			pause();
	} 
	
	printf("INICIALIZANDO...\n");
	sleep(1);
	menu(SIGUSR1); 
	while(!0)
		pause();

	exit(0);
}


