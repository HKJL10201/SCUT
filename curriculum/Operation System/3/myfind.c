#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define N 512

char* results[N];
int res_count=0;

int equal(char* tar,char* src)
{
    int len=strlen(src);
    int len2=strlen(tar);
    int i=0,j=0;
    for(i=0;i<len;i++)
    {
        if(src[i]=='*')
        {
            if(i<len-1) i++;
            else break;
            while(tar[j]!=src[i])
            {
                if(j<len2-1) j++;
                else return 0;
            }
            if(j<len2-1) j++;
            continue;
        }
        if(src[i]=='?'||tar[j]==src[i])
        {
            if(j<len2-1) j++;
            continue;
        }
        else return 0;
    }
    return 1;
}

void find(char* path,char* target,char* prune,char* m_time,char* c_time,char* exec)
{
    //printf("entry: %s, target: %s, prune: %s\n",path,target,prune);
    DIR* dp;
    if((dp=opendir(path)) == NULL)  //打开当前目录
    {
        printf("无法访问路径: %s\n", path);
        closedir(dp);
        return;
    }
    struct dirent* dirp;
    while((dirp=readdir(dp)) != NULL)   //读当前目录的每个文件
    {
        //puts(dirp->d_name);
        struct stat buf;
        char* str;
        char dir[N];
        //得到读取文件的绝对路径名
        snprintf(dir, N, "%s/%s", path, dirp->d_name);
        if(lstat(dir,&buf)<0)
        {
            printf("无法访问文件: %s\n", dir);
            continue;
        }
        //过滤..和.目录
        if(strcmp(dirp->d_name, ".")==0||strcmp(dirp->d_name, "..")==0) continue;
        //判断是目录还是文件
		if (S_ISDIR(buf.st_mode))
		{   //跳过prune不搜索
            if(prune==NULL || strcmp(prune,dirp->d_name)!=0)
            {
                find(dir,target,prune,m_time,c_time,exec);  //递归查询
            }
		}
        else
        {   //如果找到了目标文件
            if(equal(dirp->d_name,target))
            {
                if(m_time!=NULL||c_time!=NULL)  //时间判断
                {
                    int before=0;   //是否有+
                    int days=0;
                    time_t threshold;
                    if(m_time!=NULL)
                    {
                        if(m_time[0]=='+')before=1; //如果是'+'，取n天前
                        days=atoi(m_time+1);
                        time(&threshold);
                        threshold-=(long)days*86400; //24*60*60
                        if(before&&buf.st_mtime>threshold||!before&&buf.st_mtime<threshold)
                            continue;
                    }
                    if(c_time!=NULL)
                    {
                        if(c_time[0]=='+')before=1;
                        days=atoi(c_time+1);
                        time(&threshold);
                        threshold-=(long)days*86400; //24*60*60
                        if(before&&buf.st_ctime>threshold||!before&&buf.st_ctime<threshold)
                            continue;
                    }
                }
                size_t len=strlen(dir);     //目标路径dir的长度
                results[res_count]=(char*)malloc((len+1)*sizeof(char)); //新建字符串
                strncpy(results[res_count],dir,len);    //复制字符串：dir存入results表
                results[res_count][len]='\0';       //手动设置字符串末尾标记
                res_count++;
            }
        }
    }
    closedir(dp);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
	{
		printf(" Usage:%s <PATH> <-option> [-print] [-exec <command>]\n",argv[0]);
		return -1;
	}
    char* path=(char*)argv[1];
    char* name=NULL;
    char* prune=NULL;
    char* mtime=NULL;
    char* ctime=NULL;
    char* exec=NULL;
    int print=0;

    int i=0;    //counter
    int opt=0;      //读取命令的option类型
    for(i=2;i<argc;i++)
    {
        if(!opt)    //opt=0时，接下来一个参数读入某种option
        {
            /*if(i==argc-1)   //最后的option命令没有具体操作
            {
                printf("invalid syntax: %s <argument>\n",argv[i]);
                return -1;
            }*/
            if(strcmp(argv[i],"-name")==0) opt=1;
            else if(strcmp(argv[i],"-prune")==0) opt=2;
            else if(strcmp(argv[i],"-mtime")==0) opt=3;
            else if(strcmp(argv[i],"-ctime")==0) opt=4;
            else if(strcmp(argv[i],"-exec")==0) opt=5;
            else if(strcmp(argv[i],"-print")==0)
            {   opt=0;print=1;  }
            else        //输入的操作参数不是上述的任何一种
            {
                printf("invalid syntax: %s\n",argv[i]);
                return -1;
            }
        }
        else    //opt>0时，下一个参数读入option的具体内容
        {
            switch (opt)
            {
            case 1: name=(char*)argv[i];opt=0;break;
            case 2: prune=(char*)argv[i];opt=0;break;
            case 3: mtime=(char*)argv[i];opt=0;break;
            case 4: ctime=(char*)argv[i];opt=0;break;
            case 5: exec=(char*)argv[i];opt=0;break;
            default: opt=0;break;
            }
        }
    }
    if(name==NULL)
    {   //没有输入查找文件名则报错
        puts("Error: require '-name <filename>' option");
        return -1;
    }
    //puts(name);

    find(path,name,prune,mtime,ctime,exec);
    //输出结果
    if(print)
    {
        if(res_count)
        {
            int _=0;
            for(_=0;_<res_count;_++)
            {
                printf("%s\n",results[_]);
            }
        }
        else printf("no result\n");
    }
    
    return 0;
}
