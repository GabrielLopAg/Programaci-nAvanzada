//Mi primer programa de semaforos
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<stdio.h>


int semaforo_id;
ushort semaforoarray[4];
int valor;

int main (){
     //creacion de semaforos
      if( (semaforo_id = semget (ftok("auxiliar", 'K'),4,IPC_CREAT |0600 )==-1)){
         printf("No se creo ningun semaforo :(\n");
     exit(-1);
      }
    //inicializamos el semaforo
    semaforoarray[0]= 5;  //INCREMENTO/DECREMENTO 1/0
    semaforoarray[1]= 5;
    semaforoarray[2]= 8;
    semaforoarray[3]= 8;
    //Declaracion
    valor =  semctl(semaforo_id,0, SETALL, semaforoarray);
        printf("%d\n",valor);
    //preguntamos por el valor del semaforo 3
    valor = semctl(semaforo_id,3, GETVAL, 0);
        printf("%d\n",valor);
        return  0;
}
