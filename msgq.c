// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX 18
  
/*// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[18];
} message;
  
int main()
{
    key_t key;
    int msgid;
    int running = 1;
    struct mesg_buffer msg;
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(ftok(".", 800), 0666 | IPC_CREAT);

    if(msgid == -1){
    	perror("creating queue\n");
    }
  
    while(running){
	   
	    printf("Write Data : ");
	    fgets(message.mesg_text,MAX,stdin);
	    message.mesg_type = 1;
	    
	    // msgsnd to send message
	    if(msgsnd(msgid, &message, MAX, 0) == -1){
	    	perror("message not sent");
	    }
	    if(strncmp(message.mesg_text,"end",3) == 0){
	   	
		running = 0;
	    }

	    // display the message
	   // printf("Data send is : %s \n", message.mesg_text);
    }
    return 0;
}*/

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
  
    printf("Write Data : ");
    fgets(message.mesg_text,MAX,stdin);
  
    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
  
    // display the message
    printf("Data send is : %s \n", message.mesg_text);
  
    return 0;
}
