#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#include <sys/shm.h>
#include <sys/ipc.h>

int sh_memory_get();
int directory_exists(char*);

char *data, *sh_data;

int main(int argc, char *argv[]){
	int ret = sh_memory_get();
	printf("current directory: %s\n", data);
	printf("changin to %s\n", argv[1]);
	char* appended= sh_data;
	strcat(appended, "/");
	strcat(appended, argv[1]);
	printf("appended: %s\n", appended);

	if (argv[1] == ".."){
		//back
	}
	else if(argv[1] == "/"){
		//home
	}

	if(directory_exists(argv[1]) == 1){
		//full path
		strcpy(sh_data, argv[1]);
		return 0;
	}else if(directory_exists(appended) == 1){
		//local path
		strcpy(sh_data, appended);
		return 0;
	}
		
	shmdt(sh_data);
	return 0;
}

int directory_exists(char* directory){
	const char* folderr;
    struct stat sb;

    if (stat(directory, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        printf("YES\n");
        return 1;
    }
    else
    {
        printf("NO\n");
        return 0;
    }
}

int sh_memory_get(){
	int shmid;
	key_t key;
	char cwd[1024];
	data = malloc(1024 * sizeof(char));
	key = 5678;

	shmid = shmget(key, sizeof(cwd), IPC_CREAT | 0666);
	if (shmid == -1){
	printf("Failed to create memory segment");
	return 0;
	}

	sh_data = shmat(shmid, NULL, 0);
	strcpy(data, sh_data);

	if (data == (char*) -1){
		printf("Failed to attatch memory");
		return 0;
	}
	return 1;

}