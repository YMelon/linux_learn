//演示僵尸进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if(pid > 0) {
	while(1) {
	    printf("I'm parent, my pid = %d, my son = %d \n", getpid(), pid);
	    sleep(1);
	}
    } else if(pid == 0) {
	printf("------I'm child, my parent pid = %d , going to sleep 10s\n", getppid());
	sleep(10);
	printf("------child end------ \n");
    } else {
	perror("fork error");
	exit(1);
    }

    return 0;
}

