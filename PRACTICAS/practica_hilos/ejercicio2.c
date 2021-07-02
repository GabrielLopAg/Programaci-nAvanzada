/*
	LOPEZ AGUIRRE GABRIEL
	2. Crear un programa que desarrolle un almacén de bebidas
		Las variables que van a compartir los hilos son:
		a) Una estructura de datos que contenga (idProducto, Nombre_Producto, Precio_Producto).
		b) Una pila que guarde la estructura
		-El primer hilo guardara en la pila los productos y le notificara al hilo 2 cuando guarde el producto
		-El segundo hilo solo obtendrá de la pila los productos almacenados, cuando se lo notifique el hilo1 y los imprime
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>
#define LENGHT 100

static pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

typedef struct _almacen {
	int idProducto;
	char Nombre_Producto[LENGHT];
	double Precio_Producto;
} almacen;

typedef struct _Nodo {
	almacen producto;
	struct _Nodo *siguiente;
} Nodo;

Nodo *pila = NULL;

Nodo *asignarMemoria(almacen dato) {
	Nodo* nuevo;
	nuevo = (Nodo *) malloc(sizeof(Nodo));
	nuevo -> producto = dato;
	nuevo -> siguiente = NULL;
	return nuevo;
}

Nodo *push(Nodo *top, almacen dato) {
	Nodo *nuevo;
	nuevo = asignarMemoria(dato);
	if(top != NULL) {
		nuevo -> siguiente = top;
	}
	return nuevo;
}

void mostrar(Nodo *top) {
	if(top == NULL)
		printf("La PILA esta vacia...\n");
	while(top != NULL) {
		almacen aux = top->producto;
		printf("Id: %d, Nombre: %s, Precio: %.2f\n", aux.idProducto, aux.Nombre_Producto, aux.Precio_Producto);
		top = top->siguiente;
	}
}

void *codigoPrimerHilo() {
	almacen alm;
	int id;
	char nombre[LENGHT];
	double precio;
	int cantidad = 0;
	
	pthread_mutex_lock(&count_mutex);
	printf("Ingrese la cantidad de productos que desea almacenar: ");
	scanf("%d", &cantidad);
	for(int i=0; i<cantidad; i++) {
		printf("\nIngrese el ID del producto: ");
		scanf("%d", &id);
		while((getchar())!='\n');
		
		printf("Ingrese el Nombre del producto: ");
		scanf("%s", nombre);
		while((getchar())!='\n');
		
		printf("Ingrese el Precio del producto: ");
		scanf("%lf", &precio);
		while((getchar())!='\n');
		
		alm.idProducto = id;
		strcpy(alm.Nombre_Producto, nombre);
		alm.Precio_Producto = precio;
		
		pila = push(pila, alm);
	}
	putchar('\n');
	pthread_cond_signal(&condition_var);
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(0);
}

void *codigoSegundoHilo() {
	pthread_mutex_lock(&count_mutex);
	pthread_cond_wait(&condition_var, &count_mutex);
	
	mostrar(pila);
	
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(0);
}

int main() {

	pthread_t hilo1, hilo2;
	int error, error2;
	int *salida;
	
	error = pthread_create(&hilo1, NULL, codigoPrimerHilo, NULL); 
	 if(error) {
	 	printf("error\n");
	 	exit(-1);
	 }
	 error2 = pthread_create(&hilo2, NULL, codigoSegundoHilo, NULL); 
	 if(error2) {
	 	printf("error\n");
	 	exit(-1);
	 }
		
	error = pthread_join(hilo1, (void **) &salida);
	if(error) {
		printf("error\n");
	} 
	error2 = pthread_join(hilo2, (void **) &salida); 
	if(error2) {
		printf("error\n");
	} 
	
}

