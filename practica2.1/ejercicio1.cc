#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

//Gestionar correctamente los errores generados por la llamada a 
//setuid(2)
int main() {
	int exito = setuid(0); //1: exito, -1: error
	if(exito == -1) {
		perror("ERROR setuid(2)");
	}
	return 1;
}
