//https://github.com/abhinayguduri/PBRR/blob/master/PBRR.c
#include<stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "shm.h"


int main()
{
    struct PCB bt[20],p[20],wt[20],tat[20],pr[20];
    struct PCB at[20],rt[20],rbt[20];
    int i,j,n,total=0;
    int quantum, remain,timet,pos,temp;
    int avg_wt,avg_tat;
    
    printf("Enter Total Number of Process:");
    srand(time(NULL));
    for (i = 0; i < 1; i++) {
         n = (rand() %
           (20 - 1 + 1)) + 1;
        printf("%d ", n);
    }

    printf("Enter Time Quantum:\t");
    scanf("%d",&quantum);
 
    printf("\nEnter Arrival Time Burst Time and Priority\n");
    for(i=0;i<n;i++)
    {   
        printf("\nP[%d]\n",i+1);
	printf("Arrival Time");
	scanf("%d",&at[i]);
        printf("Burst Time:");
        scanf("%d",&bt[i]);
        printf("Priority:");
        //scanf("%d",&pr[i]);
	pr[i] = rand() % (1 - 0 + 1) + 0;
	printf("%d ", pr[i]);
        p[i]=i+1;           //contains process number
	rt[i] = bt[i];
    }

    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[i])
            {
	        temp=at[i];
                at[i]=at[j];
                at[j]=temp;
 
        	temp=pr[i];
        	pr[i]=pr[j];
        	pr[j]=temp;
 
        	temp=bt[i];
        	bt[i]=bt[j];
        	bt[j]=temp;
 
        	temp=p[i];
        	p[i]=p[j];
        	p[j]=temp;

		temp=rt[i];
                rt[i]=rt[j];
                rt[j]=temp;
	    }else if(pr[j] == pr[i])
	     {
		    if(p[j]>p[i]){
			temp = at[i];
		    	at[i] = at[j];
                    	at[j] = temp;
                    
		    	temp =  pr[i];                    
		    	pr[i] = pr[j];
                    	pr[j] = temp;
                    
		    	temp =  p[i];                    
		    	p[i] = p[j];
                    	p[j] = temp; 
                    
		    	temp =  bt[i];
		    	bt[i] = bt[j];
                    	bt[j] = temp;
		    
		    	temp =  rt[i];
                    	rt[i] = rt[j];
                    	rt[j] = temp;
		    }
	     }
	}

    }

    int service_time[n];
    service_time[0] = at[0];
 
    wt[0]=0; //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
	// Add burst time of previous processes
        service_time[i] = service_time[i-1] + bt[i-1];
 
        // Find waiting time for current process =
        // sum - at[i]
        wt[i] = service_time[i] - at[i];
        
	// If waiting time for a process is in negative
        // that means it is already in the ready queue
        // before CPU becomes idle so its waiting time is 0
        if (wt[i] < 0)	
        	wt[i]=0;
        
	for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;

    printf("\nProcess\t    Arrival Time\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t    %d\t\t\t%d",p[i],at[i],bt[i],wt[i],tat[i]);
    }
 
    avg_tat=total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%d",avg_wt);
    printf("\nAverage Turnaround Time=%d\n",avg_tat);
 
return 0;
}
