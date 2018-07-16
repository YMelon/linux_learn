//同fork.c 演示孤儿进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if(pid == 0) {
	while(1) {
	    sleep(1); //让父进程先打印
	    printf("I'm child, my parent pid = %d \n", getppid());
	}
    } else if(pid > 0) {
	printf("I'm parent, my pid = %d \n", getpid());
	sleep(5);
	printf("------parent going to end------ \n");
    } else {
	perror("fork error");
	exit(1);
    }

    return 0;
}

