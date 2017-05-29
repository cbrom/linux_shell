#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int args, char* argv[]){
        int fd1, fd2, nr;
        char* file1;
        char* buffer;
        size_t len_buffer = 4096;
        if(args !=2){
                printf("Please enter a valid command!!!/nuse hlp for help");
        }
        else{
                file1 = argv[1];
                //create file
                fd1 = open(file1, O_RDONLY);
                ssize_t len_read = read(fd1, *buf, len_buffer);
                if (fd == -1){
                        printf("Error in openning/reading %s file\n", file1);
                        exit(1);
                }
		printf("%s\n", buff);
                close(fd1);
        }
        exit(0);
}
