#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv){
	int fd;

	if ((fd = open(argv[1], O_CREAT | O_APPEND | O_RDWR, 0666)) == -1){
		perror("Error. Modo de uso: ./ejercicio13 ruta");		     }
	else{
		dup2(fd, 1);
		dup2(fd, 2);
		printf("Salida estandar redirigida a un fichero\n");
		perror("Error redirigido a fichero\n");
	}
	close(fd);
	return 1;
}
