//客户端:对应服务器功能:小写转大写
//省略调用函数返回值检查

#include "myunp.h"

//服务器IP 端口号
#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666

int main() {
    int cfd;
    char buf[BUFSIZ];
    int n;
    struct sockaddr_in serv_addr;

    //创建socket
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //没有显示调用bind 依赖隐式绑定

    //初始化服务器IP+port
    memset(&serv_addr, 0, sizeof(serv_addr)); //清零 防止初始化失败 里面是随机值从而发生错误
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port =htons(SERV_PORT) ;
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

    //连接
    connect(cfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

    while(1) {
	//从键盘读取输入 发送给服务器 接收服务器回传并打印到屏幕
	//"hello world\n" --> fgets --> "hello world\n\0"
	fgets(buf, sizeof(buf), stdin);
	write(cfd, buf, strlen(buf)); //strlen是由于fgets特性
	n = read(cfd, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, n);
    }

    close(cfd);

    return 0;
}
