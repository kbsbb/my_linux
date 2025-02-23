#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>

#define NUM 1024
#define TOKNUM 64

char cmdline[NUM];
char* bftok[TOKNUM];

int main(){
    while(1){
        //打印提示符
        printf("[%s@主机名 %s]$ ",getenv("USER"), getenv("PWD"));
        fflush(stdout);

        //获取用户输入
        char* s = fgets(cmdline, sizeof(cmdline)-1, stdin);
        assert(s != NULL);
        (void)s;
        cmdline[strlen(cmdline)-1] = 0;

        //字符串切割放入bftok字符串数组 
        bftok[0] = strtok(s, " "); 
        //int i = 1;
        //while(bftok[i++]= strtok(NULL," "));
        for(int i = 1; bftok[i-1]; i++){
            bftok[i] = strtok(NULL," ");
        }

//测试字符串切割是否正常
#ifdef DEBUG
        for(int i = 0; bftok[i]; i++){
            printf("bftok[%d] = %s\n",i,bftok[i]);
        }
        
#endif
        //创建子进程，使用进程替换
        pid_t id = fork();
        assert(id!=-1);
        if(id==0){
            //子进程
            execvp(bftok[0],bftok);
            exit(1);
        }
        //父进程
         waitpid(id,NULL,0);
        
        }
    return 0;
}
