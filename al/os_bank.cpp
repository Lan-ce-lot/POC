#include<stdio.h>
#include<math.h>
#include <stdbool.h>//linux系统下bool类型的引用
#define max 10
int resourceNum;//资源种类 
int processNum;//资源数目 
int available[max];//进程的最大需求
int maxRequest[max][max];//进程已经分配资源
int allocation[max][max]={0};//进程还需要资源
int need[max][max];//是否安全
bool Finish[max];//安全序列号
int safeSeries[max]={0,0,0,0,0};//进程请求资源量
int request[max];//资源数量计数
int num;
void showInfo()//打印输出系统信息
{
    printf("\n---------------------------------------------------\n");
    printf("当前系统各类资源剩余：");
    for(int j = 0; j < resourceNum; j++)
    {
        printf("%d ",available[j]);
    }
    printf("\n当前系统资源情况：\n");
    printf("    \t Max\t\tAllocation\t Need\n");
    for(int i = 0; i < processNum; i++)
    {
        printf(" P%d\t",i);
        for(int j = 0; j < resourceNum; j++)
        {
            printf("%2d",maxRequest[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < resourceNum; j++)
        {
            printf("%2d",allocation[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < resourceNum; j++)
        {
            printf("%2d",need[i][j]);
        }
        printf("\n");
    }
}
void SafeInfo(int *work, int i)//打印安全检查信息
{
    int j;
    printf(" P%d\t",i);
    for(j = 0; j < resourceNum; j++)
    {
        printf("%2d",work[j]);
    }
    printf("\t\t");
    for(j = 0; j < resourceNum; j++)
    {
        printf("%2d",allocation[i][j]);
    }
    printf("\t\t");
    for(j = 0; j < resourceNum; j++)
    {
        printf("%2d",need[i][j]);
    }
    printf("\t\t");
    for(j = 0; j < resourceNum; j++)
    {
        printf("%2d",allocation[i][j]+work[j]);
    }
    printf("\n");
}
bool isAllZero(int no)//判断一个进程的资源是否全为零
{
    num = 0;
    for(int i = 0; i < resourceNum; i++ )
    {
        if(need[no][i] == 0)
        {
            num ++;
        }
    }
    if(num == resourceNum)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isSafe()//安全检查
{
    int i,j,k;
    int trueFinished = 0;
    int work[resourceNum];
    for(i = 0; i < resourceNum; i++){
        work[i]=available[i];
    }

    for(i = 0; i < processNum; i++){
        Finish[i]=false;
    }
    i = 0;
    int temp = 0;
    while(trueFinished != processNum){
        int j =0;
        if(Finish[i]!= true){
            for(j = 0; j < resourceNum; j++){
                if(need[i][j] > work[j]){break;}
            }
        }
        if(j == resourceNum){
            Finish[i]=true;
            SafeInfo(work,i);
            for(k = 0; k < resourceNum; k++){
                work[k]+=allocation[i][k];
            }
            int k2;
            safeSeries[trueFinished++] = i;
        }
        i++;
        if(i >= processNum)
        {
            i = i % processNum;
            if(temp == trueFinished)
                break;
        }
        temp = trueFinished;
    }
    if(trueFinished == processNum){
        printf("\n系统安全！\n安全序列为：");
        for(i = 0; i < processNum; i++){
            printf("%d ",safeSeries[i]);
        }
        return true;
    }
    printf("系统不安全!\n");
    return false;
}
int main()
{
    int i,j;
    printf("输入进程需要的资源种类数目：");
    scanf("%d",&resourceNum);
    printf("\n输入进程数目：");
    scanf("%d",&processNum);
    printf("输入各资源种类剩余数目：");
    for(i=0;i<resourceNum;i++)
    {
        printf("第%d个资源：",i+1);
        scanf("%d",&available[i]);
    }
    printf("输入各进程的最大需求：");
    for(i=0;i<processNum;i++)
    {
        printf("进程p%d：",i);
        for(j=0;j<resourceNum;j++)
        {
            scanf("%d",&maxRequest[i][j]);
        }
    }
    printf("输入各进程已分配情况：");
    for(i=0;i<processNum;i++)
    {
        printf("进程p%d：",i);
        for(j=0;j<resourceNum;j++)
        {
            scanf("%d",&allocation[i][j]);
            need[i][j]=maxRequest[i][j]-allocation[i][j];
            available[j]=available[j]-allocation[i][j];
        }
    }
    int curProcess = 0;
    int a = -1;
    showInfo();
    printf("\n系统安全情况分析\n");
    printf("    \t Work\t\tAllocation\t Need\t\tWork+Allocation\n");
    bool isStart = isSafe();
    while(isStart)
    {
        do{
            printf("\n---------------------------------------------------\n");
            printf("\n输入要分配的进程：");
            a = scanf("%d",&curProcess);
            printf("\n");
        }while(curProcess >= processNum || a == 0);
        for(int i = 0; i < resourceNum; i++)
        {
            do
            {
                printf("请输入要分配给进程 P%d 的第 %d 类资源：",curProcess,i+1);
                a = scanf("%d", &request[i]);
            }while( a == 0);
        }
        //判断用户输入的分配是否合理，如果合理，开始进行预分配
        num  = 0;
        for(int i = 0; i < resourceNum; i++)
        {
            if(request[i] <= need[curProcess][i] && request[i] <= available[i])
            {
                num ++;
            }
            else
            {
                printf("\n发生错误！\n");
                break;
            }
        }
        if(num == resourceNum)
        {
            num = 0;
            for(int j = 0; j < resourceNum; j++)
            {
                //分配资源
                available[j] = available[j] - request[j];
                allocation[curProcess][j] = allocation[curProcess][j] + request[j];
                need[curProcess][j] = need[curProcess][j] - request[j];
                //记录分配以后，是否该进程需要值为0了
                if(need[curProcess][j] == 0)
                {
                    num ++;
                }
            }
            //如果分配以后出现该进程对所有资源的需求为0了，即刻释放该进程占用资源
            if(num == resourceNum)
            {
                //释放已完成资源
                for(int i = 0; i < resourceNum; i++ )
                {
                    available[i] = available[i] + allocation[curProcess][i];
                }
                printf("\n\n本次分配进程 P%d 完成,该进程占用资源全部释放完毕！\n",curProcess);
            }
            else
            {
                //资源分配可以不用一次性满足进程需求
                printf("\n\n本次分配进程 P%d 未完成！\n",curProcess);
            }
            showInfo();
            printf("系统安全情况分析\n");
            printf("    \t Work\t\tAllocation\t Need\t\tWork+Allocation\n");
//预分配完成以后，判断该系统是否安全，若安全，则可继续进行分配，若不安全，将已经分配的资源换回来
            if(!isSafe())
            {
                for(int j = 0; j < resourceNum; j++)
                {
                    available[j] = available[j] + request[j];
                    allocation[curProcess][j] = allocation[curProcess][j] - request[j];
                    need[curProcess][j] = need[curProcess][j] +request[j];
                }
                printf("资源不足！分配失败！\n");
            }
        }
    }
}