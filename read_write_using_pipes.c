#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    // 3 * 4 = 12 => 12
    int p1[2]; // P => C W => R
    int p2[2]; // P => C R => W
    if(pipe(p1) == -1) { return 1; }
    if(pipe(p2) == -1) { return 1; }
    int pid = fork();
    if(pid == -1){ return 2; }
    if(pid == 0){
        //child process
        close(p1[1]);
        close(p2[0]);
        int x;
        if(read(p1[0], &x, sizeof(int)) == -1) { return 3; }
        printf("Rceived %d\n", x);
        x *= 4;
        if(write(p2[1], &x, sizeof(int)) == -1) { return 4; }
        printf("wrote %d\n", x);
        close(p1[0]);
        close(p2[1]);
    }else{
        //parent process
        close(p1[0]);
        close(p2[1]);
        srand(time(NULL));
        int y = rand() % 10;
        if(write(p1[1], &y, sizeof(y)) == -1) { return 3; }
        printf("wrote %d\n", y);
        if(read(p2[0], &y, sizeof(y)) == -1) { return 4; }
        printf("Rceived %d\n", y);
        close(p1[1]);
        close(p2[0]);
        wait(NULL);
    }
    return 0;
}