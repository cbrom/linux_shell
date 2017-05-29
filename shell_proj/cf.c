#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int args, char* argv[]){
	int fd;
	if(args !=2){
		printf("Please enter a valid command!!!/nuse hlp for help");
	}
	else{
		//create file
		fd = creat(argv[1], 0777);
		if (fd == -1)
			printf("Error in creating %s file\n", argv[1]);
		else{
			printf("%s file was created.\n", argv[1]);
		}
	}
	exit(0);
}
