#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h> 
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int arr[5];
    for(int i = 0; i < 5; i++) {
        arr[i] = rand() % 10;
        printf("generated %d\n", arr[i]);
    }

    int fd = open("sum", O_WRONLY);
    if(fd == -1) {
        return 1;
    }

    /*for(int i = 0; i < 5; i++) {
        if(write(fd, &arr[i], sizeof(int)) == -1){
            return 2;
        }
        printf("wrote %d\n", arr[i]);
    } */
   //optimize
    if(write(fd, arr, sizeof(int) * 5) == -1){
        return 2;
    }
    close(fd);

    fd = open("sum", O_RDONLY);
    if(fd == -1){
        return 3;
    }
    int sum;
    if(read(fd, &sum, sizeof(int)) == -1){
        return 4;
    }
    printf("Result recieved %d\n", sum);
    close(fd);

    return 0;
}
