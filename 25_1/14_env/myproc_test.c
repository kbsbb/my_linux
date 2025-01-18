#include <stdio.h>
#include <unistd.h>
#include <string.h>

    int global_num = 100;
int main(){
    pid_t id = fork();
    if(id<0){
        printf("fork error\n");
    }else if(id ==0){
        int count = 0;
        while(1){
            printf("child,pid:%d,ppid:%d | global_num:%d,global_point:%p\n",getpid(),getppid(),global_num,&global_num);
            count++;
            sleep(1);
            if(count==5){
                global_num = 300;
                printf("子进程已经更改了全局变量....\n");
            }
        }
    }else{
        while(1){
            printf("father,pid:%d,ppid:%d | global_num:%d,global_point:%p\n",getpid(),getppid(),global_num,&global_num);
            sleep(2);    
        }
    }



    return 0;
}
