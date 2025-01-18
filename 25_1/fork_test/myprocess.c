#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
   pid_t id = fork();
       if(id == 0){
            printf("我是子进程，我的pid是:%d,我的父进程是:%d\n",getpid(),getppid());
            sleep(5);
            exit(1);
       }else{
            printf("我是父进程，我的pid是:%d,我的父进程是:%d\n",getpid(),getppid());
            sleep(1);
            while(1){    
            printf("我是父进程，我的pid是:%d,我的父进程是:%d\n",getpid(),getppid());
            sleep(1);
            }

   }

    return 0;
}
