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

//Hay diferencia si los descriptores de ficheros son distintos.

/*
 ls > dirlist 2>&1 imprime todo lo que salga de ls (incluido errores) al 
 fichero dirlist y luego los errores que se produzcan en el acceso a dirlist,
 se imprimen por salida estandar.

 ls 2>&1 dirlist imprime la salida de error por pantalla pero no escribe
 nada en dirlist.
 * */
