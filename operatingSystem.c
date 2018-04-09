#include<stdio.h>

int p;
int totP = 0;
int countQ1=0;
int countQ2 = 0;
int countQ3 = 0; 
int bQuanta = 10;
int sQuanta = 4;
int totWaitTime = 0;
	
struct data{
	int processId;
	int priority;
	int burstTime;
};

void sjfSort(struct data sjf[]);
//method to start processing
void startProcessing(struct data fcfs[], struct data sjf[], struct data roundRobin[], struct data info[]);
void startRounRobin(struct data roundRobin[], struct data info[]);
void startRounSJF(struct data sjf[], struct data info[]);
void startRounFCFS(struct data fcfs[], struct data info[]);

int main(){ 
  
    printf("Enter total number of processes:- ");
	scanf("%d",&p);
	
    struct data info[p];
	
	printf("\nNOTE:\nEnter priorities between \n1-10 for fcfs, \nbetween 11-20 for sjf, \nbetween 21-30 for ROUND ROBIN\n");
	
	for(int i = 0;i<p;i++)
	{	
		info[i].processId = i+1;
	    printf("\npriority of process %d: ",i+1);
		scanf("%d",&info[i].priority);
		printf("Burst time of process %d: ",i+1);
		scanf("%d",&info[i].burstTime);

		totWaitTime += info[i].burstTime;
	}
	
	for(int i =0;i<p;i++)
	{
		if(info[i].priority>=1&info[i].priority<=10)
		{
			countQ1++;
		}
		
		if(info[i].priority>=11&info[i].priority<=20)
		{
			countQ2++;
		}
		
		if(info[i].priority>=21&info[i].priority<=30)
		{
			countQ3++;
		}
	}
	

	printf("\n%d\n",countQ1);
	printf("\n%d\n",countQ2);
	printf("\n%d\n",countQ3);

	//till here code is workin fine.
    struct data fcfs[countQ1];
	printf("\nProcesses under fcfs:");
	
	int pos = 0;
	for(int i = 0;i<p;i++)
	{  
		
	    if(info[i].priority>=1 & info[i].priority<=10){
	    	
			fcfs[pos] = info[i];
	    	pos++;
	    
		}
	}	
	
	//till here code is working. below is loop to debug.
	printf("\n");
	for(int i=0; i<countQ1; i++){
		printf("p: %d  b: %d\n",fcfs[i].priority,fcfs[i].burstTime);
	}
	



	printf("\n\nFor Shortest Job First");
	int index=0;
	struct data sjf[countQ2];
	for(int i = 0;i<p;i++)
	{
		if(info[i].priority>=11 & info[i].priority<=20)
		{
			sjf[index] = info[i];
			index++;
		}
	}
	
	//sorting processes according to there burst time.
	sjfSort(sjf);

	printf("\n");
	for(int i=0; i<countQ2; i++){
		printf("p: %d  b: %d\n",sjf[i].priority,sjf[i].burstTime);
	}
	

	printf("\n\nFor Round Robin ");
	index=0;
	struct data roundRobin[countQ3];
	for(int i = 0;i<p;i++)
	{
		if(info[i].priority>=21 & info[i].priority<=30)
		{
			roundRobin[index] = info[i];
			index++;
		}
	}
	
	//sorting processes according to there burst time.
	//sjfSort(sjf);

	printf("\n");
	for(int i=0; i<countQ3; i++){
		printf("p: %d  b: %d\n",roundRobin[i].priority,roundRobin[i].burstTime);
	}

	startProcessing(fcfs, sjf, roundRobin, info);

	printf("\n");

	for(int i=0; i<p; i++){

		printf("%d\n", info[i].processId);

	}

	return 0;
	
}


//method to sort the data in ascending order.
void sjfSort(struct data sjf[]){

	for(int i=0; i<countQ2-1; i++){
		for(int j=i+1; j<countQ2; j++){

			if(sjf[i].burstTime > sjf[j].burstTime){
				struct data temp = sjf[i];
				sjf[i] = sjf[j];
				sjf[j] = temp;
			}

		}
	}

}


//method to start processing
void startProcessing(struct data fcfs[], struct data sjf[], struct data roundRobin[], struct data info[]){

	for(int i=0; i<totWaitTime; i+=30){
		startRounRobin(roundRobin,info);
		startRounSJF(sjf,info);
		startRounFCFS(fcfs,info);
	}

}

//method of RoundRobin processs
void startRounRobin(struct data roundRobin[], struct data info[]){
	int count = bQuanta;
	int quanta = sQuanta;

	for(int i=0; i<countQ3 && count > 0; i++){

		if(roundRobin[i].burstTime > quanta){

			roundRobin[i].burstTime = roundRobin[i].burstTime - quanta;
			count = count - 4;
		}else{

			roundRobin[i].burstTime = 0;
			count = count - roundRobin[i].burstTime;
			info[totP++] = roundRobin[i];
		}

	}

	if(count < 1)
		return;

}

//method of RoundRobin processs q2
void startRounSJF(struct data sjf[], struct data info[]){
	
	int quanta = 10;

	for(int i=0 ; i<countQ2; i++){
		
		if(sjf[i].burstTime > quanta){

			sjf[i].burstTime = sjf[i].burstTime - quanta;
			quanta = 0;

		}else{

			sjf[i].burstTime = 0;
			quanta = quanta - sjf[i].burstTime;
			info[totP++] = sjf[i];
		}

		if(quanta < 1)
			return;
		else
			continue;
	}

}

//method of RoundRobin processs q1
void startRounFCFS(struct data fcfs[], struct data info[]){
	
	int quanta = 10;

	for(int i=0 ; i<countQ1; i++){
		
		if(fcfs[i].burstTime > quanta){

			fcfs[i].burstTime = fcfs[i].burstTime - quanta;
			quanta = 0;

		}else{

			fcfs[i].burstTime = 0;
			quanta = quanta - fcfs[i].burstTime;
			info[totP++] = fcfs[i];

		}

		if(quanta < 1)
			return;
		else
			continue;
	}


