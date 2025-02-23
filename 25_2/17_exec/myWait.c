#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define NUM 10
typedef void (*func_t)();   //函数指针
func_t handlerTask[NUM];    //声明一个函数指针数组

//样例任务
void task1(){
    printf("handler task1\n");
}
void task2(){
    printf("handler task2\n");
}

void loadTask(){
    memset(handlerTask, 0, sizeof(handlerTask));
    handlerTask[0] = task1;
    handlerTask[1] = task2;
}

void addTask(){

}

int main(){
    pid_t id = fork();
    assert(id != -1);
    if(id == 0){
        //child
        int cnt = 5;
        while(cnt--){
            printf("child running,pid:%d, ppid:%d, cnt:%d\n",getpid(),getppid(),cnt);
        sleep(1);
        //int *p = 0;
        //*p = 100;
        }
        exit(10);
    }
    //parent
    loadTask();

    int status = 0;
    //非阻塞等待
    while(1){
        pid_t ret = waitpid(id,&status,WNOHANG);
        if(ret == 0){
            printf("wait down,but child is running...,parent running other things\n");
            
            for(int i = 0; handlerTask[i] != 0; i++){
                handlerTask[i]();   //采用回调的方式，执行我们想让父进程在空闲的时候做的事情
            }
        }else if(ret > 0){
            printf("wait success, exit code:%d,sig:%d\n",(status>>8)&0xFF, status & 0x7F);
            break;
        }else{
            printf("waitpid load fail\n");
            break;
        }
        sleep(1); 
    }
    return 0;
}
