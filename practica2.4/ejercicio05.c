#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

int main(){
	char buffer[256];
	int fd1, fd2;
	int cambios = 0;
	int nfds;
	int size;
	fd_set set;

	if((fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK)) == -1){
		perror("Error abriendo la tuberia1.\n");
		return -1;
	}
	if((fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK)) == -1){
		perror("Error abriendo la tuberia2.\n");
	}

	while(cambios != -1){
		FD_ZERO(&set);
		FD_SET(fd1, &set);
		FD_SET(fd2, &set);

		if(fd1 > fd2) nfds = fd1 + 1;
		else nfds = fd2 + 1;

		cambios = select(nfds, &set, NULL, NULL, NULL);

		if(cambios == -1){
			perror("Error en select().\n");
			return -1;
		}
		else if(cambios > 0){
			if(FD_ISSET(fd1, &set)){
				size = read(fd1, buffer, sizeof(buffer)-1);
				buffer[size] = '\0';
				printf("Tuberia1: %s", buffer);
				close(fd1);
				fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
			}
			if(FD_ISSET(fd2, &set)){
				size = read(fd2, buffer, sizeof(buffer)-1);
				buffer[size] = '\0';
				printf("Tuberia2: %s", buffer);
				close(fd2);
				fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
			}
		}
	}
	close(fd1);
	close(fd2);

	return 0;
}
