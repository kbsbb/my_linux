#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>

#define NUM 1024
#define TOKNUM 64

//重定向用宏表示没有重定向，输入/输出/追加重定向
#define NONE_REDIR      0
#define INPUT_REDIR     1
#define OUTPUT_REDIR    2
#define APPEND_REDIR    3
//跳过空格宏
#define trimSpace(start)    do{\
    while(isspace(*start)) ++start;\
}while(0)

char cmdline[NUM];
char* bftok[TOKNUM];
//记录重定向的类型和重定向的文件
int redirType = NONE_REDIR;
char* redirFile = NULL;

//"ls -a -l > myfile.txt" -> "ls -a -l" "myflie.txt"
void commandCheck(char* cmdline){
    assert(cmdline);
    char* start = cmdline;
    char* end = cmdline + strlen(cmdline);
    
    while(start < end){
        //记得初始化，防止多次执行时错误
        redirType = NONE_REDIR;
        redirFile = NULL;
        
        if(*start == '>'){
           *start = '\0';
           start++;
           if(*start=='>'){
                //"ls -a >> file.log"
                redirType = APPEND_REDIR;
                start++;
           }else{
                //"ls -a > file.log"
                redirType = OUTPUT_REDIR;
           }
           trimSpace(start);
           redirFile = start;
           break;

        }else if(*start == '<'){
            //分割前后字符串
            *start = '\0';
            start++;
            //跳过空格
            trimSpace(start);
            //记录重定向类型和文件
            redirType = INPUT_REDIR;
            redirFile = start;
            break;
        //如果没碰到重定向符就往后找
        }else{
            start++;
        }
    }
}

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

        //分割重定向后的的字符串
        commandCheck(cmdline);
        
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
            //根据重定向类型选择打开文件方式，以及dup2重定向 
            switch (redirType){
                case NONE_REDIR:
                    //什么都不做
                    break;
                case INPUT_REDIR:
                {
                    int fd = open(redirFile, O_RDONLY);
                    if(fd < 0){
                        perror("open");
                        exit(errno);
                    }
                    dup2(fd, 0);
                    break;
                }
                case OUTPUT_REDIR:
                case APPEND_REDIR:
                {
                    int flags = O_WRONLY | O_CREAT;
                    if(redirType == APPEND_REDIR) flags |= O_APPEND;
                    else flags |= O_TRUNC;
                    int fd = open(redirFile, flags,0666);
                    if(fd < 0){
                        perror("open");
                        exit(errno);
                    }
                    dup2(fd, 1);
                    break;
                }
                default:
                    printf("bug?\n");
                    break;
            }
            execvp(bftok[0],bftok);
            exit(1);
        }
        //父进程
         waitpid(id,NULL,0);
        
        }
    return 0;
}
