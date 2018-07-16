//pipe第一个简单例程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;

    int ret = pipe(fd);
    if(ret == -1) {
	perror("pipe error");
	exit(1);
    }
    pid = fork();
    if(pid == -1) {
	perror("fork error");
	exit(1);
    } else if(pid == 0) { //子 读数据并打印到屏幕
	close (fd[1]);  //关闭写端

        //读数据
	char buf[1024];
	ret = read(fd[0], buf, sizeof(buf));
	if(ret == 0) { //开始读就到了文件末尾，没读到数据,返回0
	    printf("------\n");
	}

        //向屏幕打印
	write(STDOUT_FILENO, buf, ret);
    } else { //父 向管道写数据
	close(fd[0]); //关闭读端

	//写数据
	char data[] = "hello pipe\n";
	write(fd[1], data, strlen(data));
	sleep(1); //父进程后结束，保证打印清晰，shell掺和
    }

    return 0;
}
