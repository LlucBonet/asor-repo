#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//Escribir un programa que, usando open(2), cree un fichero con los permisos rw-r--r-x.

int main(int argc, char** argv){
	mode_t mask_old = umask(0027);
	int fd; 

	if(argc != 2){
		perror("Modo de uso: ./ejercicio5 <nombre del fichero>");
		return -1;
	}

	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777); 
	if(fd == -1){
		perror("Error");
		return fd;	
	}
	close(fd);
	umask(mask_old);
	return 1;

}
