#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

void atributos(char* type){
	pid_t pid;
        struct rlimit rlim;
	pid = getpid();
	printf("(%s) ID del proceso actual: %i\n", type, pid);
	printf("(%s) ID del proceso padre: %i\n", type, getppid());
	printf("(%s) ID del grupo del proceso: %i\n", type, getpgid(pid));
	printf("(%s) ID de sesion: %i\n", type, getsid(pid));
	if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
		perror("Error en getrlimit");
	}
	printf("(%s) Número máximo de ficheros que puede abrir el proceso: %li\n", type, rlim.rlim_max);
	char *path = malloc(sizeof(char)*(4096+1));
	char *rpath = getcwd(path, 4096 + 1);
	printf("(%s) Directorio de trabajo actual: %s\n", type, path);
	free(path);
}

int main(){
	pid_t pid = fork();
	switch(pid){
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			if(setsid() == -1) perror("Error creando nueva sesión.");
			if(chdir("/tmp") == -1) perror("Error cambiando el dir");
			printf("Hijo %i (padre: %i)\n", getpid(), getppid());
		        atributos("Hijo");
			break;
		default:
			printf("Padre %i (hijo: %i)\n", getpid(), pid);
			//sleep(3);
			atributos("Padre");
			break;
	}
	return 0;
}

//Si el proc. padre termina antes que el hijo, este se queda huérfano y el ppid lo recoge la shell o init.
//Si el proc. hijo termina antes que el padre, si se muestran los procesos en consola comprobamos que aparece "<defunct>" al lado de la descripción del proceso. 
