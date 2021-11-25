#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	pid_t pid = getpid();
	struct rlimit rlim;
	printf("ID del proceso actual: %i\n", pid);
	printf("ID del proceso padre: %i\n", getppid());
	printf("ID del grupo del proceso: %i\n", getpgid(pid));
	printf("ID de sesión: %i\n", getsid(pid));
	if(getrlimit(RLIMIT_NOFILE, &rlim) == -1){
		perror("Error en getrlimit");
		return -1;
	}
	printf("Número máximo de ficheros que puede abrir el proceso: %li\n", rlim.rlim_max);

	char *path = malloc(sizeof(char)*(4096 + 1));
	char *rpath = getcwd(path, 4096 + 1);
	printf("Directorio de trabajo actual: %s\n", path);
	free(path);

	return 0;
}
