#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>
#include <string.h>

//Programa que muestra con uname(2) cada aspecto del sistema y su valor
int main() {
	struct utsname buf;
	if(uname(&buf) == -1){ //Comprobar la correcta ejecución de la llamada
		printf("uname ERROR %d: %s\n", errno, strerror(errno));
		return -1;
	}
	else{
		printf("Operating system name: %s\n", buf.sysname);
		printf("Network Node name: %s\n", buf.nodename);
		printf("Operating system release: %s\n", buf.release);
		printf("Operating system version: %s\n", buf.version);
		printf("Hardware machine identifier: %s\n", buf.machine);
		printf("Domain name: %s\n", buf.domainname);	
	}
	return 1;
}
