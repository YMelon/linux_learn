//守护进程 例子

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    pid_t pid, sid;
    int ret;
    pid = fork();
    if(pid > 0) { //父进程退出
	return 0;
    }

    //子进程
    sid = setsid(); //建立会话
    ret = chdir("/"); //改变工作目录
    if(ret == -1) {   //这个函数容易调用出错 要判断下
	perror("chdir error");
	exit(1);
    }

    umask(0002);  //设置文件掩码
    
    //把0,1,2文件描述符都重定向到/dev/null
    close(STDIN_FILENO);
    open("/dev/null", O_RDWR); //返回文件描述符为0
    dup2(0, STDOUT_FILENO);
    dup2(0, STDERR_FILENO);

    //守护进程工作
    while(1) {

    }

    return 0;
}
