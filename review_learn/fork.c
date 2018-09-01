/*循环创建N个子进程,N由命令行参数指定
 *每个子进程睡眠i秒后打印自己是第几个子进程
*/

#include "syspro.c"

int main(int argc, const char* argv[])
{
    int i, n = 5;
    pid_t pid;
    
    //这么写有错误，大错误 分析
    //n = argv[1] - '0';

    if(argc == 2)
	n = atoi(argv[1]);
    
    for(i = 0; i < n; ++i) {
	pid = fork();

	if(pid == -1) {
	    perror("fork error");
	    exit(1);
	}
        
	//child
	if(pid == 0)
	    break;
    }
    
    //child
    if(i < n) {
	sleep(i);
	printf("I'm %dth child, pid = %d\n", i+1, getpid());
    }
    
    //parent
    if(i == n) {
	sleep(n);
	printf("I'm parent, pid = %d\n", getpid());
    }

    return 0;
}
