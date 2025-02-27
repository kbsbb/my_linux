#include <stdio.h>
#include <string.h>
#define FILE_NAME "log.txt"

int main(){
    //FILE* fp = fopen(FILE_NAME,"w");
    FILE* fp = fopen(FILE_NAME,"r");
    if(NULL==fp){
        perror("fopen");
        return 1;
    }
    //写
    //int cnt = 5;
    //while(cnt){
    //    fprintf(fp,"%s:%d\n","hello",cnt--);
    
    //读
    char buffer[64];
    while(fgets(buffer, sizeof(buffer)-1, fp)!=NULL){
        buffer[strlen(buffer)-1] = 0;
        puts(buffer);
    }

    fclose(fp);

    return 0;
}
