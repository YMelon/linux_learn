/*简单shell实现
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXLINE 4096
#define MAXPIPE 16
#define MAXARG 8

struct {
    char* argv[MAXARG];
    char* in;
    char* out;        //表示是否有重定向输出
} cmd[MAXPIPE+1];


int parse(char* buf, int cmd_num) {
   int n = 0;
   char* p = buf;
   cmd[cmd_num].in = cmd[cmd_num].out = NULL;

   //ls -l -d -a -F > out
   while(*p != '\0') {
       if(*p == ' '){
	   *p ++ = '\0';
	   continue;
       }

       if(*p == '<') {
	   *p = '\0';
	   while(*(++p) == ' '); 
	   cmd[cmd_num].in = p;
	   if(*p ++ == '\0')
	       return -1;
	   continue;
       }

       if(*p == '>') {
	   *p = '\0';
	   while(*(++p) == ' ');
	   cmd[cmd_num].out = p;
	   if(*p ++ == '\0')
	       return -1;
	   continue;
       }

       if(*p != ' ' && ((p == buf) || *(p-1) == '\0')) {
	   if(n < MAXARG - 1) {
	       cmd[cmd_num].argv[n++] = p++;
	       continue;
	   } else {
	       return -1;
	   }
       }
       p ++;
   }

   if(n == 0) {
       return -1;
   }

   cmd[cmd_num].argv[n] = NULL;

   return 0;
}


int main() 
{
    char buf[MAXLINE];
    pid_t pid;
    int fd, i, j, pipe_num, cmd_num;
    int pfd[MAXPIPE][2];
    char* cur_cmd;
    char* next_cmd;

    while(1) {
	printf("mysh$ ");
	if(!fgets(buf, MAXLINE, stdin))
	    exit(0);

	//"ls -l\n"
	if(buf[strlen(buf)-1] == '\n')
	    buf[strlen(buf)-1] = '\0';
	cmd_num = 0;
	next_cmd = buf;

	while((cur_cmd = strsep(&next_cmd, "|"))) {
	    if(parse(cur_cmd, cmd_num++) < 0) {
		cmd_num --;
		break;
	    }

	    if(cmd_num == MAXPIPE + 1)
		break;
	}

	if(!cmd_num)
	    continue;

	pipe_num = cmd_num - 1;
	for(i = 0; i < pipe_num; ++i) {
	    if(pipe(pfd[i])) {
		perror("pipe");
		exit(1);
	    }
	}

	for(i = 0; i < cmd_num; ++i) {
	    if((pid = fork()) == 0)
		break;
	}

	if(pid == 0) {
	    if(pipe_num) {
		if(i == 0) {
		    dup2(pfd[0][1], STDOUT_FILENO);
		    close(pfd[0][0]);

		    for(j = 1; j < pipe_num; ++j) {
			close(pfd[j][0]);
			close(pfd[j][1]);
		    }
		} else if(i == pipe_num) {
		    dup2(pfd[i-1][0], STDIN_FILENO);
		    close(pfd[i-1][1]);

		    for(j = 0; j < pipe_num-1, ++j) {
			close(pfd[j][0]);
			close(pfd[j][1]);
		    }
		} else {
		    dup2(pfd[i-1][0], STDIN_FILENO);
		    close(pfd[i-1][1]);

		    dup2(pfd[i][1], STDIN_FILENO);
		    close(pfd[i][0]);

		    for(j = 0; j < pipe_num; ++j) {
			if(j != i || j != i-1) {
			    close(pfd[j][0]);
			    close(pfd[j][1]);
			}
		    }
		}
	    }

	    if(cmd[i].in) {
		fd = open(cmd[i].in, O_RDONLY);
		if(fd != -1)
		    dup2(fd, STDIN_FILENO);
	    }
	    if(cmd[i].out) {
		fd = open(cmd[i].out, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if(fd != -1)
		    dup2(fd, STDOUT_FILENO);
	    }

	    execvp(cmd[i].argv[0], cmd[i].argv);
	    fprintf(stderr, "executing %s error.\n", cmd[i].argv[0]);
	    exit(127);
	}
        
	//parent
	for(i = 0; i < pipe_num; ++i) {
	    close(pfd[i][0]);
	    close(pfd[i][1]);
	}
	for(i = 0; i < cmd_num; ++i) {
	    wait(NULL);
	}
    }
}


