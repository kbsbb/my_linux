#include "processOn.h"

void processOn(void){
    //存放进度条字符#的数组
    char buff[Num];
    int count = 0;
    const char* stat = "|/-\\";

    //初始化数组
    memset(buff, '\0',sizeof(buff));
    while(count<=100){
        //颜色控制，显示进度，显示进度百分比，显示进度动态
        printf("\033[40;31m[%-100s][%3d%%][%c]\r\033[0m",buff,count,stat[count%4]);
        //刷新缓存
        fflush(stdout);
        buff[count++] = Style;
        //以微秒为单位睡眠/暂停
        usleep(50000); 
    }
    printf("\n");
} 
