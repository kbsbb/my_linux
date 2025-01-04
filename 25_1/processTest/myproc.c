#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    
    pid_t id = fork();
    printf("我是一个进程，pid:%d,ppid:%d,id:%d\n",getpid(),getppid(),id);
    sleep(1);
    return 0;
}

/*int main(){
    while(1){
        printf("我是一个进程,子进程是%d,父进程是%d\n",getpid(),getppid());
        sleep(1);
    }
    return 0;
}
*/
