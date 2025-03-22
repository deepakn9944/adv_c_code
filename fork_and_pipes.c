#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //used for fork func

int main(int argc, char* argv[]) {
    int id = fork();
    printf("Hello, World! %d \n", id);
	return 0;
}

//print 1 to 5 with child process and 6 to 10 with main process using wait process

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //used for fork func
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int id = fork();
    int n;
    if(id == 0){
        n = 1;
    }
    else{
        n = 6;
    }
    if(id != 0){
        wait(NULL);
    }
    int i;
    for(i = n; i < n + 5; i++){
        printf("%d ", i);
        fflush(stdout);
    }
    if(id != 0){
        printf("\n");
    }
    
	return 0;
}

//process id
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //used for fork func
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int id = fork();
    printf("process child_id: %d, parent_id: %d\n", getpid(), getppid());
	return 0;
}


// multiple forks
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //used for fork func
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int id1 = fork();
    int id2 = fork();
    if(id1 == 0){
        if(id2 == 0){
            printf("we are process y\n");
        }
        else{
             printf("we are process x\n");
        }
    }else {
         if(id2 == 0){
            printf("we are process z\n");
        }
        else{
             printf("we are parent process \n");
        }
    }
    while(wait(NULL) != -1 || errno != ECHILD){
        printf("waiting for child process is finshed \n");
    }
	return 0;
}


// communication between processes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //used for fork func
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int fd[2];
    //fd[0] is for reading, fd[1] is for writing
    if (pipe(fd) == -1) {
        printf("an eror occured with pipe\n");
        return 1;
    }
    int id = fork();
    if(id == -1){
        printf("error while fork \n");
        return 2;
    }
    if(id == 0){
        close(fd[0]);
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        if( write(fd[1], &x, sizeof(int)) == -1){
            printf("an error occured with write\n");
            return 3;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            printf("an error occured with read\n");
            return 4;
        };
        close(fd[0]);
        printf("Got from child process %d : ", y);
    }
	return 0;
} 

/* you have an array {1,2,3,4,5,6} in which first half is 
   add by one process and second by other process. Later 
   they are add using pipes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int fd[2];
    int arr[] = {1, 2, 3, 4, 5, 6};
    int arr_size = sizeof(arr) / sizeof(int);
    int start, end;
    if (pipe(fd) == -1) {
        printf("an eror occured with pipe\n");
        return 1;
    }
    int id = fork();
    if(id == -1){
        printf("error while fork \n");
        return 2;
    }
    if(id == 0){
        close(fd[0]);
        start = 0;
        end = arr_size / 2;
    } else {
        close(fd[1]);
        start = arr_size / 2;
        end = arr_size;
    }
    int sum = 0;
    int i;
    for(i = start; i < end; i++){
        sum += arr[i];
    }
    printf("sum = %d\n", sum);

    if(id == 0){
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(int)) == -1){
            printf("an error occured with write\n");
            return 3;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            printf("an error occured with read\n");
            return 4;
        };
        close(fd[0]);
        sum += y;
        printf("total Sum : %d \n", sum);
        wait(NULL);
    }
	return 0;
}