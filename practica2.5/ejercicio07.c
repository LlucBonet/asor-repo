#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage: %s <direccion> <puerto>\n", argv[0]);
		return -1;
	}

	struct addrinfo *res;
	struct addrinfo hints;
	int rc, sd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

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

	freeaddrinfo(res);

	char buf[80];
	memset(buf, 0, sizeof(buf));

	while(1){
		int bytes = read(0, buf, sizeof(buf));
		if(bytes == -1){
			perror("Error en read()\n");
			return -1;
		}

		buf[bytes] = '\0';

		if(strcmp(buf, "Q\n") == 0) break;

		if((rc = send(sd, buf, bytes, 0)) == -1){
			perror("Error en send()\n");
			return -1;
		}

		if((bytes = recv(sd, buf, sizeof(buf), 0)) == -1){
			perror("Error en recv()\n");
			return -1;
		}

		buf[bytes] = '\0';
		printf("%s", buf);
	}
	close(sd);
	return 0;
}
