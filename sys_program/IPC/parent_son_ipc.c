//使用pipe,父子进程间通信,实现ps aux | grep "bash"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[2];
    int ret;
    pid_t pid;

    ret = pipe(fd);
    if(ret == -1) {
	perror("pipe error");
	exit(1);
    }

    pid = fork();
    if(pid == -1) {
	perror("fork error");
	exit(1);
    } else if(pid > 0) { //父 ps aux
	close(fd[0]);

	//ps 默认输出到stdout,重定向到管道写端
	dup2(fd[1], STDOUT_FILENO);
	execlp("ps", "ps", "aux", NULL);
    } else { //子 grep "bash"
	close(fd[1]);

	//grep 默认由stdin传数据,重定向到管道读端
	dup2(fd[0], STDIN_FILENO);
	execlp("grep", "grep", "bash", NULL);
	//和终端一致，输出有颜色
	//execlp("grep", "grep", "--color=auto", "bash", NULL);
    }

    return 0;
}
