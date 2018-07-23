//循环创建N个子线程 例子
//及错误传参示例分析

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//线程执行函数
void* thrd_func(void* arg) {
    int i = (int)arg; //这里void* 转化为int 理解一下
    //int i = *((int*)arg); //传过来的是地址 解引用取值
    
    sleep(i); //保证子线程输出的顺序
    printf("%dth thread: thread id = %lu, pid = %u \n", i+1, pthread_self(), getpid());

    return NULL;
}


int main() {
    pthread_t tid;
    int ret, i;
    for(i = 0; i < 5; i++) {
        ret = pthread_create(&tid, NULL, thrd_func, (void*)i);
	//ret = pthread_create(&tid, NULL, thrd_func, (void*)&i); //i 传地址过去 错误 结果不确定 分析
        
	if(ret != 0) {
	    //打印错误描述
	    fprintf(stderr, "pthread_create error: %s \n", strerror(ret));
	    exit(1);
        }
    } 
    
    sleep(i); //等等 线程执行 不写的话线程来不及执行进程就退出了

    return 0; //进程退出
}
