//fifo实现没有血缘关系进程间通信，写数据进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    //错误处理
    if(argc < 2) {
	printf("./a.out fifoname\n");
	exit(1);
    }

    //检查fifo文件是否存在
    int ret = access(argv[1], F_OK);
    if(ret == -1) {
	int r = mkfifo(argv[1], 0664);
	if(r == -1) {
	    perror("mkfifo error");
	    exit(1);
	}
	printf("有名管道%s创建成功\n", argv[1]);
    }

    //向fifo文件写数据
    int fd = open(argv[1], O_WRONLY);
    if(fd == -1) {
	perror("open error");
	exit(1);
    }

    char* p = "hello world";
    while(1) {
	sleep(1); //故意慢点写,验证fifo是阻塞的
	int len = write(fd, p, strlen(p)+1);
	//strlen()+1？
    }

    close(fd);

    return 0;

}

