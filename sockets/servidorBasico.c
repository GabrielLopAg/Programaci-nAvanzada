// Servidor
/*
1. Declarar el socket		- Apertura canal
2. Usar el metodo bind 		- Publicidad de la direcciòn
3. Usar listen				- Disposicion de ceptar conexiones
4. Usar accept				- Aceptar una conexion. Bloquea el proceso hasta que reciba una peticion de conexion
5. Usar read				- Lectura de la peticion del servicio (cliente)
6. Usar write				- Envio de respuesta o solicitud (cliente)
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //familia inet
//#include <sys/un.h> //familia unix
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void escribirEnArchivo(char const *cadena) {
	printf("Creando archivo txt\n");
	FILE *archivo;
	archivo = fopen("archivo.txt", "a");
	if(archivo) {
		fprintf(archivo, "%s\n", cadena);
	}
	fclose(archivo);
}

int main() {
	struct sockaddr_in servidor_direccion; 
    struct sockaddr_in cliente_direccion;
    int tamstructuraservidor;
    int tamstructuracliente;
    int puerto;
    
	int socket_servidor, socket_cliente;
	int socket_bind;
	int socket_listen;
	int socket_read;
	int bandera = 1;
	char cadenaCliente[1024];
    char cadenaServidor[1024];
    int inicio_sesion=0;
	
	socket_servidor = socket(AF_INET, SOCK_STREAM, 0); // creacion del socket
	if(socket_servidor == -1){
        printf("No se puede crear el socket \n");
        exit(-1);
      }
      printf("Ingrese el puerto de escucha:\n");
      scanf("%d", &puerto);
	
	servidor_direccion.sin_addr.s_addr = inet_addr("127.0.0.1");
	servidor_direccion.sin_family = AF_INET;
    servidor_direccion.sin_port = puerto;
    tamstructuraservidor= sizeof(servidor_direccion);
	
	socket_bind = bind(socket_servidor, (struct sockaddr *)&servidor_direccion, tamstructuraservidor);
	if(socket_bind == -1) {
		printf("No se puede crear el bind\n");
		exit(-1);
	}
	
	
	int backlog = 2;
	socket_listen = listen(socket_servidor, backlog); // voy a escuchar 2 clientes
	if(socket_listen == -1) {
		printf("No se puede crear el listen\n");
		exit(-1);
	}
	
	printf("Servidor en espera....\n");
	
	/*while(bandera) {
		socket_cliente = accept(socket_servidor, (struct sockaddr *)&servidor_direccion, &tamstructuraservidor);
		if(socket_cliente == -1) {
			printf("No se puede crear el bind\n");
			exit(-1);
		}
		
		printf("--CLIENTE YA CONECTADO--\n");
		
		strcpy(cadenaServidor, "--El servidor te da la bienvenida---");
		send(socket_cliente, cadenaServidor, 1024, 0);
		
		recv(socket_cliente, cadenaCliente, 1024, 0);
		printf("Mensaje del cliente: %s\n", cadenaCliente);
		
		close(socket_cliente);
	}*/
	
	while(1){
	
		socket_cliente = accept(socket_servidor, (struct sockaddr *)&cliente_direccion, &tamstructuracliente );
		if(socket_cliente == -1){
			printf("No se puede crear el accept \n");
			exit(-1);
		}

		printf("\tCliente inicio sesion\n");
		printf("-- CLIENTE CONECTADO--\n");
		
		strcpy(cadenaServidor, "--- El servidor te da la Bienvenida ---"); // mensaje al cliente
		send(socket_cliente, cadenaServidor, 1024, 0 );
		
		while(strcmp(cadenaServidor, "SALIR") != 0) {
			//5. Usar read() - Lectura de la peticion del servicio (cliente)
			recv(socket_cliente,cadenaCliente, 1024, 0);
			printf("MENSAJE DEL CLIENTE: %s\n", cadenaCliente);
				  
			//escribirEnArchivo(cadenaCliente);
				  
			printf("Ingrese una cadena para el cliente: \n");
			scanf("%*c%[^\n]",cadenaCliente);
			send(socket_cliente,cadenaCliente, 1024, 0);			
		
		}

		
		close(socket_cliente);
	}
 	
	close(socket_servidor);
		

}



