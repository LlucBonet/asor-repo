#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char **argv){
	int fd;
	int status;
	time_t t = time(NULL);	

	if((fd = open(argv[1], O_CREAT | O_RDWR, 0644)) ==-1){
		perror("Error al abrir el fichero.\n");
		return -1;
	}
	
	status = lockf(fd, F_TEST, 0);
	if (status == 0){ //desbloqueado
		printf("Cerrojo desbloqueado.\n");
		if(lockf(fd, F_LOCK, 0) == -1){
			printf("Error bloqueando cerrojo.\n");
			return -1;
		}
		printf("Bloqueando cerrojo.\n");
		printf("Hora actual: %s\n", ctime(&t));
		sleep(3);
		if(lockf(fd, F_ULOCK, 0) == -1){
			printf("Error desbloquando cerrojo.\n");
			return -1;
		}
		printf("Cerrojo desbloqueado.\n");
	}
	else {
		printf("Cerrojo bloqueado.\n");
	}
	close(fd);
	return 1;
}
