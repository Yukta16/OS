#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>



#define MIN_PID 100
#define MAX_PID 1000


pthread_mutex_t L;

struct process {
	int pid,Alloc;
}arr[MAX_PID-MIN_PID];

int allocate_map() { 
	int i; 
	for(i=MIN_PID;i<=MAX_PID;i++) 
	{
		arr[i-MIN_PID].pid=i;
		arr[i-MIN_PID].Alloc=0;
	}
	return 1;
}


void* func(void *i) 
{
	printf("A new process is created.\n");

}

void CreateP() {
	int i=0;
	pthread_t a[6]; 
	if(pthread_mutex_init(&L,NULL)!=0)
	{
		printf("Mutex init.");
	}	
	while(i<6) {
		pthread_create(&a[i],NULL,func,NULL);
		i++;
	}
	
	i=0;
	while(i<6) {
		pthread_join(a[i],NULL);
		i++;
	}	
}


int main() {
	allocate_map();
		CreateP();
	}

