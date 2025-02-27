#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define FILE_NAME2 "log2.txt"

int main(){
    umask(0);
    int fd = open(FILE_NAME2, O_WRONLY | O_CREAT |O_TRUNC, 0666);
    if(fd<0){
        perror("open");
        return 1;
    }
    int cnt = 5;
    char outBuffer[64];
    while(cnt){
        sprintf(outBuffer, "%s:%d\n", "hello kbsbb", cnt--);
        write(fd, outBuffer, strlen(outBuffer));
    }

    close(fd);

    return 0;
}
