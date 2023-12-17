#include<stdio.h>//input and output
#include<stdlib.h>
#include<unistd.h>//getpid()
#include<signal.h>// used for giving signals
#include <linux/sched.h>

#define STACK 8192
#define _GNU_SOURCE


//function 
int do_something(){
printf("child pid: %d\n",getpid());
return 0;
}


int main() {
    //allocate memory for the stack of the process
    void *stack = malloc(STACK);

    //check if malloc succeedded
    if (!stack){
        perror("malloc is failed");
        exit (0);
    }

    //create a new process using the clone() system call
    if(clone(&do_something,(char*)stack +STACK, CLONE_NEWUTS, 0)< 0){
        perror("CLONE failed");
        exit(0);
    }

    //code for the parent process
    printf("parent pid: %d\n", getpid());

    //add sleep to allow both processes to output
    sleep(1);

    //free the allocated stack memory
    free(stack);

    return 0;



}
