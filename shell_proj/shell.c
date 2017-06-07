/* Progam: shell.c 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */


char *current_dir = "./"; /* The current working directory */

int read_input(char *);
void parse_command(char*, char**);

int main(void)
{
	char *args[MAX_LINE/2 + 1]; /* Command line arguments */
	int shouldrun = 1; /* flag to determine when to exit program */
	char *command;
	int background;
	pid_t pid;
	int status;

	while (shouldrun) {
		printf("myshell>");
		fflush(stdout);

		background = read_input(command);// read the user input

		if(strcmp("exit", command) < 0){
			exit(0);	// if the user entered exit then the shell closes
		}
		pid = fork();
		if(pid== 0){ // execute command
			args[0] = "./cf";
			args[1] =  "test.c";
			//args[2] = "./cf"
			args[2] = "./";
			args[3] = NULL;
			
			execvp(args[0], args);
		}
		else{
			if(!background){
				wait(&status);		
			}		
		}
	
	}

	return 0 ;
}

int read_input(char * command){
	int background = 0;
	char c = ' ';
	while(c != '\n' && c != EOF){
		c = getchar();
		*command = c;
		command++;
	}
	command-=2;
	if(*command = '&'){
		background  = 1;
		command++;
	}
	*command = '\0';
}

void parse_command(char *command, char* args[]){
	char *c = command;
	int i = 0;
	while(*c != '\0'){
		if (*c == ' ')
		{
			i++;
		}
		*args[i]++ = *c++;
	}

	i++;
	args[i] = *current_dir;
	args[i+1] = NULL;
}
