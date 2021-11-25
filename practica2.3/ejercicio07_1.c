#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc < 2){
		perror("Error: debe introducir el programa a ejecutar.");
		return -1;
	}
	system(argv[1]);
	printf("El comando terminó de ejecutarse\n");
	
	return 0;
}

//El mensaje de finalización se muestra porque system no sustituye la imagen del proceso.
