//Mi primer programa ;) Comunicacion entre procesos usando los pipeline sin nombre

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

#define MAX 256
int main(){ 
     int tuberia[2];  //canal de comunicacion
     int pid;
     char mensaje[MAX];
     //CREACION DE TUBERIA SIN NOMBRE
    if(pipe(tuberia) == -1){
        printf("Error de crear mi canal de comunicacion (PIPELINE)");   
      exit(-1);
    }

    //CREACION DEL PROCESO BB
       if((pid=fork()) == -1){
      printf("Error de crear al proceso bb (PIPELINE)");   
      exit(-1);
    }else if(pid==0){
        //codigo del bb
	//el bb va ser el receptor encargado de leer mensajes de la tuberia y presentarlos en pantalla.
	//el ciclo terminara al leer el mensaje LionXD
        while(read (tuberia [0], mensaje, MAX)> 0 && strcmp (mensaje, "Termina\n") != 0)
        printf("PROCESO RECEPTOR. MENSAJE: %s\n", mensaje);
            close(tuberia[0]);
            close(tuberia[1]);
         exit(0);
    }else{
        //codigo del proceso padre
        //va a comportarse como emisor, se encarga de leer los mensajes de la entrada estandar y 
        //acto seguido los pasa a la tuberaia para que los reciba el proceso bb. Recordando que el ciclo terminara al escribir LionXD
          while(printf("PROCESO EMISOR. MENSAJE: %s\n", mensaje) != 0 &&
                 fgets(mensaje, sizeof(mensaje), stdin) !=NULL &&
                 write (tuberia [1], mensaje, strlen(mensaje)+1)> 0 && strcmp (mensaje, "Termina\n") != 0)
         printf("PROCESO RECEPTOR. MENSAJE: %s\n", mensaje);
            close(tuberia[0]);
            close(tuberia[1]);
         exit(0);

        }

}
