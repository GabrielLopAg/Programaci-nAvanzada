#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
	Creaciòn (ejecuciòn) de nuevos procesos, mediante la funciòn exec()
	int execv(const char *path, const char *argv[])
*/

int main() {
	//char *args[] = {"/sbin/shutdown", NULL};
	//execv("/sbin/shutdown", args);
	char *args[] = {"ls","-l","/home/gabriel", NULL};
	execv("/bin/ls", args);
	
	printf("Se produce un error al ejecutar execv\n");
	
	return 0;
}

