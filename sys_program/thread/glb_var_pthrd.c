//验证线程是否共享全局变量

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//全局变量
int var = 100;

void* tfn(void* arg) {
    var = 200; //修改全局变量
    printf("thread\n");

    return NULL;
}

int main() {
    printf("Before pthread create, var = %d \n", var);

    pthread_t tid;
    pthread_create(&tid, NULL, tfn, NULL);
    sleep(1); //保证子线程执行

    printf("After pthread create, var = %d \n", var);

    return 0;
}
