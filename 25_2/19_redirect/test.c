#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fd < 0){
        perror("open");
        return 1;
    }
    dup2(fd, 1);
    printf("open fd: %d\n", fd);
    fprintf(stdout, "open fd: %d\n",fd);

    const char *msg = "hello world\n";
    write(1, msg, strlen(msg));

    fflush(stdout);
    close(fd);

    return 0;
}
