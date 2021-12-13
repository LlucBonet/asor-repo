#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]){
	struct addrinfo hints;
	struct addrinfo *res, *rp;
	char name[257];	

	if(argc != 2){
		perror("Añade una dirección en el argumento.\n");
		return -1;
	}	

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;

	if(getaddrinfo(argv[1], NULL, &hints, &res) != 0){
		perror("Error en getaddrinfo().\n");
		return -1;
	}

	for(rp = res; rp != NULL; rp = rp->ai_next){
		getnameinfo(rp->ai_addr, rp->ai_addrlen, name, sizeof(name), NULL, 0, NI_NUMERICHOST);
		printf("%s %i %i\n", name, rp->ai_family, rp->ai_socktype);
	}

	freeaddrinfo(res);
	return 0;

}
