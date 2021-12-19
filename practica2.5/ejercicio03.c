#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char ** argv){
	if(argc != 4){
		printf("Usage: %s <direccion host> <puerto> <comando>\n", argv[0]);
		return -1;
	}

	struct addrinfo *res;
	struct addrinfo hints;
	int rc, sd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;
	
	if((rc = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1){
		perror("Error en getaddrinfo()\n");
		return -1;
	}

	if((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1){
		perror("Error en socket()\n");
		return -1;
	}

	if((rc = connect(sd, res->ai_addr, res->ai_addrlen)) == -1){
		perror("Error en connect()\n");
		return -1;
	}

	char command[2];
	command[0] = argv[3][0];
	command[1] = '\n';
	
	if((rc = sendto(sd, command, 2, 0, res->ai_addr, res->ai_addrlen)) == -1){
		perror("Error en sendto()\n");
		return -1;
	}

	char buf[100];
	struct sockaddr_storage addr;
	socklen_t addr_len = sizeof(addr);
	int bytes = recvfrom(sd, buf, 100, 0, (struct sockaddr*) &addr, &addr_len);
	buf[bytes] = '\0';
	printf("%s", buf);

	freeaddrinfo(res);

	return 0;
}
