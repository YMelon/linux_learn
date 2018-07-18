//mmap()第一个例程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main() {
    int len = 4, ret;
    char* p = NULL;

    //打开要映射的文件
    int fd = open("test_mmap.txt", O_CREAT|O_RDWR, 0644);
    if(fd < 0) {
	perror("open error");
	exit(1);
    }
    ret = ftruncate(fd, len); //扩展文件为len字节大小
    if(ret == -1) {
	perror("ftruncate error");
	exit(1);
    }

    //将文件映射到内存
    p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED) {
	perror("mmap error");
	exit(1);
    }

    //向共享内存写数据
    strcpy(p, "abd");

    //关闭共享内存
    ret = munmap(p, len);
    if(ret == -1) {
	perror("munmap error");
	exit(1);
    }

    close(fd);

    return 0;
}
