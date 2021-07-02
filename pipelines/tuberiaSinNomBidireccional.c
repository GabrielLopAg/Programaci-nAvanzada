//Tuberias sin nombre bidireccional
//version 2
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MAX 256

int main(){
    int tuberia_em_re[2]; //emisor_receptor
    int tuberia_re_em[2]; //receptor_emisor
    int pid;
    char mensaje [MAX];
	//Creacion de tuberias de comunicación
	if(pipe(tuberia_em_re)== -1 || pipe(tuberia_re_em)== -1 ){
		perror("pipe");
		exit(-1);
	}
	//Creacion de proceso hijo
    if((pid = fork())== -1) {
        perror("Proceso fork");   
        exit(-1);
    } else if(pid == 0 ){
		//Codigo del proce hijo
		//El proceso hijo (receptor) se encarga de leer mensajes de la tuberia 
		//y presentarlos en pantalla. Al recibir el mensaje "FIN\n" termina
		while(read(tuberia_em_re[0], mensaje, MAX) > 0 &&   strcmp(mensaje, "FIN\n") !=0) {
			printf("PROCESO RECEPTOR. MENSAJE: %s\n", mensaje);
			//Enviamos al proceso emisor un mensaje para indicar que estamos listos para recibir otro mensaje
			strcpy(mensaje,"LISTO");
			write(tuberia_re_em[1], mensaje, strlen(mensaje)+1);
		}
		close(tuberia_em_re[0]);
		close(tuberia_em_re[1]);
		close(tuberia_re_em[0]);
		close(tuberia_re_em[1]);
		exit(0);
	} else{
		//Codigo del proceso padre
		//El proceso padre (emisor) se encarga de leer un mensaje de la entrada estandar y acto seguido
		//escribirlo en la tuberia, para que lo reciba el proceso hijo. Al escribir el mensaje "FIN\n" acaban los dos procesos
		while(printf("PROCESO EMISOR. MENSAJE: ")!=0 && fgets(mensaje, sizeof(mensaje),stdin)!= NULL &&
		write(tuberia_em_re[1], mensaje, strlen(mensaje)+1)>0 &&
		strcmp(mensaje, "FIN\n")!=0)
		//Nos ponemos a esperar el mensaje "LISTO" procedente del proceso receptor
		do{
		    read(tuberia_re_em[0], mensaje, MAX);   
		} while(strcmp(mensaje,"LISTO")!=0);

		close(tuberia_em_re[0]);
		close(tuberia_em_re[1]);
		close(tuberia_re_em[0]);
		close(tuberia_re_em[1]);
		exit(0);
    }

}
