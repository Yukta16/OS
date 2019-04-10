#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<pthread.h>
#include<time.h>
#include<conio.h>

#define MIN_PID 100
#define MAX_PID 1000


pthread_mutex_t L;

struct process 
	{
			int pid,Alloc;
	}arr[MAX_PID-MIN_PID];


int allocate_map() { // Creates and initializes a data structure for representing pids; returns—1 if unsuccessful, 1 if successful
	
	if (MIN_PID<MAX_PID)    
		{            
			for(int i=MIN_PID;i<=MAX_PID;i++) 
				{
					arr[i-MIN_PID].pid=i;
					arr[i-MIN_PID].Alloc=0;
				}
			return 1;
		}
	
	else               //Since, the data structure won't be created only if max<min
	{
		return -1;
	}
}

int allocate_pid()    // Allocates and returns a pid; returns— 1 if unable to allocate a pid (all pids are in use) 
{  
	int i;
		for(i=0;i<MAX_PID;i++)
		{
				if (arr[i].Alloc==0) 
				{
						pthread_mutex_lock(&L);
						arr[i].Alloc=1;
						pthread_mutex_unlock(&L); // lock only while changing
						return arr[i].pid;
				}
		}
	return -1;  //returns -1 once i>=max_pid
}

void release_pid(int pid)      //Releases a pid 
{
	
	for(int i=0;i<MAX_PID;i++)
	{
	
		if(arr[i].pid==pid) 
		{
			pthread_mutex_lock(&L);
			arr[i].Alloc=0;
			pthread_mutex_unlock(&L);
			break;
		}

	}
}

void* func(void *) 
{
	int pid=allocate_pid();
	printf("A new process %d is created.\n",pid);

	int time=(rand());
	Sleep(time);  //puts the process to sleep once it is created. So that all the processes can be destroyed once all of them are created.
	
	release_pid(pid);
	printf("Process %d is destroyed.\n",pid);
}

void CreateP() 
	{ int n;
				printf("Enter the number of processes : ");
				scanf("%d",&n);
				pthread_t a[n]; //an array of threads
	
				if(pthread_mutex_init(&L,NULL)!=0)
						{
							printf("Mutex not initialized, an error occured");
						}	
				for(int i=0;i<n;i++) 
						{
							pthread_create(&a[i],NULL,func,NULL);
							Sleep(1);  // makes sure the processes are created in order
						}
		
				for(int i=0;i<n;i++) 
						{
							pthread_join(a[i],NULL);
		
						}	
	}
	
	
int main() 
	{
		system("COLOR F2");
		allocate_map();
		CreateP();
	}
