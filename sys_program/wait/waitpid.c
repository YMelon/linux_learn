//waitpid回收指定子进程；及回收所有子进程
//与获取子进程结束状态的四种宏函数结合同wait()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    int n = 5; //创建子进程个数，默认5个
    pid_t pid, q;
    pid_t wpid;
    
    for(i = 0; i < n; i ++) { //出口1，父进程出口
        pid = fork();

        if(pid == -1) {
            perror("fork error");
	    exit(1);
	} else if(pid == 0) {
	    break;         //出口2，子进程出口,i不自增 
	} else if(i == 2) { //1-1.父进程保存第三个子进程pid，用于后面waitpid回收
	    q = pid;
	} 
    }

    if(i == n) {   //父进程执行
        sleep(n);
	printf("I'm parent, pid = %u \n", getpid());
       
	/*
	//1.waitpid回收第三个子进程,以阻塞方式
	waitpid(q, NULL, 0);
        */

	//2.waitpid回收所有子进程,下面写法时waitpid等同wait(NULL)
	//while(waitpid(-1, NULL, 0)); 

	//3.非阻塞方式，轮询，回收所有子进程
	do{
	    //wpid == 0,说明子进程还没有结束
	    //wpid > 0 说明成功回收了一个子进程
	    //wpid == -1, 说明子进程都回收完毕，没有可供回收的子进程
	    wpid = waitpid(-1, NULL, WNOHANG);
	} while(wpid > 0 || wpid == 0);
     
      /*
	do{
	    wpid = waitpid(-1, NULL, WNOHANG);
	    if(wpid > 0) {
		n --;
	    }
	} while(n > 0);
      */

	printf("wait finished \n");

    } else { //子进程执行
	sleep(i);
	printf("I'm %dth child, pid = %u \n", i+1, getpid());
    } 

    return 0;
}
