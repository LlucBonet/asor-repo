#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc < 2){
		perror("Error: debe introducir el programa a ejecutar.");
		return -1;
	}
	
	execvp(argv[1], argv+1);
	printf("El comando termino de ejcutarse\n");
	
	return 0;
}

//El mensaje de finalización no se muestra porque execvp sustituye la imagen del proceso original por el comando que se está realizando.
