//测试计算机1秒能数多少个数
//time 命令
//time ./a.out
//time ./a.out > out.txt  对比这两种   得出I/O对性能影响很大

#include <stdio.h>
#include <unistd.h>

int main() {
    //先计时 设置一个定时器
    alarm(1);

    int cnt = 1;
    while(1) {
	printf("%d\n", cnt ++);
	//printf("大哞爱哞哞\n");
    }

    return 0;
}
