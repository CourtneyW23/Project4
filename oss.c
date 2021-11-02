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

#define MAXINT 18
#define MAXPCB 18

union semun {   /* Used in calls to semctl() */
      int val;
      struct semid_ds *buf;
      unsigned short *array;
      #if defined(__linux__)
      struct seminfo *__buf;
      #endif
};

struct shmseg {
   int cntr;
   int write_complete;
   int read_complete;
};

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

//Process Control Block
struct pcb{
     pid_t pid;
     int running; //running, not running
     int prio;
     int counter;
     char *shm;
     FILE *fp;
     time_t totalCPUtime;
     time_t totalTimeinSys;
     time_t lastBurst;

};


pid_t r_wait(int *stat_loc) {
   pid_t retval;
   while (((retval = wait(stat_loc)) == -1) && (errno == EINTR)) ;
   return retval;
}


void logmsg(const char *msg){
        FILE *f;
        char *log;
        int i;
        time_t t;
        char *tm;
	
	//msg = argv[2];

        t = time(NULL);
        tm = ctime(&t);

        f = fopen(msg, "a");
        if(!f)
        {
                perror("Error opening file: ");
                exit(0);
        }

        if(log == NULL)
        {
                printf("Empty Log\n");
                exit(0);
        }
        log = tm;

        fprintf(f, "%s\n", log);
        fclose(f);

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
    union semun arg;
    struct sembuf sop[1];
    char *shmp;

    time_t t;
    char *tm;
  
    char **myargv;
    pid_t child, grandchild;
    struct sigaction sa;
    char *stuff = "stupid";
    extern char *optarg;

    FILE *fp;
    //int running = 1;
    int msgid;

    t = time(NULL);
    tm = ctime(&t);


    setbuf(stdout, NULL); 

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
				fp = fopen(optarg, "w");
				if (sizeof(fp > MAXINT))
					perror("file limit exceeded");		
				fprintf(fp, tm, "\n");
            			if (fp == NULL)
                			perror("fopen");
            			setbuf(fp, NULL);
	    			fclose(fp);
				break;
			default:
				perror("getopt");
				exit(1);
		}
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


     printf("Data read from memory: %s\n",shmp);
     shmdt(shmp);
     if (shmctl(shmid, IPC_RMID, 0) == -1)
         perror("shmctl");


     msgid = msgget(ftok(".", 600), 0666 | IPC_CREAT);

    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    // display the message
    printf("Data Received is : %s\n", message.mesg_text);

    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);


     kill(msgid, SIGKILL);
    
     exit(EXIT_SUCCESS);

     return 0;
}
