//循环创建N个子进程 错误版本示例

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    pid_t pid;

    
    for(i = 0; i < 5; i ++) {
        pid = fork();

        if(pid == -1) {
            perror("fork error");
	    exit(1);
	} else if(pid == 0) {
	    printf("I'm %dth child. pid = %u, ppid = %u \n", i+1, getpid(), getppid() );
	
	} else {
	    printf("I'm parent. pid = %u, ppid = %u \n", getpid(), getppid() );
	} 
    }

    return 0;
}
