//子进程调用execlp()执行ls命令例程,execl()类比

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if(pid == -1) {
	perror("fork error");
	exit(1);
    } else if(pid == 0) { //子进程
        //execlp("ls", "ls", "-l", "-a", NULL); //正确

        //第二个参数类比命令行参数argv[0],虽然传入但是ls执行时不用这个参数，所以乱写也没有出错
        //execlp("ls", "djaljdlkkl", "-l", "-a", NULL);

        //错误,第三个参数就不能乱写了，因为是argv[1],ls的参数
        //execlp("ls", "ls", "-dljd", "-a", NULL);

	//execl()
	execl("/bin/ls", "ls", "-l", NULL);

	//错误示例，相当于ls,同样注意第二个参数为argv[0],为可执行程序名，第三个参数才是真正用于命令的参数
	//execl("/bin/ls", "-l", NULL);
    } else { //父进程
	sleep(1);  //保证父进程最后退出,然后shell控制前台,防止输出混乱
	printf("parent \n");
    }

    return 0;
}
