#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define TRUE 1
typedef int semaphore;

int readcount=0, writecount=0;
semaphore mutex1=1; //reader进入或离开的互斥信号量
semaphore mutex2=1; //writer进入或离开的互斥信号量
semaphore mutex3=1; //保证reader独占访问从Down(r)到Up(r)的代码块，在r处最多会有一个进程等待
semaphore w=1;      //w对于writer来说是一个互斥信号量
semaphore r=1;      //读写操作的互斥锁

void *reader(void *tid)
{
    printf("创建了新的reader: reader%d\n",tid);

    //Down(mutex3);   
    while (mutex3==0)//没有mutex3，可能有一个writer和多个reader同时等待Down(r)被一个reader完成，则不能保证writer的优先级
    {   printf("reader%d: waiting for mutex3\n",tid);
        sleep(1);
    } mutex3--;

    //Down(r); 
    while (r==0)//只有当r=1，即最后一个writer写完时reader可以进入
    {   printf("reader%d: waiting for r\n",tid);
        sleep(1);
    } r--;

    //Down(mutex1);   
    while (mutex1==0)//mutex1互斥确保一次只有一个reader进入或离开，从而消除了由哪个进程负责调整w的可能性
    {   printf("reader%d: waiting for mutex1\n",tid);
        sleep(1);
    } mutex1--;

    readcount++;
    printf("reader%d进入了等待队列，共有：%d\n",tid,readcount);

    if(readcount==1)    //readcount从0变1，给writer上锁
    {   //Down(w);
        while (w==0)
        {   printf("reader%d: waiting for w\n",tid);
            sleep(1);
        } w--;
    }

    mutex1++;   //Up(mutex1);
    r++;        //Up(r);
    mutex3++;   //Up(mutex3);
    
    //reading
    int i=0,t=rand()%5+1;
    for(i=0;i<t;i++)
    {
        printf("reader%d: reading\n",tid);
        sleep(1);
    }
    printf("reader%d: done\n",tid);
    //reading is done

    //Down(mutex1);   
    while (mutex1==0)//mutex1互斥确保一次只有一个reader进入或离开
    {   printf("reader%d: waiting for mutex1\n",tid);
        sleep(1);
    } mutex1--;

    readcount--;
    printf("剩余readers: %d\n",readcount);

    if(readcount==0) w++;   //Up(w);     //readcount从1变0，给writer解锁
    mutex1++;   //Up(mutex1);
	pthread_exit(NULL);
}

void *writer(void *tid)
{
    printf("创建了新的writer: writer%d\n",tid);

    //Down(mutex2);
    while (mutex2==0)//mutex2互斥确保一次只有一个writer进入或离开，从而消除了由哪个进程负责调整r的可能性
    {   printf("writer%d: waiting for mutex2\n",tid);
        sleep(1);
    } mutex2--;

    writecount++;
    printf("writer%d进入了等待队列，共有：%d\n",tid,writecount);

    if(writecount==1) //writecount从0变1，给reader上锁
    {   //Down(r);
        while (r==0)
        {   printf("writer%d: waiting for r\n",tid);
            sleep(1);
        } r--;
    }

    mutex2++;    //Up(mutex2);

    //Down(w);
    while (w==0)    //互斥确保一次只有一个writer进行写操作
    {   printf("writer%d: waiting for w\n",tid);
        sleep(1);
    } w--;

    //writing
    int i=0,t=rand()%5+1;
    for(i=0;i<t;i++)
    {
        printf("writer%d: writing\n",tid);
        sleep(1);
    }
    printf("writer%d: done\n",tid);
    //writing is done
    w++;    //Up(w);

    //Down(mutex2);
    while (mutex2==0)//mutex2互斥确保一次只有一个writer进入或离开
    {   printf("writer%d: waiting for mutex2\n",tid);
        sleep(1);
    } mutex2--;

    writecount--;
    printf("剩余writers: %d\n",writecount);

    if(writecount==0) r++;  //Up(r);    //writecount从1变0，给reader解锁
    mutex2++;    //Up(mutex2);
	pthread_exit(NULL);
}

void *reader_creater()
{
    pthread_t readers;
    int status,i=1;
    while (TRUE)
    {
        sleep(rand()%5);    //随机创建reader
		status = pthread_create(&readers, NULL, reader,  (void*)i);
        i++;
		if(status!=0)
        {
            printf("pthread_create returned error code %d\n", status);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t readers, writers;
	int status,i=1;
	status = pthread_create(&readers, NULL, reader_creater, NULL);
	if(status!=0)
	{
		printf("pthread_create returned error code %d\n", status);
		exit(-1);
	}
	while(TRUE)
	{
		sleep(rand()%5);    //随机创建writer
		status = pthread_create(&writers, NULL, writer, (void*)i);
        i++;
		if(status!=0)
        {
            printf("pthread_create returned error code %d\n", status);
            exit(-1);
        }
	}
    return 0;
}
