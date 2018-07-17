//使用函数测试pipe 缓冲区大小

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];

    int ret = pipe(fd);
    if(ret == -1) {
	perror("pipe error");
	exit(1);
    }
    
    //第一个参数传fd[0]或fd[1]都可以 对应的都是同一缓冲区
    long size = fpathconf(fd[0], _PC_PIPE_BUF);
    printf("pipe size = %ld\n", size);

    return 0;
}
