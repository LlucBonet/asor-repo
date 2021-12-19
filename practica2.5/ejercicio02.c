#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]){
	struct addrinfo hints;
	struct addrinfo *res;
	int rc, sd;

	if(argc != 3){
		perror("Añade la dirección y el puerto como argumentos.\n");
		return -1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if((rc = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0){
		perror("Error en getaddrinfo().\n");
		return -1;
	}

	if((sd = socket(res->ai_family, res->ai_socktype, 0)) == -1){
		perror("Error en socket().\n");
		return -1;
	}

	if(bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen) == -1){
		perror("Error en bind().\n");
		return -1;
	}
	
	freeaddrinfo(res);

	while(1){
		char buf[8];
		int bytes;
		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof(struct sockaddr_storage);
		if((bytes = recvfrom(sd, buf, 80, 0, (struct sockaddr *) &addr, &addrlen)) == -1){
			perror("Error en recvfrom()\n");
			return -1;
		}
		buf[bytes] = '\0';

		char host[NI_MAXHOST],  serv[NI_MAXSERV];
		if((rc = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST)) == -1){
			perror("Error en getnameinfo()\n");
			return -1;
		}
		printf("%d bytes de %s:%s\n", bytes, host, serv);

		if(strcmp(buf, "t\n") == 0){
			struct tm *lt;
			time_t t;
			time(&t);
			lt = localtime(&t);

			if(lt == NULL){
				perror("Error localtime()");
				return -1;
			}

			char cadena[100];

			strftime(cadena, 100, "%H:%M:%S\n", lt);
			sendto(sd, cadena, strlen(cadena)+1, 0, (struct sockaddr*) &addr, addrlen);
		}

		else if(strcmp(buf, "d\n") == 0){
			struct tm *lt;
			time_t t;
			time(&t);
			lt = localtime(&t);

			if(lt == NULL){
				perror("Error en localtime()\n");
				return -1;
			}

			char cadena[100];

			strftime(cadena, 100, "%d/%m/%y\n", lt);
			sendto(sd, cadena, strlen(cadena)+1, 0, (struct sockaddr *) &addr, addrlen);
		}
		else if(strcmp(buf, "q\n") == 0){
			printf("Saliendo...\n");
			close(sd);
			return 0;
		}
		else{
			buf[bytes-1]='\0';
			printf("Comando %s no soportado.\n", buf);
		}
	}
	return 0;
}
