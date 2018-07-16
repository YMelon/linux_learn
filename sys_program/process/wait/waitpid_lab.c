//练习，父进程fork三个子进程，一个调用ps命令，一个调用自定义程序1(正常),
//一个调用自定义程序2(段错误),父进程使用waitpid对子进程回收

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, wpid;
    int i, status;
    int n = 3; //创建三个子进程
    for(i = 0; i < n; i ++) {
        pid = fork();
	if(pid == -1) {
	    perror("fork error");
	    exit(1);
	} else if(pid == 0) {
	    break;
	}
    }

    //三个子进程执行不同程序
    switch(i) {
	case 0: 
	    sleep(i);
	    execlp("ps", "ps", "aux", NULL);
	    break;
	case 1:
	    sleep(i);
	    execl("./normal.out", "normal.out", NULL);
	    break;
	case 2:
	    sleep(i);
	    execl("./abnor.out", "abnor.out", NULL);
	    break;

	case 3: //父进程
	    do {
		wpid = waitpid(-1, &status, WNOHANG);
		if(wpid > 0) { //成功回收一个子进程
		    n --;

		    if(WIFEXITED(status)) { //正常结束子进程
		        printf("child exit with %d \n", WEXITSTATUS(status));
		    } else if(WIFSIGNALED(status)) { //异常结束子进程
		        printf("child killed by %d \n", WTERMSIG(status));
		    }
		}

		sleep(1); //歇会在轮询
	    }while(n > 0);
	    printf("wait finished \n");
	    break;
    }

    return 0;
}
