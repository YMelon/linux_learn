//通过设置线程属性实现线程分离

#include "mythread.h"

void* tfn(void* arg) {
    pthread_exit((void*)100);
}

int main() {
   pthread_t tid;
   int ret;
   pthread_attr_t attr;
    
   //设置分离 省略返回值检查
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   pthread_create(&tid, &attr, tfn, NULL);
   
   //打印分离状态下回收的返回值
   ret = pthread_join(tid, NULL);
   if(ret != 0) {
       fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
   }

   return 0;

}
