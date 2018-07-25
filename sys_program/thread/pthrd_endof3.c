//杀死线程 注意取消点 
//注意:线程被杀死的退出值为-1

#include "mythread.h"

void* tfn1(void* arg) {
    printf("thread 1 returning\n");

    return (void*)111;
}

void* tfn2(void* arg) {
    printf("thread 2 exiting\n");
    pthread_exit((void*)222);
}

void* tfn3(void* arg) {
    while(1) {
	//线程杀死需要取消点
	//printf("thread 3: I'm going to end in 3 seconds...\n");
	//sleep(1);
        
	//自己添加取消点
	pthread_testcancel();
    }

    return (void*)666;
}

//注: 为了突出逻辑 省略程序中各函数调用返回值检查
int main() {
    pthread_t tid;
    void* tret = NULL;
    
    //创建线程1 回收
    pthread_create(&tid, NULL, tfn1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code = %d\n", (int)tret);

    //创建线程2 回收
    pthread_create(&tid, NULL, tfn2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code = %d\n", (int)tret);

    //创建线程3 杀死 并回收
    pthread_create(&tid, NULL, tfn3, NULL);
    sleep(3);
    pthread_cancel(tid); //杀死线程3
    pthread_join(tid, &tret);
    printf("thread 3 exit code = %d\n", (int)tret);

    return 0;
}
