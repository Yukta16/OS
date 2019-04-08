#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


#define MIN_PID 100
#define MAX_PID 1000


pthread_mutex_t L;

struct process 
	{
	int pid,Alloc;
	}arr[MAX_PID-MIN_PID];

int allocate_map() { 
	
	for(int i=MIN_PID;i<=MAX_PID;i++) 
	{
		
		arr[i-MIN_PID].pid=i;
		arr[i-MIN_PID].Alloc=0;
	}
	return 1;
}


int allocate_pid()    
{  
		for(int i=0;i<MAX_PID;i++)
		{
				if (arr[i].Alloc==0) 
				{
						pthread_mutex_lock(&L);
						arr[i].Alloc=1;
						pthread_mutex_unlock(&L); 
						return arr[i].pid;
				}
		}
	return -1; 
}


void* func(void *i) 
{
		int pid=allocate_pid();
	printf("A new process %d is created.\n",pid);
}

void CreateP() 
	{
	
				pthread_t a[6]; 
	
				if(pthread_mutex_init(&L,NULL)!=0)
						{
							printf("Mutex initialized");
						}	
				for(int i=0;i<6;i++) 
						{
							pthread_create(&a[i],NULL,func,NULL);
						}
	
	
				for(int i=0;i<6;i++) 
						{
							pthread_join(a[i],NULL);
		
						}	
	}


int main() 
	{
		allocate_map();
		CreateP();
	}
