//互斥量用于进程间同步

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

//把共享资源 互斥量 互斥量的属性 封装到一起了 
//结构体 方便处理
struct mt {
    int num;
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr_mutex;
};

int main() {
    int i;
    struct mt* mm;
    pid_t pid;
    
    //创建匿名映射区 并清零初始化
    mm = mmap(NULL, sizeof(*mm), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    memset(mm, 0, sizeof(*mm));
    
    //初始化并设置mutex属性为用于进程同步
    pthread_mutexattr_init(&mm->attr_mutex);
    pthread_mutexattr_setpshared(&mm->attr_mutex, PTHREAD_PROCESS_SHARED);
    
    //初始化mutex互斥锁 并传入上面设置好的属性
    pthread_mutex_init(&mm->mutex, &mm->attr_mutex);

    pid = fork();
    if(pid = 0) {
	//子进程对num进行加1操作10次
	for(i = 0; i < 10; i++) {
	    pthread_mutex_lock(&mm->mutex);

	    (mm->num) ++;
	    printf("---child---num++   %d\n", mm->num);

	    pthread_mutex_unlock(&mm->mutex);
	    sleep(1);
	}
    } else if(pid > 0) {
	//父进程对num进行加2操作10次
	for(i = 0; i < 10; i++) {
	    pthread_mutex_lock(&mm->mutex);

	    mm->num += 2;
	    printf("------parent------num+=2   %d\n", mm->num);

	    pthread_mutex_unlock(&mm->mutex);
	    sleep(1);
	}
	wait(NULL);
    }
    
    //销毁
    pthread_mutexattr_destroy(&mm->attr_mutex);
    pthread_mutex_destroy(&mm->mutex);
    munmap(mm, sizeof(*mm));

    return 0;
}
