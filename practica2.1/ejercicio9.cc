#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

//Escribir un programa que muestre, igual que id, el UID real y efectivo del usuario. ¿Cuándo podríamos asegurar que el fichero del programa tiene activado el bit setuid?

int main() {

	printf("UID real: %i\n", getuid());
	printf("UID efectivo: %i\n", geteuid());
	
	printf("\nCuando el UID real y el UID efectivo son diferentes podemos asegurar que el fichero del programa tiene actvado el bit setuid.\n"
);
	return 1;
}

