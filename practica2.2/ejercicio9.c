#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdio.h>

int main(int argc, char **argv){
	struct stat buf;
	char *filetype;

	
	if(stat(argv[1], &buf) == -1){
		perror("Error. Modo de uso: ./ejercicio9 fichero");
		return -1;
	}
	printf("Major: %u\n", major(buf.st_dev));
	printf("Minor: %u\n", minor(buf.st_dev));
	printf("Inodo: %ld\n",buf.st_ino);

	if(S_ISREG(buf.st_mode)) filetype = "Regular file";
	else if (S_ISDIR(buf.st_mode)) filetype = "Directory";
	else if(S_ISLNK(buf.st_mode)) filetype = "Symbolic link";
	printf("Tipo de fichero: %s\n", filetype);
	
	printf("Teimpo desde el último acceso: %ld\n", buf.st_atim.tv_sec);
	
	return 1;
}

//st_mtime muestra el tiempo desde la última modificacion del fichero
//st_ctime muestra el tiempo desde el último cambio de estado del fichero
