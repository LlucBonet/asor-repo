#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//Escribir un programa que, usando open(2), cree un fichero con los permisos rw-r--r-x.

int main(int argc, char** argv){
	umask(0027);

	if(argc != 2){
		perror("Modo de uso: ./ejercicio5 <nombre del fichero>");
	}
	else if(access(argv[1], F_OK) == 0){
		perror("Este fichero ya existe.");
	}
	else if(open(argv[1], O_CREAT, 00645) == -1){
		perror("Error");	
	}
	return 1;

}
