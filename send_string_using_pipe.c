#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main() {
    int fd[2];
    if(pipe(fd) == -1){
        return 1;
    }
    int pid = fork();
    if(pid == -1){
        return 2;
    }
    if(pid == 0){
        //string
        close(fd[0]);
        char str[200];
        printf("Enter string :");
        fgets(str, 200, stdin);
        //last char will be \n
        str[strlen(str) - 1] = '\0';
        int len = strlen(str) + 1;
        if( write(fd[1], &len , sizeof(int)) == -1){
            return 3;
        }
        if( write(fd[1], str, sizeof(char) * len) == -1){
            return 4;
        }
        close(fd[1]);
    }
    else{
        //parent
        close(fd[1]);
        char str[200];
        int len = 0;
        if( read(fd[0], &len, sizeof(int)) < 0){
            return 5;
        }
        if( read(fd[0], str, sizeof(char)*len) < 0){
            return 6;
        }
        printf("received %s \n", str);
        close(fd[0]);
        wait(NULL);
    }
}
