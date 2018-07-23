//创建线程 例子

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//线程执行函数
void* thrd_func(void* arg) {
    printf("In thread: thread id = %lu, pid = %u \n", pthread_self(), getpid());
    return NULL;
}


int main() {
    pthread_t tid;
    int ret;
    
    //这里为什么可以使用pthread_self()
    //在这之前还没有创建线程 为什么可以获取线程id？
    printf("In main1: thread id = %lu, pid = %u \n", pthread_self(), getpid());
    
    //创建线程
    ret = pthread_create(&tid, NULL, thrd_func, NULL);
    if(ret != 0) {
	//打印错误描述
	fprintf(stderr, "pthread_create error: %s \n", strerror(ret));
	exit(1);
    }
    
    sleep(1); //等等 线程执行 不写的话线程来不及执行进程就退出了
    printf("In main2: thread id = %lu, pid = %u \n", pthread_self(), getpid());

    return 0;
}
