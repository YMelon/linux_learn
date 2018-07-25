//线程分离函数 例子
//并观察在线程分离状态下对线程进行回收 发生的错误

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* tfn(void* arg) {
    int n = 3;
    while(n--) {
	printf("thread count %d\n", n);
	sleep(1);
    }

    pthread_exit((void*)1);
}

int main() {
    pthread_t tid;
    void* ret;
    int err;

    pthread_create(&tid, NULL, tfn, NULL);
    pthread_detach(tid); //设置线程分离
    //不设置分离状态 运行观察
    //pthread_detach(tid);
    
    //线程分离状态下 对线程进行回收 
    //错误验证
    while(1) {
	err = pthread_join(tid, &ret);
	//打印错误号
	printf("------err = %d\n",err);
	//注意strerror函数使用
	//向标准错误打印 stderr？
	//join成功返回0 非0说明失败
	if(err != 0)
	    fprintf(stderr, "thread_join error: %s\n", strerror(err));
	else
	    fprintf(stderr, "thread exit code %d\n", (int)ret);

	sleep(1);
    }

    return 0;

}
