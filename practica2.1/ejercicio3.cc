#include <stdio.h>
#include <string.h>

//Imprimir todos los mensajes de error disponibles en el sistema
int main() {

	char *s;
		
	for(int i = 0; i < 134; i++) {
		printf("Error %i: %s\n", i, strerror(i));
	}
	return 1;
}
