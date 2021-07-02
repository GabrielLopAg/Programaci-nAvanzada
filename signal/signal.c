#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
     void manejador_SIGINT();
    
    if(signal(SIGINT, manejador_SIGINT)== SIG_ERR){
      perror("senial");
      exit(-1);
   }
      while(1){
           printf("En espera de Ctrl-C\n");
           sleep(999);
      }
}

//Método para el tratamiento de la señal
void manejador_SIGINT(int senial){
   static int cnt=0;
   printf("\nSenial numero %d recibida. \n", senial);
   if(cnt<5)
    printf("Contador = %d\n", cnt++);
   else
    exit(0);
   if(signal (SIGINT, manejador_SIGINT) == SIG_ERR)
   {
       perror("signal");
    exit(-1);
   }
}
