//打印未决信号集状态
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void printpend(sigset_t* pend) {
    int i;
    //打印1-31号常规信号
    for(i = 1; i < 32; i++) {
	if(sigismember(pend, i) == 1)
	    putchar('1');
	else
	    putchar('0');
    }
    printf("\n");
}


int main() {
    sigset_t myset, oldset, pend;
    //为了逻辑清晰 省略各函数的错误判断
    sigemptyset(&myset);
    
    //3号信号 此程序执行时 在终端通过按键产生
    sigaddset(&myset, SIGQUIT);
    //2号信号 按键产生
    sigaddset(&myset, SIGINT);
    //20号信号 按键产生
    sigaddset(&myset, SIGTSTP);
    //11号信号 通过kill -11 pid 发出
    sigaddset(&myset, SIGSEGV);

    //特殊信号19号信号 通过kill命令发出
    sigaddset(&myset, SIGSTOP);
    //加入到阻塞信号集中
    sigprocmask(SIG_BLOCK,&myset, &oldset);
    
    while(1) {
        //读取 打印 未决信号集
        sigpending(&pend);
        printpend(&pend);
	sleep(2);
    }

    return 0;
}
