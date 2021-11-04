#define BUFF 100
#define MAX 18

typedef struct Time{
	long sec; 
	long ns; 
}Time;

//Process Control Block
typedef struct PCB{
	pid_t pid; 
	unsigned int local_simulated_pid;
	unsigned int process_priority;
	Time arrival_time; 
	Time exit; 
	Time cpu_time_used; 
	Time time_last_burst;
	Time queue; 
	Time block;
	Time wait_time; 
	Time total_time_system;
}PCB;

typedef struct Shared{
	Time total_time_system;;
	PCB ptable[MAX];
}Shared;

