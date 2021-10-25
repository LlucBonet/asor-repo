#include <unistd.h>
#include <stdio.h>

//Escribir un programa que obtenga, con pathconf(3), información de configuración del sistema de ficheros e imprima, por ejemplo,  el número máximo de enlaces, el tamaño máximo de una ruta y el de un nombre de fichero.
int main() {
	
	const char *path = "/";
	printf("Número máximo de enlaces: %li\n", pathconf(path, _PC_LINK_MAX));
	printf("Tamaño máximo de una ruta: %li\n", pathconf(path, _PC_PATH_MAX));
	printf("Tamaño máximo de un nombre de fichero: %li\n", pathconf(path, _PC_NAME_MAX));

	return 1;
}

