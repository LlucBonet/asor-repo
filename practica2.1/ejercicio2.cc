#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
	int exito = setuid(0);
	if(exito == -1) {
		printf("setuid(2) ERROR %d: %s\n", errno, strerror(errno));
	}
	return 1;
}
