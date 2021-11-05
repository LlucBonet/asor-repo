#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//Escribir un programa que, usando open(2), cree un fichero con los permisos rw-r--r-x.

int main(int argc, char** argv){

	if(argc != 2){
		perror("Modo de uso: ./ejercicio5 <nombre del fichero>");
	}
	else if(open(argv[1], O_RDONLY) != -1){
		perror("Este fichero ya existe");	
		return -1;
	}
	else if(open(argv[1], O_CREAT, 00645) == -1){
		perror("Error");
		return -1;
	}
	return 1;

}
