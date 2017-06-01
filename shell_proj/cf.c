#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

char *description = "This will allow you to create files\nUSAGE: cf <filename> [directory]\n";

int main(int argc, char *argv[]){
	char *filename;
	int fd;
	if(argc == 2){
		filename = argv[1];
	}
	else if(argc == 3){
		filename = argv[2];
		strcat(filename, "/");
		strcat(filename, argv[1]);
	}
	else if (argc == 1)
	{
		printf("%s\n", description);
		exit(1);
	}
	else{
		printf("USAGE: cf <filename> [directory]\n");
		exit(0);
	}
	
	fd = creat(filename, 0766);
	if(fd == -1){
		printf("Error creating file, check if the directory exists\n");
	}
	close(fd);
	
	
	
	return 0;
}
