#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// ping -c 5 google.com | grep rtt

int main( ) {
    int fd[2];
    if(pipe(fd) < 0){
        return 1;
    }
    int pid1 = fork();
    if(pid1 < 0){
        return 2;
    }
    if(pid1 == 0) {
        // child process for ping
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }

    int pid2 = fork();
    if(pid2 < 0){
         return 3;
    }
    if(pid2 == 0) {
        //child process for grep
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "rtt", NULL);

    }
    close(fd[0]);
    close(fd[1]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}