#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int args, char* argv[]){
        int fd1, fd2, nr;
	char* file1, file2;
	char* buffer;
	size_t len_buffer = 4096;
        if(args !=3){
                printf("Please enter a valid command!!!/nuse hlp for help");
        }
        else{
		file1 = argv[1];
		file2 = argv[2];
                //create file
		fd1 = open(file1, O_RDONLY);
                ssize_t len_read = read(fd1, *buf, len_buffer);
                if (fd == -1){
                        printf("Error in openning %s file\n", file1);
			exit(1);
		}
		fd2 = open(file2, O_CREAT | O_WRONLY);
		if(fd2 == -1){
			printf("Error creating file %s file\n", file2);
			exit(1);
		}
		nr = write(fd2, buffer, strlen(buffer));
		if(nr == -1)
			printf("There was an error wrting to %s\n", file2;

                close(fd1);
		close(fd2);
        }
        exit(0);
}

