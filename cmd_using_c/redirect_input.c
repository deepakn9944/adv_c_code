#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    int pid = fork();
    if(pid == -1) { return 1; }
    if(pid == 0) {
        //child process
        int file = open("ping.txt", O_WRONLY | O_CREAT, 0777);
        if(file == -1){
            printf("creation or opening error\n"); 
            return 5;
        }
        //STDOUT_FILENO 1
        dup2(file, STDOUT_FILENO);
        close(file);

        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        if(err == -1){
            printf("could not find program to execute!\n");
            return 2;
        }
    }else{
        //parent process
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)) {
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0) {
                printf("success!\n");
            } else {
                printf("Failure!\n");
            }
        }
        printf("SUCESS \n");
        printf("Some post processing goes here!\n"); 
    }
    return 0;
}