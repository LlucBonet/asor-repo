#include <unistd.h>
#include <limits.h>
#include <stdio.h>

// Escribir un programa que obtenga, con sysconf(3), información de configuración del sistema e imprima, por ejemplo, la longitud máxima de los argumentos, el número máximo de hijos y el número máximo de ficheros.

int main() {
	
	printf("Longitud máxima de los argumentos: %li\n",sysconf(_SC_ARG_MAX));
	printf("Número máximo de hijos: %li\n", sysconf(_SC_CHILD_MAX));
	printf("Número máximo de los ficheros: %li\n", sysconf(_SC_OPEN_MAX));	
	return 1;
}
