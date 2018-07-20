//利用setitimer() 参数it_interval的使用 周期定时参数
//简单捕捉信号的方法示例

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

//自定义信号捕捉处理函数
//回调函数
void myfunc(int signo) {
    printf("hello world\n");
}

int main() {
    //注册SIGALRM信号的捕捉处理函数
    //一旦该进程收到该信号时 执行注册的处理函数
    //不在执行默认动作
    signal(SIGALRM, myfunc);
    
    struct itimerval it, oldit;
    it.it_value.tv_sec = 5;
    it.it_value.tv_usec = 0;
    //下次定时器的间隔
    it.it_interval.tv_sec = 1;
    it.it_interval.tv_usec = 0;
    
    //设置定时器
    int ret = setitimer(ITIMER_REAL, &it, &oldit);
    if(ret == -1) {
	perror("setitimer error");
	exit(1);
    }

    while(1);

    return 0;
}
