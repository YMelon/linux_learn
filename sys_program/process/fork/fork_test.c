//fork()的第一个例程序

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    printf("before fork:xxxxxxxxxx \n");

    pid = fork();
    if(pid == -1){
       perror("fork error");
       exit(1);
    }else if(pid == 0) {
        printf("I'm child. pid = %u, ppid = %u \n", getpid(), getppid() ); 
    }else {
        printf("I'm parent. pid = %u, ppid = %u \n", getpid(), getppid() );        sleep(1);//不加这个语句，执行结果解释？
    }

    printf("YYYYYYYYYY \n");

    return 0;
}
