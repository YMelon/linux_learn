//子进程调用execl()执行自定义可执行程序

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if(pid == -1) {
	perror("fork error");
	exit(1);
    } else if(pid == 0) { //子进程
	//这里第一个参数用的是相对路径，也可以
	execl("./while", "while", NULL);
    } else { //父进程
	sleep(6);  //保证父进程最后退出,然后shell控制前台,防止输出混乱
	printf("parent \n");
    }

    return 0;
}
