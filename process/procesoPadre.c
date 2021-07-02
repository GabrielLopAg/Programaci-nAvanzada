#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int proceso_id = 0;
	int i = 0;
	//proceso_id = fork();
	switch(fork()) {
		case -1:
			perror("No se creo el proceso\n");
			exit(-1);
			break;
		case 0: // codigo del proceso hijo
			while(i < 10) {
				sleep(1);
				printf("\n\t\tI'm your son: %d\n", i++);
			}
			break;
		default: // codigo del padre
			while(i < 10){			
				printf("Im your father luke: %d\n", i++);
				sleep(1);
			}
	};
	exit(0);


	return 0;
}
