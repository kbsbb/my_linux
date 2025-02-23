#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("process is running...\n");
    execl("./cPro", "cPro",NULL); 
    exit(1);
}
