#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include "shm.h"

#define MMAX 18
#define SMAX 20

#define BLOCK 0
#define TERMINATE 1
#define WAIT 2
#define RUN 3

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

struct mesg_buffer arr[1] = {
	{0,"HAPPY"}, {0,"SAD"}, {0,"BAD"}, {0,"MAD"}
	};

int main()
{
  
    // shmget returns an identifier in shmid
    int shmid, i;
    char *shm;
    char buf[SMAX]; 
    int msgid;
    time_t start_t;
    double diff_t;
    FILE *fp;

    fp = fopen("data.txt", "r");
	
    start_t = time(NULL);

    shmid = shmget(ftok(".", 700),SMAX,0666|IPC_CREAT);
  
    //shmat to attach to shared memory
    shm = shmat(shmid, NULL, 0);

    //fgets(buf, SMAX, fp);

    //strncpy(shm, buf, SMAX);
    //printf("Data written in memory: %s\n",shm);

    msgid = msgget(ftok(".", 600), 0666 | IPC_CREAT);
    message.mesg_type = 1;
  
    fgets(message.mesg_text, MMAX, fp);
        
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
  
    // display the message
    printf("Data send is : %s \n", message.mesg_text);	
    
    diff_t = difftime(time(NULL), start_t);

    printf("Execution time = %f\n", diff_t);
    printf("Exiting of the program...\n");
  
    fclose(fp);

    return 0;
}
