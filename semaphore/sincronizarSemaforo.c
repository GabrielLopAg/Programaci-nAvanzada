#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#define SEM_HIJO 0
#define SEM_PADRE 1

/*
	struct sembuf {
		ushort sem_num; // numero de semaforo
		short sem_op; // operacion del semaforo
		short sem_flg; // mascara de bits
	}
*/

int main() {
	int i = 10;
	int semid, pid, semaforo_id;
	struct sembuf operacion; // nos permite configurar de forma personalizada cada semaforo
	key_t llave;
	
	// Pedimos un  identificador con dos semaforos
	// 1. Pedir llave
	llave = ftok("auxiliar", 'k');
	if((semaforo_id = semget(llave, 2, IPC_CREAT |0600) == -1)) {
		printf("No se creo ningun semaforo: (\n");
		exit(-1);
	}
	
	// Iniciamos los semaforos
	// Grupo-Semaforos, id_semaforo, setvalor
	semctl(semaforo_id, SEM_HIJO, SETVAL, 0);
	semctl(semaforo_id, SEM_PADRE, SETVAL, 0);
	
	// creamos el proceso hijo
	if((pid = fork()) == -1) {
		printf("No se creo el proceso hijo: (\n");
		exit(-1);
	} else if(pid == 0) {
		while(i) {
			// codigo del proceso hijo
			// cerramos el semaforo
			operacion.sem_num = SEM_HIJO;
			operacion.sem_op = -1;
			operacion.sem_flg = 0;
			semop(semid, &operacion, 1);
			printf("PROCESO HIJO: %d\n", i--);
			// abrimos el semaforo
			operacion.sem_num = SEM_PADRE;
			operacion.sem_op = 1;
			
			semop(semaforo_id, &operacion, 1);
		}
		// borrramos el semaforo
		semctl(semaforo_id, 0, IPC_RMID, 0);
	} else {
		// codigo del padre
		operacion.sem_flg = 0;
		while(i) {
			// cerramos el semaforo del proceso padre
			operacion.sem_num = SEM_PADRE;
			operacion.sem_op = -1;
			operacion.sem_flg = 0;
			semop(semid, &operacion, 1);
			printf("PROCESO PADRE: %d\n", i--);
			// abrimos el semaforo DEL HIJO
			operacion.sem_num = SEM_HIJO;
			operacion.sem_op = 1;

			semop(semaforo_id, &operacion, 1);
		}
		// borrramos el semaforo
		semctl(semaforo_id, 0, IPC_RMID, 0);
	
	}
}

/*
	int sem_init(sem_t *sem, int pshared, unisgned value);
	pshared = 1 (semaforo compartido por procesos padre-hijo)
	value (valor de inicializaciòn)
	int sem_post(sem_t *sem); desbloquea Incrementa
	int sem_wait(sem_t *sem); bloquea Decrementa
	int sem_destroy(sem_t *sem);
*/
