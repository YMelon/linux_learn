//fifo实现没有血缘关系进程间通信，读数据进程

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

    //从fifo文件读数据
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
	perror("open error");
	exit(1);
    }

    char buf[512];
    while(1) {
	int len = read(fd, buf, sizeof(buf));
	buf[len] = 0; //读到的没有‘\0'吗？
	printf("buf = %s, len = %d\n", buf, len);
	//len=12,为什么？
    }

    close(fd);

    return 0;

}

