//线程同步例子1 两个线程操作了标准输出stdout这一共享资源
//1.主线程打印大写 子线程打印小写 模拟产生错误情况
//2.加锁

#include "mythread.h"

//定义锁
pthread_mutex_t mutex;

void* tfn(void* arg) {
    srand(time(NULL));
    
    while(1) {
	pthread_mutex_lock(&mutex);

	printf("hello ");
	//模拟长时间操作共享资源 导致CPU易主 产生与时间有关的错误
	sleep(rand() % 3); 
	printf("world\n");

	pthread_mutex_unlock(&mutex);
	sleep(rand() % 3);
	//3.注意加锁的粒度
	//pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t tid;
    //初始化锁 在创建线程之前  此时mutex=1
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid, NULL, tfn, NULL);
    while(1) {
	pthread_mutex_lock(&mutex);

	printf("HELLO ");
	//同子线程
	sleep(rand() % 3);
	printf("WORLD\n");

	pthread_mutex_unlock(&mutex);
	sleep(rand() % 3);
	//3.粒度
	//pthread_mutex_unlock(&mutex);
    }
    //对应init 
    pthread_mutex_destroy(&mutex);

    return 0;
}
