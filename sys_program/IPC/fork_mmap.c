//父子进程间通过mmap进行通信

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

//全局变量，用于验证父子进程独享
int var = 100;

int main() {
    int* p = NULL;
    pid_t pid;

    //打开用于映射的文件
    int fd = open("temp.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd == -1) {
	perror("open error");
	exit(1);
    }
    unlink("temp.txt"); //删除临时文件目录项,使之具备被释放条件,等占用此文件的所有进程结束 文件被释放
    ftruncate(fd, 4);

    //共享映射
    p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    //private私有映射 父子进程各自独占映射区 不能通信
    //p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(p == MAP_FAILED) {
	perror("mmap error");
	exit(1);
    }
    close(fd);   //映射区建立完毕,即可关闭文件

    //父子进程通信
    pid = fork();
    if(pid == -1) {
	perror("fork error");
	exit(1);
    } else if(pid == 0) { //子进程对映射区写入
	*p = 2000;
	var = 1000;
	printf("Child, *p = %d, var = %d\n", *p, var);
    } else { //父 读 回收 释放
	sleep(1); //等待子进程写完
	//考察父子进程共享什么,独享什么
	printf("Parent, *p = %d, var = %d\n", *p, var);
        
	//回收
	wait(NULL);
        
	//释放映射区
	int ret = munmap(p, 4);
	if(ret == -1) {
	    perror("munmap error");
	    exit(1);
	}
    }

    return 0;
}

