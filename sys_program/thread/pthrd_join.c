//回收子线程 例子

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//定义复杂线程退出值
typedef struct {
    char ch;
    int var;
    char str[64];
} exit_t;


//线程执行函数
void* thrd_func(void* arg) {
    
    //1.退出值为100
    //100 --> void* 64位 4 --> 8 补0 没问题
    //pthread_exit((void*)100);

    //2.复杂退出值
    exit_t * ret = (exit_t*)malloc(sizeof(exit_t));
    ret -> ch = 'a';
    ret -> var = 100;
    strcpy(ret -> str, "my pthread\n");
    pthread_exit((void*)ret);
}


int main() {
    pthread_t tid;
    int ret;
    
    //1.用于接收子线程退出值
    //int *retval;
    //2.复杂的退出值
    exit_t* retval;    

    printf("In main1: thread id = %lu, pid = %u \n", pthread_self(), getpid());
    
    //创建线程
    ret = pthread_create(&tid, NULL, thrd_func, NULL);
    if(ret != 0) {
	//打印错误描述
	fprintf(stderr, "pthread_create error: %s \n", strerror(ret));
	exit(1);
    }
    
    //回收子线程
    pthread_join(tid, (void**)&retval);
    //1.打印子线程退出值 为什么不是*retval来取值 
    //而是转换为int? 不明白
    //printf("------%d\n", (int)retval);
    
    //2.打印复杂退出值
    printf("ch = %c, var = %d, str = %s\n", retval -> ch, retval -> var, retval -> str);

    pthread_exit(NULL);
}
