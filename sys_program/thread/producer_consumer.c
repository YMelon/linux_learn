//生产者-消费者模型 条件变量实现

#include "mythread.h"

//共享资源用链表模拟
struct msg {
    int num;
    struct msg* next;
};
//头指针和节点指针
struct msg* head = NULL;
struct msg* mp = NULL;

//定义并初始化 互斥锁和条件变量 采用静态初始化方法
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    while(1) {
	//生产
	mp = (struct msg*)malloc(sizeof(struct msg));
	mp -> num = rand() % 500 + 1;
	printf("---produced---%d\n", mp->num);

	//把产品放入共享区
	pthread_mutex_lock(&mutex);
	mp -> next = head;
	head = mp;
	pthread_mutex_unlock(&mutex);

	//通知
	pthread_cond_signal(&has_product);
        
	//cpu易主
	sleep(rand() % 3);
    }

    return NULL;
}

void* consumer(void* arg) {
    while(1) {
	//加锁
	pthread_mutex_lock(&mutex);

	//等待条件变量满足 注意while而不是if
	while(head == NULL) {
	    pthread_cond_wait(&has_product, &mutex);
	}

	//消费
	mp = head;
	head = mp -> next;
	pthread_mutex_unlock(&mutex);
	printf("------consumed------%d\n", mp->num);

	//释放
	free(mp);
	mp = NULL;

	sleep(rand() % 3);
    }

    return NULL;
}

int main() {
    pthread_t pid, cid;
    srand(time(NULL));

    //创建生产者 消费者线程
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    
    //回收
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}
