//CLIENTE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>	//familia inet
//#include <sys/un.h> 	//familia unix
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/*
	1. socket
	2. connect
	3. write()
	4. read()
	5. close()
*/

int main() {
	int socket_cliente;
	char ip_servidor[10];
	int puerto;
	int tam_struct_cliente;
	int estadoConexion;
	
	char cadenaCliente[1024];
    char cadenaServidor[1024];
    
    
    int inicio_sesion = 0;
		
	socket_cliente = socket(AF_INET, SOCK_STREAM, 0); // socket creado
	struct sockaddr_in servidor_direccion;
    struct sockaddr_in cliente_direccion;  
    
    printf("Ingresa la ip del servidor:\n");
    scanf("%s", ip_servidor);
    printf("Ingresa el puerto del servidor:\n");
    scanf("%d", &puerto);
    
    /*while(ciclo) {
		cliente_direccion.sin_family = AF_INET;  
		cliente_direccion.sin_addr.s_addr = inet_addr(ip_servidor); 
		cliente_direccion.sin_port = puerto; 
		tam_struct_cliente = sizeof(cliente_direccion);
		
		estadoConexion = connect(socket_cliente, (struct sockaddr *)&cliente_direccion, tam_struct_cliente);
		if(estadoConexion == -1) {
			printf("NO se pudo conectar\n");
			exit(-1);
			close(socket_cliente);
		}
			    	
		printf("---Sesion iniciada conb el servidor ---\n");
		printf("Ingresa un texto para enviarle al servidor\n");
		scanf("%*c%[^\n]", cadenaCliente);
		
		recv(socket_cliente, cadenaServidor, 1024, 0);
		printf("%s\n", cadenaServidor);
    
    }*/
    
    // inicializaciòn del socket
		cliente_direccion.sin_family = AF_INET;  
		cliente_direccion.sin_addr.s_addr = inet_addr(ip_servidor); 
		cliente_direccion.sin_port = puerto; 
		tam_struct_cliente = sizeof(cliente_direccion);

    	//2. connect (peticion de conexion)
       	estadoConexion = connect(socket_cliente, (struct sockaddr *)&cliente_direccion, tam_struct_cliente );
       	if(estadoConexion == -1 ){
         	printf("Problemas al conectar con servidor... \n");
         	exit(-1);
         	close(socket_cliente);
      	}
    printf("\t--Sesion iniciada con el servidor--\n");
    
	while(strcmp(cadenaCliente, "SALIR") != 0) {		
              
		//recibir mensaje del servidor
		recv(socket_cliente, cadenaServidor, 1024, 0);
		printf("MENSAJE DEL SERVIDOR: %s \n", cadenaServidor);
		inicio_sesion = 1;

		//3. write()
		//Enviamos una mensaje de texto al servidor
		printf("Ingresa un texto para enviarle al servidor:\n");
		scanf("%*c%[^\n]", cadenaCliente);
		send(socket_cliente, cadenaCliente, 1024, 0);
		
		//4. read()
		//Recibimos la respuesta del servidor
		//recv(socket_cliente,cadenaServidor, 1024,0 );
		//printf("El servidor contesto: %s \n", cadenaServidor);
      
  }

    close(socket_cliente);
     
}
