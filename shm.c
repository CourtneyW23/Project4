#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MMAX 18
#define SMAX 20
 
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;


int main()
{
  
    // shmget returns an identifier in shmid
    int shmid, n;
    char *shm;
    char buf[SMAX]; 
    int msgid;
	
    
    shmid = shmget(ftok(".", 700),SMAX,0666|IPC_CREAT);
  
    //shmat to attach to shared memory
    shm = shmat(shmid, NULL, 0);

    printf("Write Data : ");
    fgets(buf, SMAX, stdin);

    strcpy(shm, buf);
    printf("Data written in memory: %s\n",shm);

    msgid = msgget(ftok(".", 600), 0666 | IPC_CREAT);
    message.mesg_type = 1;

    printf("Write Data : ");
    fgets(message.mesg_text,MMAX,stdin);

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
    printf("Data send is : %s \n", message.mesg_text);
  
    return 0;
}
