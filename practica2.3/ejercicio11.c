#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

//Crear variable de entorno SLEEP_SECS: 
//SLEEP_SECS=10
//export SLEEP_SECS

int main(){
	sigset_t set, pending;
	char *sleep_secs = getenv("SLEEP_SECS");
	int sec;
	
	if (sleep_secs == NULL){
		perror("SLEEP_SECS no definido\n");
		return -1;
	}
	
	//Inicializo un set de señales vacío y le añado las señales SIGINT y SIGTSTP
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);

	//Bloquear las señales del set
	sigprocmask(SIG_BLOCK, &set, NULL);

	//Obtener las señales pendientes
	sleep(atoi(sleep_secs));

	//Comprobamos las señales pendientes
	sigpending(&pending);

	if(sigismember(&pending, SIGINT) == 1){
		printf("SIGINT recibida\n");
		sigdelset(&set, SIGINT);
	}
	else printf("SIGINT no recibida\n");
	if(sigismember(&pending, SIGTSTP) == 1) {
		printf("SIGTSTP recibida\n");
		sigprocmask(SIG_UNBLOCK, &set, NULL);
		printf("El proceso continúa\n.");
	}
	else printf("SIGTSTP no recibida\n");

	//Desbloquear el set
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	
	return 0;
}
