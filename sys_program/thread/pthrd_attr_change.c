//设置线程属性 修改线程栈空间
//修改SIZE大小运行观察结果
//注:SIZE太小或太大都会导致修改失败 恢复默认栈空间来创建线程

#include "mythread.h"

//申请堆空间大小 十六进制
#define SIZE 0x1000000

void* tfn(void* arg) {
    //保证线程不会退出
    while(1)
	sleep(2);
}

int main() {
    pthread_t tid;
    int err, detachstate, i = 1;
    pthread_attr_t attr;
    size_t stacksize; //size_t unsigned int
    void* stackaddr;
    
    //初始化线程属性 并获取默认栈空间和分离信息
    pthread_attr_init(&attr);
    pthread_attr_getstack(&attr, &stackaddr, &stacksize);
    pthread_attr_getdetachstate(&attr, &detachstate);
    //打印线程分离属性
    if(detachstate == PTHREAD_CREATE_DETACHED)
	printf("thread detached\n");
    else if(detachstate == PTHREAD_CREATE_JOINABLE)
	printf("thread joinable\n");
    else
	printf("thread unknown\n");

    //设置线程属性分离
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while(1) {
	//在堆上申请内存,指定线程栈的起始地址和大小
	stackaddr = malloc(SIZE);
	if(stackaddr == NULL) {
	    perror("malloc error");
	    exit(1);
	}
	stacksize = SIZE;
	pthread_attr_setstack(&attr, stackaddr, stacksize);

	//创建线程
	err = pthread_create(&tid, &attr, tfn, NULL);
	if(err != 0) {
	    fprintf(stderr, "pthread_create error: %s\n", strerror(err));
	    exit(1);
	}
	printf("%d\n", i++); //打印成功创建线程数量
    }
    //销毁 对应pthread_attr_iniy()
    pthread_attr_destroy(&attr);

    return 0;
}









