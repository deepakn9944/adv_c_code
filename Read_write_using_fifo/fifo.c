#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char* argv[]){
    if(mkfifo("fifo1", 0777) == -1){
        if(errno != EEXIST){
            printf("something went wrong with creating fifo \n");
            return 1;
        }
    }
    int fd = open("fifo1", O_WRONLY);
    int x = 97;
    if(write(fd, &x, sizeof(int)) == -1){
        printf("fail to write");
        return 2;
    }
    close(fd);
}