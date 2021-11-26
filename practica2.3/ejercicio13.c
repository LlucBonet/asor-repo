#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int stop = 0;

static void handler(int signal){
	if(signal == SIGUSR1) stop = 1;
}

int main(int argc, char **argv){
	if (argc != 2){
		printf("Introduce los segundos de sleep");
		return -1;
	}
	
	sigset_t set;
	struct sigaction sa;
	int secs;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	
	sigaction(SIGUSR1, &sa, NULL);
	
	sigemptyset(&set);
	
	secs = atoi(argv[1]);
	if(secs < 0) secs = 0;
	sleep(secs);

	if(stop){
		printf("Se ha detenido.\n");
	}
	else{
		printf("Borrando fichero...\n");
		unlink(argv[0]);
	}

	return 0;
}
