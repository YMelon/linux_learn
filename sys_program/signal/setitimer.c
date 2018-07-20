//利用setitimer()实现alarm()
//测试计算机1秒能数多少个数

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

unsigned int my_alarm(unsigned int sec) {
    //setitimer()第二/三各参数
    struct itimerval it, oldit;
    int ret;
    
    //alarm()只有一个定时参数 只有秒 初始化
    it.it_value.tv_sec = sec;
    it.it_value.tv_usec = 0;
    //setitimer()参数结构体中下一次定时时间
    //这里实现alarm()不需要这个参数 为0值
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_sec = 0;

    ret = setitimer(ITIMER_REAL, &it, &oldit);
    if(ret == -1) {
	perror("setitimer error");
	exit(1);
    }
    
    //alarm()返回上一次定时剩下时间
    return oldit.it_value.tv_sec;
}


int main() {
    //先计时 设置一个定时器
    my_alarm(1);

    int cnt = 1;
    while(1) {
	printf("%d\n", cnt ++);
    }

    return 0;
}
