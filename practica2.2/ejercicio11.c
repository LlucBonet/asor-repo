#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


int link(const char *oldpath, const char *newpath);
int symlink(const char *target, const char *linkpath);

int main(int argc, char **argv){
	struct stat buf;
	mode_t mode;

	if(stat(argv[1], &buf) == -1){
		perror("Error. Modo de uso: ./ejercicio11 ruta");
		return -1;
	}	
	else{
		mode = buf.st_mode;
		char hard[strlen(argv[1]) + strlen(".hard")];
		char sym[strlen(argv[1]) + strlen(".sym")];
		
		strcat(strcpy(hard, argv[1]), ".hard");
		strcat(strcpy(sym, argv[1]), ".sym");
		
		if(S_ISREG(mode)){
			if(link(argv[1], hard) == -1){
				perror("Error en la creación del enlace rígido.");
				return -1;
			}	
			if(symlink(argv[1], sym) == -1){
				perror("Error en la creación del enlace simbólico.");
				return -1;
			}
		}
		else {
			perror("La ruta especificada debe ser un fichero regular.");
			return -1;
		}
		return 1;
	}
}
