#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv){

	if(argc < 2){
		perror("Se necesita un comando como argumento.\n");
		return -1;
	}

	int fd = open("tuberia3", O_WRONLY);

	if(fd == -1){
		perror("Error abriendo tubería.\n");
		return -1;
	}

	write(fd, argv[1], strlen(argv[1])+1);
	
	close(fd);

	return 0;
}
