//读写锁
//三个线程不定时"写"全局资源,五个线程不定时"读"同一全局资源

#include "mythread.h"

int counter; //全局资源
pthread_rwlock_t rwlock; //读写锁定义

void* th_write(void* arg) {
    int t;
    int i = (int)arg;
    
    while(1) {
	//这么写有问题
	//t = counter;
	//usleep(1000);

	pthread_rwlock_wrlock(&rwlock);
	t = counter; //自己修改的
	printf("======write %d: %lu: counter = %d ++counter = %d\n",
		i, pthread_self(), t, ++counter);
	pthread_rwlock_unlock(&rwlock);

	usleep(5000); //微秒 为了让cpu易主
    }

    return NULL;
}

void* th_read(void* arg) {
    int i = (int)arg;

    while(1) {
	pthread_rwlock_rdlock(&rwlock);
	printf("-----read %d: %lu: %d\n", i, pthread_self(), counter);
	pthread_rwlock_unlock(&rwlock);

	usleep(900);
    }
    return NULL;
}

int main() {
    int i;
    pthread_t tid[8];
    
    //初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);
    
    //创建三个写线程
    for(i = 0; i < 3; i++)
	pthread_create(&tid[i], NULL, th_write, (void*)i);

    //创建五个读线程
    for(i = 0; i < 5; i++)
	pthread_create(&tid[i], NULL, th_read, (void*)i);
    
    for(i = 0; i < 8; i++)
	pthread_join(tid[i], NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
