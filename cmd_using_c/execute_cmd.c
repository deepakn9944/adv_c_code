#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid = fork();
    if(pid == -1) { return 1; }
    if(pid == 0) {
        //child process
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