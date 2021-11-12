#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <linux/limits.h>


int main(int argc, char **argv) {
	DIR * dir;
	struct dirent * entry;
	int buf_size;
	char path[PATH_MAX];
	int total_size = 0;
	

	if(argc != 2) {
		perror("Error. Debe proporcionar la ruta de un directorio.\n");
		return -1;
	}	
	 
	if((dir = opendir(argv[1])) == NULL){
		perror("Eror al abrir el directorio.\n");
		return -1;
	  }
	  while((entry = readdir(dir)) != NULL){
		if(entry->d_type == DT_REG) { 
			printf("%s\n", entry->d_name); 
			total_size += entry->d_reclen;
		}
		if(entry->d_type == DT_DIR) { printf("%s/\n", entry->d_name); }
		if(entry->d_type == DT_LNK) { 
			if((buf_size = readlink(entry->d_name, path, PATH_MAX)) == -1){
				perror("Error al leer el enlace simbólico.\n");
				return -1;
			}		
			path[buf_size] = '\0';
			total_size += entry->d_reclen;	
			printf("%s -> %s\n", entry->d_name, path); 
		}
	}
	printf("Tamaño total: %d kB\n", total_size);
	closedir(dir);
	return 1;
}
