#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define TRUE 1
#define N 5
typedef int semaphore;

semaphore studio = 1;   //工作室的空椅子数量
semaphore empty = N;    //接待室的空座位数量
semaphore full = 0;     //接待室有人座位数量

void asleep()
{
    if(studio--)        //占用工作室空椅子并睡觉
    {
        while (studio==0)   //没有顾客叫醒时继续睡
        {
            printf("sleeping\n");
            sleep(1);
        }
    }
}

void wake_up()
{
    studio++;       //叫醒理发师时工作室空位加一
    printf("一位顾客叫醒了理发师 -awake\n");
}

void *barber()
{
	while(TRUE)
	{
        while (full)        //接待室有人时
        {
            printf("开始理发，剩余%d人 -begin\n",full);
            full--;
		    sleep(rand()%3+1);       //理发中
            printf("理发完成，还有%d人 -end\n",full);
            empty++;        //空位加一
        }
		asleep();       //没有新顾客则睡觉
	}
	pthread_exit(NULL);
}

void *customer()
{
    if(empty)       //如果有空位
    {
        empty--;    //占据空位
        full++;
        printf("有新顾客来了，店内共有%d人\n", N-empty);
        if(studio==0) wake_up();    //如果理发师在睡觉，叫醒他
    }
    else printf("没有空位，一位顾客离开了 -leave\n");  //没有空位直接离开
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
	pthread_t baber, cunstomers;
	int status;
	status = pthread_create(&baber, NULL, barber, NULL);    //创建理发师线程
	if(status!=0)
	{
		printf("pthread_create returned error code %d\n", status);
		exit(-1);
	}
	while(TRUE)
	{
		sleep(rand()%5);    //随机创建顾客线程
		status = pthread_create(&cunstomers, NULL, customer, NULL);
		if(status!=0)
        {
            printf("pthread_create returned error code %d\n", status);
            exit(-1);
        }
	}
	return 0;
}
