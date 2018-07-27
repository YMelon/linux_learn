//生产者-消费者模型 信号量实现semaphore

#include "mythread.h"

#define NUM 5

//共享资源 用队列实现
int queue[NUM];
//两个信号量 空格子 产品
sem_t blank_num, product_num;

void* producer(void* arg) {
    int i = 0;
    while(1) {
	//若空格>0 将空格--  为0则阻塞
	sem_wait(&blank_num);
        
	//生产
	queue[i] = rand() % 1000 + 1;
	printf("---produce---%d\n", queue[i]);
        
	//将产品++ 并通知消费者
	sem_post(&product_num);

	i = (i+1) % NUM;
	sleep(rand() % 3);
    }

    return NULL;
}

void* consumer(void* arg) {
    int i = 0;
    while(1) {
	//产品-- 为0则阻塞
	sem_wait(&product_num);
        
	//消费
	printf("---consumed------%d\n", queue[i]);
	queue[i] = 0;
        
	//空格++
	sem_post(&blank_num);

	i = (i+1) % NUM;
	sleep(rand() % 3);
    }

    return NULL;
}


int main() {
    srand(time(NULL));

    pthread_t pid, cid;
    
    //初始化信号量 格子数为NUM  产品数为0
    sem_init(&blank_num, 0, NUM);
    sem_init(&product_num, 0, 0);
    
    //创建生产者 消费者
    pthread_create(&pid, NULL, &producer, NULL);
    pthread_create(&cid, NULL, &consumer, NULL);
    
    //回收
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    
    //销毁 对应init
    sem_destroy(&blank_num);
    sem_destroy(&product_num);

    return 0;
}
