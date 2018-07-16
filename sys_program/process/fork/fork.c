//演示孤儿进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid == -1){
       perror("fork error");
       exit(1);
    }else if(pid == 0) {
        printf("child pid = %u, parent pid = %u \n", getpid(), getppid() ); 
	sleep(3); //确保比父进程晚结束
        printf("child pid = %u, parent pid = %u \n", getpid(), getppid() ); 
    }else {
	//让子进程先打印
	sleep(1);
        printf("I'm parent. pid = %u \n", getpid());        
    }

    return 0;
}
