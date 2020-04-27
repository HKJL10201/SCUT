#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define TRUE 1

int shared_var = 0;

void *child()
{
	while(TRUE)
	{
		sleep(1);
		shared_var--;
		printf("Chil:%d\n",shared_var);
	}
	pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
	pthread_t th;
	int status;
	int i=0;
	status = pthread_create(&th,NULL,child,NULL);
	if(status!=0)
	{
		printf("pthread_create returned error code %d\n", status);
		exit(-1);
	}
	while(TRUE)
	{
		sleep(1);
		shared_var++;
		printf("Main:%d\n",shared_var);
	}
	return 0;
}
