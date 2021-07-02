#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    int socket_descriptor;
        struct sockaddr_in servidor;
    char *mensaje;
    //CREAMOS el socket
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_descriptor == -1){
     printf("Error en crear el socket");
    }
    servidor.sin_addr.s_addr = inet_addr("172.217.7.36");
    servidor.sin_family= AF_INET;
    servidor.sin_port = htons(80);
    //Conexion al servidor remoto
        if(connect(socket_descriptor, (struct sockaddr*)&servidor, sizeof(servidor)) < 0){
       puts("Error al conectarse");
         return 1;
    }
    puts("Conectado \n");
//Enviamos algun mensaje
mensaje= "GET /api/v2/ability/7/ HTTP/1.1\r\n\r\n";
if(send(socket_descriptor, mensaje, strlen(mensaje),0 )< 0){
    puts("Error al enviar el mensaje");
         return 1;
    }
    puts("Dato Enviado\n");
    return 0;
}
