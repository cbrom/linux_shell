#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAX 10485760 // 10MB

char *description = "This will display a file in the given path.\nUSAGE: display <filename>\n";

int main(int argc, char *argv[]){
        char *file, *buff;

        int fd;

        if(argc == 2){
                file = argv[1];
        }
        else if (argc == 1)
        {
                printf("%s\n", description);
        }
        else{
                printf("USAGE: display <filename>\n");
                exit(0);
        }

        fd = open(file, O_RDONLY);
        
        if(fd == -1){
                printf("Error displaying file, check if you have read permissions\n");
                exit(0);
        }

        ssize_t s = read(fd, buff, MAX);
        if(s == -1){
                printf("error 1\n");
                exit(0);
        }
        close(fd);      
        printf("%s\n", buff);
        
        return 0;
}
