#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main() {
    int pid1 = fork();
    if(pid1 < 0){
        return 1;
    }
    if(pid1 == 0){
        sleep(4);
        printf("finised Execution \n");
        return 0;
    }
    int pid2 = fork();
    if(pid2 < 0){
        return 1;
    }
    if(pid2 == 0){
        sleep(1);
        printf("finised Execution \n");
        return 0;
    }
    int pid = waitpid(pid1, NULL, 0);
    printf("pid : %d \n", pid);
    pid = waitpid(pid2, NULL, 0);
    printf("pid : %d \n", pid);

}