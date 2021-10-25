#include <sys/time.h>
#include <stdio.h>

//Escribir un programa que mida, en microsegundos usando la función gettimeofday(2), lo que tarda un bucle que incrementa una variable un millón de veces.
int main() {
	struct timeval tv1, tv2;
	
	gettimeofday(&tv1, NULL);
	int m = 1;
	for(int i=0; i < 1000000; i++) {
		m++;
	}
	gettimeofday(&tv2, NULL);

	printf("Tiempo en microsegundos: %li\n", tv2.tv_usec - tv1.tv_usec);
	return 1;
}
