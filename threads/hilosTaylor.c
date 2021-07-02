/*
   Cancelar hilos
La mayor parte de las aplicaciones los hilos terminan por si mismosos con una llamada pthread_exit una vez
concluido su trabajo.
Sin embargo puede haber aplicaciones donde los hilos no terminan nunca, o donde se permita que sean otros
hilos quienes den la orden de terminarlos

	-Se hace una peticion de cancelacion al hilo
		int pthread_cancel(pthread_t thread)
	-Se emplea para cambiar el estado de cancelacion del hilo actual (state, se refiere al estado actual y old al anterior)
		int pthread_setcancelstate(int state, int  *oldstate)
	-se emplea para cambiar el tipo de cancelacion del hilo actual
		int pthread_setcanceltype(int type, int *oldstate)
	-crear un punto de cancelacion en el hilo actual
		void pthread_testcancel(void)
	-se  utiliza para limpiar la pila donde se esta almacenando los hilos que se estan ejecutando
	-esta rutina se va ser ejecutada al recibir el argumento, para que inicie la limpieza
		void pthread_cleanup_push(void(*routine)(void*), void *arg)
		void pthread_cleanup_pop(int execute)
*/
//calcular la serie de taylor
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void  fin_de_calculo(void *arg){
    double resultado = *(double*)arg;
    printf("El resultado final es: %g\n", resultado);
}

void *calculo(void *arg){
    int error;
    int estado_ant, tipo_ant;
    double x = *(double *) arg;
    double resultado = 1, sumando = 1;
    long indicei, j;
    
    //Deshabilitamos la posibilidad de cancelar el hilo
    error = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &estado_ant);
    if(error)
    	printf("error, pthread_setcancelstate");
    	
    for(indicei=1; indicei<10; indicei++){
        sumando *= x/indicei;
        resultado += sumando;
    }
    printf("Primera aproximacion de exp(%g) = %g \n", x, resultado);
    
    //pthread_cleanup_push(void(*routine)(void*), void *arg)
    pthread_cleanup_push(fin_de_calculo, &resultado);  //macro
    
	//Una vez ejecutada la parte obligatoria habilitamos la posibilidad de cancelar el hilo en modo diferido
    error = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &tipo_ant);
    if(error)
        printf("error, pthread_setcanceltype");
        
    error = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &estado_ant);
    if(error)
        printf("error, pthread_setcancelstate");
        
    //En este momento del calculo se pueden aceptar peticiones de cancelacion
    printf("REFINAMIENTO DEL CALCULO\n");
    for(;;) {
        pthread_testcancel(); //punto de cancelacion
        //si no hay peticiones de cancelacion
        for(j=0; j<10; j++) {
            sumando *= x/indicei;
            resultado += sumando;
        }
    }
    pthread_cleanup_pop(1); //macro-fin
}

int main(int argc, char *argv[]){
    pthread_t hilo;
    int error;
    double x;
    int plazo;
    
    //aqui se leen los argumentos pasados por el main
    if(argc !=3){
        printf("Forma de uso: %s x plazos\n", argv [0]);   
        exit(-1);
    }else{
        x = atof(argv [1]);   
        plazo = atoi(argv [2]);
    }
    
    //Creacion de hilos para realizar los calculos
    error = pthread_create(&hilo, NULL, calculo, &x);
    if(error)
        printf("error, pthread_create");
        
	//Una vez concluido el plazo se cancela el hilo que calculo
    sleep(plazo);
    error = pthread_cancel(hilo);
    if(error)
        printf("error, pthread_cancel");
        
	//Esperando que la cancelacion se realice (o se haga efectiva)
    error = pthread_join(hilo, NULL);
    if(error)
        printf("error, pthread_join");
}
