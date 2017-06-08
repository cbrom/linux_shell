#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define RL_BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

int sh_touch(char **args);
int sh_cp(char **args);

void usage(const char *myname);
int sh_mkdir(char **args);
int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
int sh_cat(char **args);

void loop(void);
char *read_line(void);
char **parse_line(char *line);
int launch(char **args);

int main(int argc, char **argv)
{
  loop();
  // Perform any shutdown/cleanup.
  return EXIT_SUCCESS;
}

void loop(void){
  char *line;
  char **args;
  int shouldrun = 1;

  while(shouldrun){
    printf("shell$>");
    line = read_line();
    args = parse_line(line);
    shouldrun = execute(args);

    free(line);
    free(args);
  }
}

char *read_line(void){
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}

char **parse_line(char *line){
  int bufsize = TOKEN_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "sh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TOKEN_DELIMITERS);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += TOKEN_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOKEN_DELIMITERS);
  }
  tokens[position] = NULL;
  return tokens;
}

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = { 
  "cf",
  "cpf",
  "ctdir",
  "chgdir",
  "display",
  "hlp",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &sh_touch,
  &sh_cp,
  &sh_mkdir,
  &sh_cd,
  &sh_cat,
  &sh_help,
  &sh_exit
};

int sh_num_builtins(){
  return sizeof(builtin_str) /sizeof(char *);
}

/*
  Builtin functions
*/
int sh_touch(char **args){
	pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    char *command = malloc(100 * sizeof(char*));
    strcpy(command, "./");
    command = strcat(command, args[0]);

    if (execvp(command, args) == -1) {
      perror("sh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("sh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int sh_cp(char **args){
   char *cmd[1024] = {"cp",args[1],args[2]};
   execvp(cmd[0],cmd); 
  return 1;
}
 
int sh_mkdir(char **args){
	if(args[1] != NULL && args[2] == NULL){
		char *cmd[1024] = {"mkdir",args[1]};
		execvp(cmd[0],cmd);
		return 1;
	} else if(args[1] !=NULL && args[2] != NULL){
	   strcat(args[2],"/");
	   strcat(args[2],args[1]);
	   char *cmd[1024] = {"mkdir",args[2]};
	   execvp(cmd[0],cmd);
	   return 1;

	} else{
		wait(NULL);
	}
	return 1;
}

int sh_cd(char **args){
	if (args[1] == NULL) {
		fprintf(stderr, "sh: expected argument to \"chgdir\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("Error");
		}
	}
	return 1;
}

int sh_cat(char **args){
	int fd,i,argc;
	char buf[600];
	fd=open(args[1],O_RDONLY,0777);
	if(fd==-argc){
		printf("file open error");

	}else{
		while((i=read(fd,buf,1))>0){
			printf("%c",buf[0]);
		}
  		close(fd);
	}
    return 1;
}

int sh_help(char **args){
  int i; 
  if(args[1] != NULL){
     if(strcmp(args[1],"chgdir")==0){
         printf("chgdir is a command used to change directory\n");
         printf("you can change the current directory as follows\n");
         printf("   chgdir directoryName\n");
	}else if(strcmp(args[1],"display")==0){
	       	printf("display is a command used to display te content of the file given\n");
	        printf("you can display the file as follows\n");
	        printf("   display fileName\n");

	}else if(strcmp(args[1],"cf")==0){
	        printf("cf is a command used to create a file\n");
	        printf("you can create the file as follows\n");
	        printf("   cf fileName\n");

	}else if(strcmp(args[1],"cpf")==0){
	        printf("cpf is a command used to copy a file from one destination to another\n");
	        printf("you can copy a file as follows\n");
	        printf("   cpf source destination\n");

	}else if(strcmp(args[1],"ctdir")==0){
	        printf("ctrdir is a command used to make a directory\n");
	        printf("you can make the directory as follows\n");
	        printf("   ctdir directoryName\n");

	}else if(strcmp(args[1],"hlp")==0){
	        printf("hlp is a command used to display help to commands\n");
	        printf("you can display the help as follows\n");
	        printf("   hlp commandName\n");

	}else{
	        printf("Error : You inserted undefined command\n");
	}
	}
	else{
	    printf("this is a help command which is used to display help to the following commands\n");
	    for (i = 0; i < sh_num_builtins(); i++) {
	    printf("  %s\n", builtin_str[i]);
	  }
	   printf("you can use this command with command arguments to display help foreach of the commands as follows\n");
	   printf("   hlp commandName\n  ");
	   printf("Use the man command for information on other programs.\n");
	} return 1;
}

int sh_exit(char **args)
{
  return 0;
}

int execute(char **args){
  int i;
  if (args[0] == NULL) {
    // An empty command
    return 1;
  }

  for (i = 0; i < sh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      // make a call here
      pid_t pid, wpid;
      int status;

      pid = fork();
      if (pid == 0) {
        // Child process
        char *command = malloc(100 * sizeof(char*));
        strcpy(command, "./");
        command = strcat(command, args[0]);

        if (execvp(command, args) == -1) {
          perror("sh");
        }
        exit(EXIT_FAILURE);
      } else if (pid < 0) {
        // Error forking
        perror("sh");
      } else {
        // Parent process
        do {
          wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
      }

      return 1;
    }
  }

  return launch(args);
}

int launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("sh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("sh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


void usage(const char *myname){
	printf("\nUsage: %s <pathname> [<mode>]\n\n", myname);
	exit(1);
}
