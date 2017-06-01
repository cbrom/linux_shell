#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAX 10485760 //10MB

char *description = "This program will list the current running process\nUSAGE: pslist \n";

int main(int argc, char *argv[]){
	int fd;
	if(argc != 1){
	{
		printf("%s\n", description);
		exit(0);
	}

	DIR *proc = opendir("/proc");
	struct dirent* ent;
	long tgid;

	if (proc == NULL)
	{
		printf("Error\n");
	}
	while(ent = readdir(proc)){
		if (!is_digit(*ent->d_name))
		{
			continue;
		}
		
	}
	
	return 0;
}
