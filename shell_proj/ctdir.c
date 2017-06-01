#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX 10485760 // 10MB

char *description = "This will create a directory in the given path.\nUSAGE: ctdir [path]<directory>\n";

int main(int argc, char *argv[]){
	char *dir;
	int result;
	struct stat st = {0};
	{
		
	};
	if(argc == 2){
		
		dir = argv[1];
	}
	else if (argc == 1)
	{
		printf("%s\n", description);
	}
	else{
		printf("USAGE: ctdir [path]<directory>\n");
		exit(0);
	}
	if (stat(dir, &st) == -1)
	{
		result = mkdir(dir, 0700) ;
		if(result == -1){
			printf("Error creating directory\n");
			exit(1);
		}
	}
	
	return 0;
}
