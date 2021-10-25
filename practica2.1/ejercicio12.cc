#include <stdio.h>
#include <time.h>

//Escribir un programa que muestre la hora, en segundos desde el Epoch, usando la función time(2). 
int main() {
	
	printf("Hora en segundos desde el Epoch: %li\n", time(NULL));
	return 1;
}
