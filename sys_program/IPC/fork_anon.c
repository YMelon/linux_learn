//父子进程间通过匿名映射区mmap进行通信
//Linux下两种创建匿名映射区的方法

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

    //1.Linux下特有宏MAP_ANON创建共享匿名映射区
    p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    //2.类Unix的创建方法 Linux下也可以用
    //int fd = open("/dev/zero", O_RDWR); //这里省略判断文件打开失败代码
    //p = (int*)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED) {
	perror("mmap error");
	exit(1);
    }

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

