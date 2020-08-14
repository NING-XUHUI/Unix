#include <apue.h>
#include <sys/wait.h>


int main(void)
{
    char buf[MAXLINE]; /* 来自apue.h */
    pid_t pid;
    int status;

    printf("%% ");     /* */
    while(fgets(buf, MAXLINE,stdin) != NULL){
        if(buf[strlen(buf)-1] == '\n')
            buf[strlen(buf) - 1] = 0;   /* 将尾部的\0替换为null，因为execlp执行命令时以null为结束符  */
        if((pid = fork()) < 0){
            err_sys("fork error");
        }


        else if(pid == 0){
            execlp(buf,buf,(char *)0);
            err_ret("couldn't execute: %s",buf);
            exit(127);
        }
        /*parent*/
        if((pid = waitpid(pid,&status,0))< 0)
            err_sys("waitpid error");
        printf("%%" );
    }
    exit(0);
}

