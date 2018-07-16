//自定义程序,用于被execl()调用执行测试
#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 5;
    while(n --) {
        sleep(1);
	printf("------ \n");
    }

    return 0;
}
