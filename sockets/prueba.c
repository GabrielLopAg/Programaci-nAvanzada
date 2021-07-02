//Servidor
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>//familia inet
//#include <sys/un.h> //familia unix
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
     struct sockaddr_in servidor_direccion; //es una estructura donde se define (puertos, direcciones, familia)
     struct sockaddr_in cliente_direccion;  //es donde defino las caracteristicas del cliente
     int tamstructuraservidor;
     int tamstructuracliente;
     int puerto;

     int socket_servidor, socket_cliente; //es el que se le asigna al socket sfd (socket_descriptor)
     int socket_bind;  //recibe el valor del bind
     int socket_listen;
     
     char cadenaCliente[1024];
     char cadenaServidor[1024];


     printf("Creando el servidor en la ip 127.0.0.1 :\n");
    
	//1. Declarar el socket  -Apertura del canal
      socket_servidor = socket(AF_INET, SOCK_STREAM,0);  //socket(tipo_familia, comportamiento, protocolo);
      //verifico si todo va bien
	//1a. Inicializarlo
      if(socket_servidor == -1){
        printf("No se puede crear el socket \n");
        exit(-1);
      }
      printf("Ingrese el puerto de escucha:\n");
      scanf("%d", &puerto);

	//1b. Configuracion -direccion,puerto etc.
      servidor_direccion.sin_family= AF_INET;  //familia
      servidor_direccion.sin_addr.s_addr = inet_addr("127.0.0.1"); //especifico la direccion donde me conecto
      servidor_direccion.sin_port= puerto; //htons(80); //asignamos el puerto de comunicacion
      tamstructuraservidor= sizeof(servidor_direccion);

	//2. Usar el metodo bin- Publicidad de la direccion (conectar el socket con el puerto o direccion)
     
     //int bind (int sfd, const void *addr, int addrlen);
     socket_bind = bind(socket_servidor,(struct sockaddr *)&servidor_direccion,tamstructuraservidor );
     if(socket_bind == -1){
        printf("No se puede crear el bind \n");
        exit(-1);
      }

	//3. Usar listen  -Disposicion de acpetar conexiones
      //int listen (int sfd, int backlog);
      socket_listen = listen(socket_servidor,2); //voy a escuchar a 2 clientes
      if(socket_listen == -1){
        printf("No se puede crear el listen \n");
        exit(-1);
      }
      printf("Servidor en espera....\n");

	while(bandera) {
		socket_cliente = accept(socket_servidor, (struct sockaddr *)&cliente_direccion, &tamstructuracliente );
      	if(socket_cliente == -1){
		    printf("No se puede crear el accept \n");
		    exit(-1);
      }
	
	}
      
     printf("--CLIENTE YA CONECTADO--\n");
	
	strcpy(cadenaServidor, "--El servidor te da la bienvenida---");
	send(socket_cliente, cadenaServidor, 1024, 0);
	
}
