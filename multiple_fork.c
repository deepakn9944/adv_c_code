#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESS 10

int main() {
    int fd[NUM_PROCESS + 1][2];
    for(int i = 0; i < NUM_PROCESS + 1; i++){
        if(pipe(fd[i]) == -1){
            return 1;
        }
    }

    for(int i = 0; i < NUM_PROCESS; i++){
        int pid = fork();
        if(pid < 0){
            return 2;
        }
        if(pid == 0){
            for(int j = 0; j < NUM_PROCESS + 1; j++){
                if(i != j){
                    close(fd[j][0]);
                }
                else if(i+1 != j){
                    close(fd[j][1]);
                }
            }
            int x;
            if(read(fd[i][0], &x, sizeof(int)) < 0){
                return 3;
            }
            printf("(%d) got %d \n", i, x);
            x++;
            if(write(fd[i+1][1], &x, sizeof(int)) < 0){
                return 4;
            }
            printf("(%d) sent %d \n", i+1, x);
            close(fd[i][0]);
            close(fd[i+1][1]);
            return 0;
        }
    }
    int x = 5;
    if(write(fd[0][1], &x, sizeof(int)) < 0){
        return 5;
    }
    printf("(0) main sent : %d \n", x);
    if(read(fd[NUM_PROCESS][0], &x, sizeof(int)) < 0){
        return 6;
    }
    printf("result : %d \n", x);
    for(int i = 0; i < NUM_PROCESS+1; i++){
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for(int i = 0; i < NUM_PROCESS; i++){
        wait(NULL);
    }
}