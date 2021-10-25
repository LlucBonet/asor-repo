#include <stdio.h>
#include <time.h>

//Modificar el programa anterior para que imprima la hora de forma legible, como "lunes, 29 de octubre de 2018, 10:34", usando la función strftime(3).

int main() {
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
        printf("Año: %i\n", lt->tm_year + 1900);

	char s[100];
	strftime(s, 100, "%A, %d de %B de %Y, %H:%M", lt);
	printf("Fecha y hora: %s\n", s);	
	return 1;
}
