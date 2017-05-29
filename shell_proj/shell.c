#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define MAXLINE 80
#define current_directory "dir"
char ** parse(char* user_input);

int main(int args, char* argv[]){
	char * args[MAXLINE/ 2 + 1]; /* command line arguments */
	int shouldrun = 1; /* flag to determine to exit program*/
	//while loop prompt for commands
	while(shouldrun){
		//
		printf("myshell>>");
		fflush(stdout);
		scanf("%s", args); //read input from user
		//parse user input
		
		//execute user command or print an error
	}
	
	return 0;
}


char** parse(char* user_input){
	//return char
}
