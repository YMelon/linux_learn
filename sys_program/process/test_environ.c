/*打印当前进程的所有环境变量*/
#include <stdio.h>

extern char **environ;

int main() {
    int i;
    for(i = 0; environ[i] != NULL; i ++) {
        printf("%s \n", environ[i]); 
    }

    return 0;
}
