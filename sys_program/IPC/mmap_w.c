//非血缘关系进程间利用mmap进行通信 写数据进程

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

struct STU {
    int id;
    char name[20];
    char sex;
};

//自己封装了出错处理函数
void sys_err(char* str) {
    perror(str);
    exit(-1);
}


int main(int argc, const char* argv[]) {
    int fd;
    struct STU student = {10, "Thompson", 'm'};
    char* mm;
    
    //程序使用错误处理 通过命令行参数获取用于创建映射区的文件
    if(argc < 2) {
	printf("./a.out file_shared.txt\n");
	exit(-1);
    }
    
    //打开用于映射的文件
    //提前在同一目录下准备好文件,大小要大于结构体
    fd = open(argv[1], O_RDWR);
    if(fd == -1)
	sys_err("open error");

    mm = mmap(NULL, sizeof(student), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(mm == MAP_FAILED)
	sys_err("mmap error");
    close(fd);

    //向映射区写数据
    while(1) {
	memcpy(mm, &student, sizeof(student));
	student.id ++;
	sleep(1);
    }
    
    //释放
    munmap(mm, sizeof(student));

    return 0;
}
