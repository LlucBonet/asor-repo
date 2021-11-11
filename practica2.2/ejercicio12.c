#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv){
	int fd;

	if ((fd = open(argv[1], O_CREAT | O_APPEND | O_RDWR)) == -1){
		perror("Error. Modo de uso: ./ejercicio12 ruta");		     }
	else{
		dup2(fd, 1);
		printf("printf redirigido a un fichero\n");
		printf("Otro printf\n");
	}
	close(fd);
	return 1;
}
