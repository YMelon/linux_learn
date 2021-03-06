//循环创建N个子进程架构

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    int n = 5; //创建子进程个数，默认5个
    pid_t pid;

    
    for(i = 0; i < n; i ++) { //出口1，父进程出口
        pid = fork();

        if(pid == -1) {
            perror("fork error");
	    exit(1);
	} else if(pid == 0) {
	    break;         //出口2，子进程出口,i不自增 
	} else {
	} 
    }

    if(i < n) { //子进程执行
	sleep(i);
	printf("I'm %dth child, pid = %u \n", i+1, getpid());
    } else {   //父进程执行
        sleep(i);
	printf("I'm parent, pid = %u \n", getpid());
    }

    return 0;
}
