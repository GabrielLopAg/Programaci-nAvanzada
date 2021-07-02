#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "utmp.h"
#define MAX 256

// macro para comparar dos cadenas de caracteres
#define EQ(str1, str2) (strcmp((str1), (str2)) == 0)

// descriptores de fichero de las tuberias con nombre mediante las cuales 
// vamos a comunicarnos
int fifo_12, fifo_21;;
char nombre_fifo_12[MAX], nombre_fifo_21[MAX];

// array para leer los mensajes
char mensaje[MAX];
void fin_de_transmision(int sig);

int main(int argc, char *argv[]) {
	int tty;
	char terminal[MAX], *logname, *getenv();
	struct utmp *utmp, *getutent();
	void fin_de_transmision();
	
	// analisis de los argumentos de la linea de ordenes
	if(argc != 2) {
		fprintf(stderr, "Forma de uso: %s usuario\n", argv[0]);
		exit(-1);
	}
	
	// lectura de nuestro nombre de usuario
	logname = getenv("LOGNAME");
	
	// comprobacion para que un usuario no se llame a si mismo
	if(EQ(logname, argv[1])) {
		fprintf(stderr, "Comunicacion con uno mismo no permitida\n");
		exit(0);
	}
	
	// consultamos si el usuario ha iniciado una sesion
	while((utmp = getutent()) != NULL && strncmp(utmp->ut_user, argv[1], sizeof(utmp->ut_user)) != 0);
	if(utmp == NULL) {
		printf("EL USUARIO %s NO HA INICIADO SESION\n", argv[1]);
		exit(0);
	}	
	
	// formacion de los nombres de las tuberias de comunicacion
	sprintf(nombre_fifo_12, "/tmp/%s_%s", logname, argv[1]);
	sprintf(nombre_fifo_21, "/tmp/%s_%s", argv[1], logname);
	
	// creacion y apertura de las tuberias
	// primero borramos las tuberias, para que la llamda a mknod no falle 
	unlink(nombre_fifo_12);
	unlink(nombre_fifo_21);
	
	// cambiamos la mascara de permisos por defecto para este proceso.
	// esto permitira crear las tuberias con los permisos rw-rw-rw = 0666
	umask(~0666);
	
	// creamos las tuberias para que la llamada a open no falle
	if(mkfifo(nombre_fifo_12, 0666) == -1) {
		perror(nombre_fifo_12);
		exit(-1);
	}
	if(mkfifo(nombre_fifo_21, 0666) == -1) {
		perror(nombre_fifo_21);
		exit(-1);
	}
	
	// apertura del terminal del usuario
	sprintf(terminal, "/dev/%s", utmp->ut_line);
	if((tty = open(terminal, O_WRONLY)) == -1) {
		perror(terminal);
		exit(-1);
	}
	
	// aviso al usuario con el que queremos comunicarnos
	sprintf(mensaje, "\n\t\tLlamada procedente del usuario %s\07\07\07\n \t\tResponder escribiendo: responder-a %s\n\n", logname, logname);
	write(tty, mensaje, strlen(mensaje)+1);
	close(tty);
	
	printf("Esperando respuesta...\n");
	// apertura de las tuberias. Una de ellas para escribir mensajes y la otra para leerlos
	if((fifo_12 = open(nombre_fifo_12, O_WRONLY)) == -1 || (fifo_21 = open(nombre_fifo_21, O_RDONLY)) == -1) {
		if(fifo_12 == -1)
			perror(nombre_fifo_12);
		else 
			perror(nombre_fifo_21);
		exit(-1);
	}
	
	// a este punto llegamos cuando nuestro interlopcutor responde a nuestra llamada
	printf("Llamada atendida. \07\07\07\n");
	
	// armamos el manejador de la señal SIGINT. Esta señal se genera al pulsar ctrl+c
	signal(SIGINT, fin_de_transmision);
	
	// bucle de envios de mensajes
	do {
		printf("<== ");
		fgets(mensaje, sizeof(mensaje), stdin);
		write(fifo_12, mensaje, strlen(mensaje) + 1);
		// bucle de recepcion de mensaje
		if(EQ(mensaje, "cambio\n"))
			do {
				printf("==> "); fflush(stdout);
				read(fifo_21, mensaje, MAX);
				printf("%s", mensaje);
			} while(!EQ(mensaje, "cambio\n") && !EQ(mensaje, "corto\n"));
	} while(!EQ(mensaje, "corto\n"));
	
	// fin de la transmision
	printf("FIN DE TRANSMISION\n");
	close(fifo_12);
	close(fifo_21);
	
	exit(0);
	
}

void fin_de_transmision(int sig) {
	sprintf(mensaje, "corto\n");
	write(fifo_12, mensaje, strlen(mensaje) + 1);
	printf("FIN DE TRANSMISION\n");
	close(fifo_12);
	close(fifo_21);
	exit(0);
}
