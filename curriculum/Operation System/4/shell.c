#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h> 
#include <string.h>
#define TRUE 1
#define N 256
#define GREEN "\e[1;32m"
#define BLUE "\e[1;34m"
#define RED "\e[1;31m"
#define YELLOW "\e[1;33m"
#define WHITE "\e[0m"

void type_prompt() 
{   //type_prompt()采取“用户名@主机名：目录+prompt”的形式，且如果为root用户，prompt为#，普通用户为$。
	char hostname[N] = { '\0' };
	gethostname(hostname, sizeof(hostname));    //获取主机名

	char curpath[N] = { '\0' };
	getcwd(curpath, N);   //获取当前目录

    char cwdcopy[N];
    strcpy(cwdcopy,curpath);
    const char *delim = "/";
    char* first=strtok(cwdcopy, delim);     //取目录的第一个单词
    char* second=strtok(NULL, delim);       //取目录的第二个单词

    if(!(strcmp(first,"home"))&&!(strcmp(second,getpwuid(getuid())->pw_name)))  //如果是home+用户名，改为~
    {
        int shift=strlen(first)+strlen(second)+2;
        char tmp[N];
        strcpy(tmp,"~");
        strcat(tmp,curpath+shift);
        strcpy(curpath,tmp);
    }

	char prompt = '$';
	if (geteuid() == 0)    //判断是否为root用户
    {
		prompt = '#';
	}

	//printf("%s@%s:%s%c", getpwuid(getuid())->pw_name, hostname, curpath, prompt);
    printf(RED "shell>");
	printf(BLUE "%s@%s", getpwuid(getuid())->pw_name, hostname);
    printf(WHITE ":");
	printf(GREEN "%s", curpath);
	printf(YELLOW "%c", prompt);
    printf(WHITE " ");
}

int background=0;

char** read_command() 
{
    background=0;
	char cmd[N];
	fgets(cmd, N, stdin);

	const char *delim = " \n\t\r";
	int num = 0;
	char copy[N];
	strcpy(copy, cmd);
	char *p = strtok(copy, delim);  //首先使用strtok()函数判断命令分为几部分（按照空格分开），然后创建一个char*数组保存命令并返回。
	while (p != NULL) 
    {
		p = strtok(NULL, delim);
		num++;
	}
	
	char **argv = (char**)malloc((num+1) * sizeof(char*));
	for (int i = 0; i < num; i++) {
		argv[i] = (char*)malloc(N * sizeof(char));
	}

	num = 0;
	strcpy(copy, cmd);
	p = strtok(copy, delim);
	while (p != NULL) {
		strcpy(argv[num], p);
		p = strtok(NULL, delim);
		num++;
	}
	argv[num] = (char *)0;
    if(num>1&&!strcmp(argv[num-1],"&")) background=1;    //最后一个字符是&，后台命令

	return argv;
}

void help()
{
    printf("$exit\t:退出程序\n$help\t:帮助列表\n");
    printf("$cd\t:更改当前工作目录，支持：\n\tcd \t:回到用户家目录\n\tcd ~\t:回到用户家目录\n\tcd ['/'或'~'开头的绝对路径]\n\tcd [相对路径]\n");
    printf("$ls\t:显示指定工作目录下之内容\n$pwd\t:显示当前目录\n");
    printf("$[可执行程序或脚本]\n");
}


int main()
{
    int work_num=0;
	while (TRUE)     //一直循环下去
	{
		type_prompt();  //在屏幕显示提示符N
		char* envp[] = { "PATH=/bin",0 };
		char** argv= read_command();    //从终端读取输入

        //exit when command is exit
        if(argv[0]==NULL) continue;
        else if(!strcmp(argv[0],"exit"))        //exit命令
        {   exit(EXIT_SUCCESS); }
        else if(!strcmp(argv[0],"help"))        //help命令
        {   help(); }
        else if(!strcmp(argv[0],"pwd"))        //pwd命令
        {   
            char path[N] = { '\0' };
            getcwd(path,N);
            puts(path);
        }
        else if(!strcmp(argv[0],"cd"))          //cd命令
        {
            char cd_path[N] = { '\0' };
            if(argv[1]==NULL||!strcmp(argv[1],"~"))     //无参数或参数为~
            {
                sprintf(cd_path,"/home/%s",getpwuid(getuid())->pw_name);
            }
            else if (argv[1][0]=='/')  //绝对路径开头为/
            {   
                strcpy(cd_path,argv[1]);
            }
            else if (argv[1][0]=='~')  //绝对路径开头为~
            {
                sprintf(cd_path,"/home/%s%s",getpwuid(getuid())->pw_name,argv[1]+1);
            }
            else        //相对路径
            {
                getcwd(cd_path,N);
                strcat(cd_path,"/");
                strcat(cd_path,argv[1]);
            }
            //do cd
            if((chdir(cd_path))<0)
            {   printf("cannot cd to: %s\n",cd_path);   }
        }
        else        
        {   
            struct timeval t1,t2;
            long sta,end;
            gettimeofday(&t1,NULL);
            sta = t1.tv_sec * 1000 + t1.tv_usec/1000;
            
            char* file=argv[0]; //可执行程序或脚本
            if(!strcmp(argv[0],"ls"))   file="/bin/ls";     //ls命令
            __pid_t pid=0;
            __pid_t pid2=0;
            if(background)  //有后台命令
            {   
                work_num++;
                pid=fork();
                if(pid!=0)
                    printf("[%d] %d: 后台命令$%s开始执行\n",work_num,pid,argv[0]);
                if (pid == 0)   //子进程fork
                {
                    //派生子进程
                    pid2=fork();
                    if (pid2 != 0) {  //父代码
                        waitpid(pid2, NULL, 0);   //等待子进程退出
                    }
                    else {  //子代码
                        printf("\n");
                        execve(file, argv, envp);  //执行命令
                    }
                }
            }
            else
            {
                //派生子进程
                __pid_t tmp=fork();
                if (tmp != 0) {  //父代码
                    waitpid(tmp, NULL, 0);   //等待子进程退出
                }
                else {  //子代码
                    execve(file, argv, envp);  //执行命令
                }
            }
            
            if(pid==0)
            {
                if (pid2 != 0) 
                    printf("[%d] 后台命令: %s执行完成\n",work_num,argv[0]);
                gettimeofday(&t2,NULL);
                end = t2.tv_sec * 1000 + t2.tv_usec/1000;

                struct rusage buf;
                getrusage(RUSAGE_CHILDREN,&buf);
                printf("1) 命令占用的CPU时间:\n   用户态时间: %ldms\n   系统态时间: %ldms\n", 
                (long)buf.ru_utime.tv_usec/1000, (long)buf.ru_stime.tv_usec/1000);
                printf("2) 命令执行的时间: %ldms\n",end-sta);
                printf("3) 进程被抢占的次数: %ld\n",buf.ru_nivcsw);    // involuntary context switches 
                printf("4) 进程主动放弃CPU的次数: %ld\n",buf.ru_nvcsw);  // voluntary context switches 
                printf("5) 进程执行过程中发生缺页的次数: %ld\n",buf.ru_minflt);   // page faults 
                if (pid2 != 0) exit(EXIT_SUCCESS);  //后台进程执行完退出
            }
        }
	}
	return 0;
}
