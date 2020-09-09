#include <stdio.h>
#include <apue.h>
#include <sys/wait.h>

static void sig_int(int);   //信号捕捉函数

int main()
{
    char buf[MAXLINE];      //来自apue.h文件
    pid_t pid;
    int status;

    if(signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != NULL){
        if(buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;   // 将null替换为新的一行
        
        if((pid = fork()) < 0){
            err_sys("fork error");   
        }else if(pid == 0){
            execlp(buf, buf, (char*)0);
            err_ret("couldn't execute:%s",buf);
            exit(127);
        }

        if((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }

    
    return 0;
}

void sig_int(int signo){
    printf("interrupt\n%% ");
}
