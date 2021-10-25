#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

//Modificar el programa anterior para que muestre además el nombre de usuario, el directorio home y la descripción del usuario.

int main() {

	printf("UID real: %i\n", getuid());
	printf("UID efectivo: %i\n", geteuid());

	struct passwd *p = getpwuid(getuid());
	printf("Nombre de usuario: %s\n", p->pw_name);
	printf("Directorio home: %s\n", p->pw_dir);
	printf("Descripción del usuario: %s\n:", p->pw_gecos);	

	return 1;
}

