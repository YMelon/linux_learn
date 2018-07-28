//文件锁 例子程序
//1.先测试读锁 同时运行两个或多个此进程 都可以加锁成功 证明读可以共享
//2.测试写锁 同时运行多个此进程 只能一个进程加锁成功 其他等待加锁 证明写独占
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//自定义 错误处理函数
void sys_err(char* str) {
    perror(str);
    exit(1);
}

int main(int argc, char* argv[]) {
    int fd;
    struct flock f_lock;
    
    //程序使用错误检测 从命令行传入要操作的文件名
    if(argc < 2) {
	printf("./a.out filename\n");
	exit(1);
    }
    
    //注意这个if语句 有错 这么写 读锁也能一起加 为什么？分析
    //运算符优先级
    //if(fd = open(argv[1], O_RDWR) < 0)

    if((fd = open(argv[1], O_RDWR)) < 0)
	sys_err("open error");
    
    //设置读 写 锁
    f_lock.l_type = F_WRLCK;
    //f_lock.l_type = F_RDLCK;
    
    //设置其他属性
    f_lock.l_whence = SEEK_SET; //加锁起始位置
    f_lock.l_start = 0; //偏移量
    f_lock.l_len = 0; //0表示加锁整个文件
    
    //加锁
    fcntl(fd, F_SETLKW, &f_lock);
    printf("get flock\n");
    
    //对文件操作的模拟 啥也没做
    sleep(10);
    
    //解锁
    f_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &f_lock);
    printf("un flock\n");

    close(fd);

    return 0;
}
