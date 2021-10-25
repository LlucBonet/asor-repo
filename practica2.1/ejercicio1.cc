#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int exito = setuid(0);
	if(exito == -1) {
		perror("ERROR setuid(2)");
	}
	return 1;
}
