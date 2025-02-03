#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t id = fork();
    if(id==0){
        //子进程
        int cnt = 5;
        while(cnt){
            printf("我是子进程:%d,父进程:%d,cnt:%d\n",getpid(),getppid(),cnt--);
            sleep(1);
        }
        exit(0);
    }
    //父进程
    sleep(10);
    pid_t ret = wait(NULL);
    if(id>0){
        printf("wait success:%d\n",ret);
 }
    sleep(3);
}
