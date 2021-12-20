#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 4

int process(int clisd, struct sockaddr_storage *addr, socklen_t addrlen);

int main(int argc, char **argv){
	if(argc != 3){
		printf("Usage: %s <address> <port>\n", argv[0]);
		return -1;
	}
	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	int rc, sd;

	if((rc = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1){
		perror("Error en getaddrinfo()\n");
		return -1;
	}

	if((sd = socket(res->ai_family, res-> ai_socktype, 0)) == -1){
		perror("Error en socket()\n");
		return -1;
	}

	if((rc = bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) == -1){
		perror("Error en bind()\n");
		return -1;
	}

	freeaddrinfo(res);
	
	if((rc = listen(sd, 5)) == -1){
		perror("Error en listen()\n");
		return -1;
	}

	for(int i = 0; i < N; i++){
		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof(addr);

		int clisd = accept(sd, (struct sockaddr *) &addr, &addrlen);
		if(clisd == -1){
			perror("Error en accept()\n");
			return -1;
		}
		
		pid_t pid = fork();

		if(pid == -1){
			perror("Error en fork()\n");
			return -1;
		}
		if(pid == 0){
			rc = process(clisd, &addr, addrlen);
			return rc;
		}
		else 
			close(clisd);
	}

	while(wait(NULL) > 0);
	return 0;
}

int process(int clisd, struct sockaddr_storage *addr, socklen_t addrlen){
	char host[NI_MAXHOST], serv[NI_MAXSERV];
	int rc = getnameinfo((struct sockaddr *) addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	
	if(rc == -1){
		perror("Error en getnameinfo()\n");
		return -1;
	}

	printf("Serv PID: %d -> Conexión desde %s:%s\n", getpid(), host, serv);
	char buf[80];
	int bytes = recv(clisd, buf, sizeof(buf), 0);

	if(bytes == -1){
		perror("Error en recv()\n");
		return -1;
	}

	while(bytes > 0){
		buf[bytes] = '\0';
		int sent = send(clisd, buf, bytes, 0);
		if(sent == -1){
			perror("Error send()\n");
			return -1;
		}
		bytes = recv(clisd, buf, sizeof(buf), 0);
		if(bytes == -1){
			perror("Error en recv()\n");
			return -1;
		}
		
	}
	printf("Conexión terminada. Serv PID: %d\n", getpid());
	close(clisd);
	return 0;
}
