//程序中调用kill函数 自己杀死自己
//父进程给第三个子进程发送信号

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/*
//1.自己杀死自己
int main() {
    int ret = kill(getpid(), SIGKILL);
    if(ret == -1) {
	exit(1);
    }

    return 0;
}
*/

//2.给三号子进程发送信号
int main() {
    int i;
    int n = 5; //创建子进程个数，默认5个
    pid_t pid, q;
    pid_t wpid;
    
    for(i = 0; i < n; i ++) { //出口1，父进程出口
        pid = fork();
        if(pid == -1) {
            perror("fork error");
	    exit(1);
	} else if(pid == 0) {
	    break;         //出口2，子进程出口
	} else if(i == 2) {
	    q = pid;
	}
    }

    if(i < n) { //子进程执行
	printf("I'm %dth child, pid = %u \n", i+1, getpid());
	sleep(10);
    } else {   //父进程执行
        sleep(1); //让子进程先输出 
	int ret = kill(q, SIGKILL);
	if(ret == -1) {
	    perror("kill error");
	    exit(1);
	}
	printf("I'm parent, killed pid = %d\n", q);
        
	//回收
	do {
	    wpid= waitpid(-1, NULL, WNOHANG);
	    sleep(1);
	} while(wpid != -1);

    }

    return 0;
}
