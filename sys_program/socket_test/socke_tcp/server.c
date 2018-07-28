//服务器示例 功能:小写转大写
//突出逻辑 省略各调用函数返回值检查
//3.加入出错处理

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666

int main() {
    int sfd, cfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_len;
    char buf[BUFSIZ];
    char cli_ip[BUFSIZ]; //用于存储连接上的客户端IP
    int n, i;
    int ret;

    //创建
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1) {
	perror("socket error");
	exit(1);
    }
    //绑定
    bzero(&serv_addr, sizeof(serv_addr)); //好习惯 清零 对比memset
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret =  bind(sfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret == -1) {
	perror("bind error");
	exit(1);
    }
    //设置同时可连接数 好好理解这里
    ret = listen(sfd, 128);//默认上限
    if(ret == -1) {
	perror("listen error");
	exit(1);
    }

    //等待连接
    cli_addr_len = sizeof(cli_addr);
    cfd = accept(sfd, (struct sockaddr*)&cli_addr, &cli_addr_len);
    if(cfd == -1) {
	perror("accept error");
	exit(1);
    }
    
    //2.打印连接好的客户端信息
    printf("client IP: %s, client port: %d\n",
	    inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, cli_ip, sizeof(cli_ip)),
	    ntohs(cli_addr.sin_port));

    //处理数据并回传
    while(1) {
	n = read(cfd, buf, sizeof(buf));
	for(i = 0; i < n; i++)
	    buf[i] = toupper(buf[i]);
	write(cfd, buf, n);
    }

    //关闭
    close(sfd);
    close(cfd);

    return 0;
}
