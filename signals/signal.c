/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int main()
{
    int pid = fork();
    if(pid == -1){
        return 1;
    }
    if(pid == 0){
        while(1){
            printf("Some text is running");
            usleep(5000);
        }
    }
    else{
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}

//STOP and CONTINUE a process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int main()
{
    int pid = fork();
    if(pid == -1){
        return 1;
    }
    if(pid == 0){
        while(1){
            printf("I'm alive\n");
            usleep(5000);
        }
    }
    else{
        kill(pid, SIGSTOP);
        int t;
        do {
            printf("Time :");
            scanf("%d", &t);

            if (t > 0) {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }

        } while (t > 0);
        
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}

//STOP = ctrl + Z , CONTINUE = fg <Id> in terminal
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int main()
{
   int x;
   printf("Enter a number :");
   scanf("%d", &x);
   printf("x = %d \n", x);
    return 0;
}

/*SIGNAL we have a question if user 
does not give answer give hint */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>


int x = 0;
void handle_sigusr1(int sig)
{
    if(x == 0) {
        printf("one\n");
    } 
}

int main()
{
   int pid = frok();
   if(pid == -1) {
    return 1;
   }
   if(pid == 0) {
    // Child
    sleep(5);
    kill(getppid(), SIGUSR1);
   }else{
    // Parent
    struct sigaction sa = { 0 };
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = &handle_sigusr1;
    sigaction(SIGUSR1, &sa, NULL);

    
    printf("Tell me your Password : ");
    scanf("%d", &x);
    if(x == 1234) {
        printf("Right !\n");
    }else{
        printf("Wrong !\n");
    }
    wait(NULL);
   }
}