/* I was able to find bits and pieces but could not fully implement the project.*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/msg.h>
#include "oss.h"
#include "shm.h"

#define MAXINT 18
#define MAXPCB 18

pid_t r_wait(int *stat_loc) {
   pid_t retval;
   while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
   return retval;
}

static void handler(int sig)
{
   //const char *name;
   printf("Caught signal %d, coming out...\n", sig);
   //logmsg(name);
   exit(1);
}

int main(int argc, char *argv[]){
    int shmid, count;
    int i, status, exit_status, n;
    int val, opt, timer = 100;
    char *shmp;
    pid_t child;
    struct sigaction sa;
    extern char *optarg;
    FILE *fp;
    char buff[50];
    //int running = 1;
    int msgid;

    setbuf(stdout, NULL); 

    //strncpy(buff, "logfile.txt", sizeof(buff));

    while ((opt = getopt(argc, argv, "hs:l:")) != -1) {
		switch (opt) {
			case 'h':
				printf("oss [-h] [-s t] [-l f]\n");
				printf("-h	Describe how the project should be run and then, terminate.\n"); 
				printf("-s t	Indicate how many maximum seconds before the system terminates.\n"); 
				printf("-l f	Specify a particular name for the log file\n");
				exit(0);
				break;
			case 's':
				timer = atoi(optarg);
				break;
			case 'l':
				strncpy(buff, optarg, sizeof(buff));
				break;
			default:
				perror("getopt failure");
				exit(1);
		}
	}

    // open log file for writing
	fp = fopen(buff,"w+");

	if (fp == NULL) {
		perror("Cannot open log file");
		exit(1);
	}

     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
     sa.sa_handler = handler;
     if (sigaction(SIGHUP, &sa, NULL) == -1)
        perror("sigaction");


     signal(SIGINT, handler);
     alarm(timer);


     shmid = shmget(ftok(".", 700), sizeof(char), IPC_CREAT | 0666);
     if (shmid == -1)
         perror("shmget");

    // Attach shared memory into our address space 

     shmp = shmat(shmid, NULL, 0);
     if (shmp == (void *) -1)
         perror("shmat");

     //write shared memory to a file
     fprintf(fp,"Data read from memory: %s\n",shmp);
     
     shmdt(shmp);
     if (shmctl(shmid, IPC_RMID, 0) == -1)
         perror("shmctl");


     msgid = msgget(ftok(".", 600), 0666 | IPC_CREAT);

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    // write the message to a file
    fprintf(fp,"Data Received is : %s\n", message.mesg_text);

    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);


     kill(msgid, SIGKILL);
    
     exit(EXIT_SUCCESS);

     return 0;
}
