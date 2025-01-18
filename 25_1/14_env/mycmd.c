#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_VAL "myval"
int main(int argc, char* argv[]){
    for(int i = 0; i < argc; i++){
        printf("argv[%d]->%s\n",i,argv[i]);
    }
    
    //char* who = getenv("USER");
    //printf("%s\n",who);

    /*
     * char* myenv = getenv(MY_VAL);
    if(NULL==myenv){
       printf("%s,not found\n",MY_VAL); 
    i}else{
        printf("%s:%s\n",MY_VAL,myenv);
    }
    */


    return 0;
}
