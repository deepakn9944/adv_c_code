// 2 processes
// 1) Child process should generate random numbers and send them to the parent
// 2) Parent is going to sum all the numbers and print the result
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int fd[2];
    if(pipe(fd) == -1){
        return 1;
    }
    int pid = fork();
    if(pid == -1){
        return 2;
    }
    if(pid == 0){
        close(fd[0]);
        int arr[10];
        int n;
        srand(time(NULL));
        n = rand() % 10 + 1;
        printf("n : %d \n", n);
        for(int i = 0; i < n; i++){
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }
        printf("\n");
        if(write(fd[1], &n, sizeof(int) ) < 0 ){
            return 4;
        }
        if(write(fd[1], arr, sizeof(int) * n ) < 0 ){
            return 3;
        }
        close(fd[1]);
    }
    else{
        
        close(fd[1]);
        int arr[10];
        int n;
        if(read(fd[0], &n, sizeof(int) ) == -1){
            return 5;
        }
        if(read(fd[0], arr, sizeof(int) * n ) == -1){
            return 6;
        }
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += arr[i];
        }
        printf("sum result : %d \n", sum );
        close(fd[0]);
        wait(NULL);
    }
    return 0;
}
