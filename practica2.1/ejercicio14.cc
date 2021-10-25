#include <stdio.h>
#include <time.h>

//Escribir un programa que muestre el año usando la función localtime(3).
int main() {
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
        printf("Año: %i\n", lt->tm_year + 1900);	
	return 1;
}
