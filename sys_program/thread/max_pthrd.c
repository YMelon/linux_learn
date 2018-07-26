//查看所用计算机一个进程最多可以创建线程数量

#include "mythread.h"

void* tfn(void* arg) {
    //保证线程不能结束, 结束了就释放栈空间了, 后续计算就不准确了
    while(1)
	sleep(1);

    //pthread_exit((void*)1);
}

int main() {
    pthread_t tid;
    int ret;
    int cnt = 0;
    while(1) {
	ret = pthread_create(&tid, NULL, tfn, NULL);
	if(ret != 0) {
	    fprintf(stderr, "%s\n", strerror(ret));
	    break;
	}

	cnt ++;
	printf("%d\n", cnt);
    }

    return 0;
}
