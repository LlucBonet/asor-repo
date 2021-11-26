#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <fcntl.h>

void atributos(char *type){
	pid_t pid;
	struct rlimit rlim;

	pid = getpid();
	printf("(%s) ID del proceso actual: %i\n", type, pid);
	printf("(%s) ID del proceso padre: %i\n", type, getppid());
	printf("(%s) ID del grupo del proceso: %i\n", type, getpgid(pid));
	printf("(%s) ID de sesion: %i\n", type, getsid(pid));
	if(getrlimit(RLIMIT_NOFILE, &rlim) == -1)
		perror("Error en getrlimit");
	else
		printf("(%s) Número máximo de ficheros que puede abrir el proceso: %li\n", type, rlim.rlim_max);
	char *path = malloc(sizeof(char) * (4096+1));
	char *rpath = getcwd(path, 4096+1);
	printf("(%s) Directorio de trabajo actual: %s\n", type, path);
	free(path);
}

int main(int argc, char **argv){

	if(argc < 2){
		printf("Error: debe introducir el programa a ejecutar.\n");
	        return -1;	
	}
	pid_t pid = fork();

	switch(pid){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			if(setsid() == -1) perror("Error creando nueva sesión.");
			if(chdir("/tmp") == -1) perror("Error al cambiar el dir de trabajo");
			atributos("Hijo");
			
			int fd = open("/tmp/daemon.out", O_RDWR | O_CREAT, 0644);
			int fd2 = open("/tmp/daemon.err", O_RDWR | O_CREAT, 0644);
			int fd3 = open("/dev/null", O_RDWR | O_CREAT, 0644);
			if(fd == -1 | fd2 == -1 || fd3 == -1)
				perror("Error en open()");
			else{
				dup2(fd,1);
				dup2(fd2,2);
				dup2(fd3, 0);
				execvp(argv[1], argv+1);
			}
			close(fd);
			close(fd2);
			close(fd3);
			break;
		default:
			atributos("Padre");
			break;
	}
	return 0;
}
