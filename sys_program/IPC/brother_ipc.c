//使用pipe,兄弟进程间通信,实现ps aux | grep "bash"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int ret;
    pid_t pid, wpid;
    
    //创建管道
    ret = pipe(fd);
    if(ret == -1) {
	perror("pipe error");
	exit(1);
    }
    
    //创建两个子进程
    int i;
    for(i = 0; i < 2; i++) {
	pid = fork();
	if(pid == -1) {
	    perror("fork error");
	    exit(1);
	} else if(pid == 0) {
	    break;
	}
    }
    
    //子进程间IPC
    if(i == 0) { //子进程1 ps aux
	close(fd[0]);

	dup2(fd[1], STDOUT_FILENO);
	execlp("ps", "ps", "aux", NULL);
    } 
    if(i == 1) { //子进程2 grep "bash"
	close(fd[1]);

	dup2(fd[0], STDIN_FILENO);
	execlp("grep", "grep", "bash", NULL);
    }

    //父进程 回收子进程
    if(i == 2) {
	//注意关闭管道两端 父进程不用
	close(fd[0]);
	close(fd[1]);

	do {
	    wpid = waitpid(-1, NULL, WNOHANG);
	    if(wpid > 0)
		printf("child end, pid = %d\n", wpid);

	    sleep(1);
	} while(wpid != -1);
    }

    return 0;
}
