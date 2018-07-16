//练习,将当前系统中进程信息打印到文件中

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd;
    fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd < 0) {
        perror("open ps.out error");
	exit(1);
    }
    //文件描述符拷贝，重定向
    dup2(fd, STDOUT_FILENO);
    //dup2(fd, 0);

    //注意，exec()只要调用成功就不会返回，所以下面语句是不会执行的，借助os隐式回收fd
    execlp("ps", "ps", "ax", NULL);
    //close(fd);

  /*据exec()族函数特征，对此函数错误处理,放在exec函数之后
    perror("exec error");
    exit(1);
  */

    return 0;
}
