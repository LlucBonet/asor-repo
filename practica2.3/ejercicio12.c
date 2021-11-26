#include <stdio.h>
#include <signal.h>

volatile int sigint_count = 0; 
volatile int sigtstp_count = 0;
volatile int total_count = 0;

static void sigint_handler(int signal){
	sigint_count++;
	total_count++;	
}
static void sigtstp_handler(int signal){
	sigtstp_count++;
	total_count++;
	
}

int main(){
	struct sigaction sa;
	sigset_t set;

	
	sigaction(SIGINT, NULL, &sa);
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	sigaction(SIGTSTP, NULL, &sa);
	sa.sa_handler = sigtstp_handler;
	sigaction(SIGTSTP, &sa, NULL);

	sigemptyset(&set);

	while(total_count < 10){
		sigsuspend(&set);
	}

	printf("SIGINT: %i\n", sigint_count);
	printf("SIGTSTP: %i\n", sigtstp_count);

	return 0;
}

