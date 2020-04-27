#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAX 50
#define TRUE 1

//用于储存生产的字母
struct Cache{
    int written;    //储存的字母数量
    char text[MAX]; //字母列表
    int rear,head;  //列表的头和尾下标
};

int Up(int semid,int sem_num){
	struct sembuf buf={sem_num,+1,SEM_UNDO};
	if(semop(semid,&buf,1)==-1){
		perror("Up failed.\n");
		return 0;
	}
	return 1;
}

int Down(int semid,int sem_num){
	struct sembuf buf={sem_num,-1,SEM_UNDO};
	if(semop(semid,&buf,1)==-1){
		perror("Down failed.\n");
		return 0;
	}
	return 1;
}

int main(int argc,char *argv[])
{
    key_t key;
    char * path="./tmp";
    key=ftok(path,1);   //把路径名和一个整数标识符转换成IPC键值
    if(key==-1)perror("key error.\n");

    int shmid = shmget(key, sizeof(char), IPC_CREAT|0604);
    if(shmid==-1) perror("shmid error.\n");

    int semid = semget(key, 4, IPC_CREAT|0666);
    if(semid==-1) perror("semid error\n");

    semctl(semid, 0, SETVAL, 1);  //mutex1：生产者互斥信号量
    semctl(semid, 1, SETVAL, 1);  //mutex2：消费者互斥信号量
    semctl(semid, 2, SETVAL, 0);  //full_sem
    semctl(semid, 3, SETVAL, MAX);  //empty_sem

    struct Cache *  cache;
    if ((cache = (struct Cache *)shmat(shmid, NULL, 0)) == (void *)-1) 
    {   perror("shmat error.\n");   }
    cache->written=0;
    cache->rear=0;
    cache->head=0;

    __pid_t pid[4];
    int i;
    for(i=0;i<4;i++){
        pid[i]=fork();
        if(pid[i]==-1||pid[i]==0)break;
    }
    if(pid[i]==-1)perror("fork error.\n");
    else if(pid[i]==0)
    {
        if(i==0||i==1)  //producer
        {
            while(TRUE)
            {
                int x=rand()%26;
                char a;
                if(i==0)a='a';
                else a='A';
                a+=x;
                Down(semid,3);      //down empty_sem
                Down(semid,0);      //down mutex1
                (cache->written)++;     //字母数+1
                cache->text[cache->rear]=a;     //将a添加到列表末尾
                cache->rear=(cache->rear+1)%MAX;    //列表末尾下标+1
                printf("produce: %c; remain: ", a);
                int j;
                for(j=0;j<cache->written;j++)       //显示缓存列表所有字母
                {   printf("%c", cache->text[(cache->head+j)%MAX]);  }
                printf("\n");
                sleep(2);
                Up(semid,0);        //up mutex1
                Up(semid,2);        //up full_sem
            }
        }
        else
        {
            while (TRUE)        //consumer
            {
                Down(semid,2);      //down full_sem
                Down(semid,1);      //down mutex2
                (cache->written)--;     //缓存字母数-1
                char a=cache->text[cache->head];    //取列表头字母到a
                cache->head=(cache->head+1)%MAX;    //列表头+1
                printf("consume: %c; remain: ", a);
                int j;
                for(j=0;j<cache->written;j++)
                {   printf("%c", cache->text[(cache->head+j)%MAX]);  }
                printf("\n");
                sleep(3);
                Up(semid,1);      //up mutex2
                Up(semid,3);      //up empty_sem
            }
        }
    }
    else        //main p
    {
        while (TRUE)        //consumer
        {
            Down(semid,2);      //down full_sem
            Down(semid,1);      //down mutex2
            (cache->written)--;
            char a=cache->text[cache->head];
            cache->head=(cache->head+1)%MAX;
            printf("consume: %c; remain: ", a);
            int j;
            for(j=0;j<cache->written;j++)
            {   printf("%c", cache->text[(cache->head+j)%MAX]);  }
            printf("\n");
            sleep(3);
            Up(semid,1);      //up mutex2
            Up(semid,3);      //up empty_sem
        }
    }
    return 0;
}