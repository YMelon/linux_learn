//演示wait()回收子进程；及获取子进程结束状态的四个重要宏函数

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, wpid;
    int status;
    pid = fork();
    if(pid == 0) {
	//3-2.子进程自身出现运行异常状态
	execl("./abnor.out", "abnor.out", NULL);

	printf("------I'm child, my parent pid = %d , going to sleep 10s\n", getppid());
	//sleep(10);
	//3-1.设置足够时间，在终端手动kill掉子进程,验证wait获取子进程异常结束状态
	sleep(60);
	printf("------child end------ \n");

	//用于验证wait获取子进程结束状态，设定退出值,return也可以
	exit(76);
    } else if(pid > 0) {
	/*
	//1.wait()简单回收子进程，这里我先不关心子进程状态，传NULL参数
	wpid = wait(NULL);
	if(wpid == -1) {
	    perror("wait error");
	    exit(1);
	} */
        
	//2.获取子进程结束状态,子进程正常结束情况，使用下面两个宏函数
	wpid = wait(&status);
	if(wpid == -1) {
	    perror("wait error");
	    exit(1);
	}
	if(WIFEXITED(status)) {
	    printf("child exit with %d \n", WEXITSTATUS(status));
	}

        //3.子进程异常结束，使用这两个宏函数,
	if(WIFSIGNALED(status)) {
	    printf("child killed by %d \n", WTERMSIG(status));
	}

	while(1) {
	    printf("I'm parent, my pid = %d, my son = %d \n", getpid(), pid);
	    sleep(1);
	}
    } else {
	perror("fork error");
	exit(1);
    }

    return 0;
}

