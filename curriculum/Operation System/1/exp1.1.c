#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

void an_ch2_1b()
{
	while(1)
	{
		time_t t;
		time(&t);
		printf("Those output come from child,%ld\n",t);
		sleep(1);
	}
}

void an_ch2_1a()
{
	__pid_t pid;
	pid = fork();
    if(pid==0)
    {
        an_ch2_1b();
    }
	else if(pid > 0)
	{
		while (1)
		{
			time_t t;
			time(&t);
			printf("Those output come from parent,%ld\n",t);
			sleep(1);
		}
	}
}

int main(int argc,char *argv[])
{
	an_ch2_1a();
	return 0;
}

