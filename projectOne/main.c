// Angel Camacho
// Username: acamacho
// CS474 Project One
// 10/4/2020

// I just want to say that this was supper confusing I dont understand why I got completly diff
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define SHMKEY ((key_t) 1497)
//static int total = 0;

// initializing shared mamory as a global variable
typedef struct
{
	int value;
}shared_mem;

shared_mem *total;

// in these functions we are essentially adding total->value secuentially
// untill it reaches its determined value
// not to mention we also print out the result
void process1(){
    while(total->value < 100000){
        total->value = total->value + 1;
    }
    printf("Executed: process1 \nResult: %d\n",total->value);
    exit(0);
}
void process2(){
    while(total->value < 200000){
        total->value = total->value + 1;
    }
    printf("Executed: process2 \nResult: %d\n",total->value);
    exit(0);
}
void process3(){
    while(total->value < 300000){
        total->value = total->value + 1;
    }
    printf("Executed: process3 \nResult: %d\n",total->value);
    exit(0);
}
void process4(){
    while(total->value < 500000){
        total->value = total->value + 1;
    }
    printf("Executed: process4\nResult: %d\n",total->value);
    exit(0);
}

int main() {

    // initializing my four processes
    int shmid,pid1,pid2,pid3,pid4;
    // initializing shared memory
    char *shmadd;
    shmadd = (char*)0;

    // create and connecting shared memory
    // we are checking if the shared memory has appropriate instances
    if ((shmid=shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0){
        perror("shemget");
        exit(1);
    }
    if ((total = (shared_mem*) shmat(shmid,shmadd, 0)) == (shared_mem*)-1){
        perror("shmat");
        exit(0);
    }

    // withing these if statements we are essentially makeing sure that the children
    // are not having more children not to mention we call the process functions if
    // our argument is true 
    total->value = 0;
    if((pid1 = fork())==0){
        process1();
        exit(0);
    }
    // waitpid(pid1,NULL,0);
    // printf("Finished Child PID: %d\n", pid1);
    if((pid2 = fork())==0){
        process2();
        exit(0);
    }
    // waitpid(pid2,NULL,0);
    // printf("Finished Child PID: %d\n", pid2);
    if((pid3 = fork())==0){
        process3();
        exit(0);
    }
    // waitpid(pid3,NULL,0);
    // printf("Finished Child PID: %d\n", pid3);
    if((pid4 = fork())==0){
        process4();
        exit(0);
    }
    // waitpid(pid4,NULL,0);
    // printf("Finished Child PID: %d\n", pid4);

    // was not sure which method to use
    // here we are simply waiting for our processes to be finished
    // when our processes are finished we print out their process ID
	waitpid(pid1,NULL,0);
    printf("Finished Child PID: %d\n", pid1);
	waitpid(pid2,NULL,0);
	printf("Finished Child PID: %d\n", pid2);
	waitpid(pid3,NULL,0);
	printf("Finished Child PID: %d\n", pid3);
	waitpid(pid4,NULL,0);
    printf("Finished Child PID: %d\n", pid4);

    // waitpid(pid1,NULL,0);
    // waitpid(pid2,NULL,0);
    // waitpid(pid3,NULL,0);
    // waitpid(pid4,NULL,0);
    // printf("Finished Child PID: %d\n", pid1);
    // printf("Finished Child PID: %d\n", pid2);
    // printf("Finished Child PID: %d\n", pid3);
    // printf("Finished Child PID: %d\n", pid4);

    // realeasing shared memory (shared memory detatch)
	if(shmdt(total)==-1){
		perror("shmdt");
		exit(-1);
	}

    printf("\n\n---------------------------------\n\n");
    //test
    return 0;
}