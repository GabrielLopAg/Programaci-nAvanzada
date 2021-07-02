//creacion de socket

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*#include <sys/types.h>
#include <sys/socket.h>
int socket (int af, int type, int protocol); */

int main() {
    int descriptor_socket;  //descriptor del socket
    struct sockaddr_in servidor; //direccion del servidor
    
     //Creamos socket
    descriptor_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(descriptor_socket == -1){
      printf("No se puede crear el socket");
    }
    
	//Permite recibir una ip del servidor que uno desea conectarse
    servidor.sin_addr.s_addr = inet_addr("148.204.86.30");
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(80);
	//la funcion htons() convierte el entero corto sin signo, a una orden de bytes del host al de la red

/*
	struct sockaddr_in{
		short sin_family;  //AF_INET
		u_short sin_port;  //16 bits con el número de puerto
		struct in_addr sin_addr;    //32 bits con  la identificaciones de la red y del nodo
		char sin_zero[8];    //8 byts no usados.
	}
*/
	//int connect(int sfd, const void *addr, int addrlen);
	//Conexión al servidor remoto
    if(connect(descriptor_socket, (struct sockaddr *)&servidor, sizeof(servidor)) > 0){
		puts("error de conexion");
		return 1;
    }
    
    puts("Conectado");
    return 0;
}
