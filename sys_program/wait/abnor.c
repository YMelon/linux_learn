//测试程序，用于验证wait获取子进程自身异常退出状态，而非人工kill

int main() {
    char *p = "test of wait\n";
    
    //改变常量,段错误,11信号
    //p[0] = 'h';
    
    //浮点数例外，8信号
    int a = 5/0;
}
