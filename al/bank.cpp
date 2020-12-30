#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50 //最大进程数
#define M 100 //最大资源种类数

int process; //进程的个数
int resource; //资源的种类
int max[N][M]; //最大需求矩阵，即每个进程对每类资源的最大需求
int allocation[N][M];//定义已分配矩阵，即每类资源当前已分配给每个进程的资源数
int need[N][M];//定义需求矩阵，表示每一个进程尚需的各类资源数
int available[M]; //可利用资源向量，表示每种资源的可利用资源数
int request[N][M]; //进程的请求向量, 表示进程申请资源的大小
int safe[N];  //安全序列
int length; //安全序列的长度
int works[N][M];
int finish[N] = { 0 }; //表示系统是否有足够的资源分配给进程，使其运行完成

void menu() {
    printf("------------------choose----------------------\n");
    printf("*              1.初始化数据                  *\n");
    printf("*              2.申请资源                    *\n");
    printf("*              3.显示资源分配情况     	     *\n");
    printf("*              4.退出                        *\n");
    printf("----------------------------------------------\n");
    printf("请选择: ");
}

void display() { //先假定可分配，再进行安全性检查
    printf("资源情况 \t Max \t\t Allocation \t Need \t\t Available\n");
    printf("进程     \t ");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < resource; j++)
        {
            if (j != resource - 1) printf("%c  ", 'A' + j);
            else printf("%c  \t ", 'A' + j);
        }
    printf("\n");

    for (int i = 0; i < process; i++)
    {
        printf(" P%d      \t ", i);
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", max[i][j]);
        }
        printf("\t ");
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", allocation[i][j]);
        }
        printf("\t ");
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", need[i][j]);
        }
        printf("\t ");
        for (int j = 0; i == 0 && j < resource; j++)
        {
            printf("%-3d", available[j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displaySafe() {
    printf("\n----------------------------------该安全序列资源分配情况----------------------------------\n");
    printf("资源情况 \t Work \t\t Need \t\t Allocation \t Work+Allocation \t Finish\n");
    printf("进程     \t ");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < resource; j++)
        {
            if (j != resource - 1) printf("%c  ", 'A' + j);
            else printf("%c  \t ", 'A' + j);
        }
    printf("\n");

    for (int i = 0; i < process; i++)
    {
        printf(" P%d      \t ", safe[i]);
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", works[safe[i]][j]);
        }
        printf("\t ");
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", need[safe[i]][j]);
        }
        printf("\t ");
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", allocation[safe[i]][j]);
        }
        printf("\t ");
        for (int j = 0; j < resource; j++)
        {
            printf("%-3d", works[safe[i]][j] + allocation[safe[i]][j]);
        }
        printf("\t\t ");
        if (finish[i] == 0) printf("false\n");
        else printf("true\n");
    }
    printf("\n");
}

int safeCheck() {
    int safeList[N] = { 0 }, len = 0; //存放安全序列
    int work[M] = { 0 }; //表示系统可提供给进程继续运行所需的各类资源数目
    for (int i = 0; i < N; i++) finish[i] = 0; //表示系统是否有足够的资源分配给进程，使其运行完成

    for (int i = 0; i < resource; i++)
        work[i] = available[i]; //等同于available

    for (int z = 0; z < process; z++)
    {
        for (int i = 0; i < process; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 1;
                for (int j = 0; j < resource; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) //成功找到
                {
                    safeList[len++] = i;
                    //执行当前pi进程到完成
                    for (int j = 0; j < resource; j++) works[i][j] = work[j];
                    for (int j = 0; j < resource; j++)
                    {
                        work[j] += allocation[i][j];
                        //						works[i][j] += allocation[i][j];
                        finish[i] = 1;
                    }
                    break;
                }
            }
        }
    }

    int flag = 1;
    for (int k = 0; k < process; k++)
    {
        if (finish[k] == 0)
        {
            flag = 0;
            break;
        }
    }

    if (flag == 1) //安全状态
    {
        printf("找到安全序列，且安全序列为: ");
        for (int k = 0; k < len; k++)
        {
            safe[length++] = safeList[k];
            if (k != len - 1)   printf("P%d->", safeList[k]);
            else printf("P%d \n", safeList[k]);
        }
        displaySafe();
    }
    else //不安全状态
    {
        return 0;
    }
    return 1;
}

int init() { //初始化，输入银行家算法起始各项数据
    printf("请输入系统进程的个数:");
    scanf("%d", &process);
    printf("请输入系统资源的种数:");
    scanf("%d", &resource);
    for (int i = 0; i < process; i++)
    {
        printf("------------------P%d----------------------\n", i);
        printf("              Max: ");
        for (int j = 0; j < resource; j++)
        {
            scanf("%d", &max[i][j]);  //输入最大需求
        }

        printf("              Allocation: ");
        for (int j = 0; j < resource; j++)
        {
            scanf("%d", &allocation[i][j]); //输入已分配资源
        }

        printf("              need: ");
        for (int j = 0; j < resource; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
        printf("------------------------------------------\n");
    }

    printf("整个系统可利用资源向量Available: "); //输入可利用资源向量
    for (int j = 0; j < resource; j++)
        scanf("%d", &available[j]);
    printf("\n----------------------------------当前资源分配情况----------------------------------\n");
    display();
    int isSafe = safeCheck(); //对此时刻状态进行安全性检查
    if (isSafe == 1)
        return 1;
    else
        return 0; //失败重新初始化
}

void req() { //申请资源
    int n; //请求资源的进程号
    printf("请输入请求的进程号: ");
    scanf("%d", &n);

    while (n >= process)
    {
        printf("没有该进程，请重新输入: ");
        scanf("%d", &n);
    }

    printf("请输入进程P%d的请求向量: ", n);
    for (int i = 0; i < resource; i++)
    {
        scanf("%d", &request[n][i]);
    }
    //开始判断
    for (int i = 0; i < resource; i++)
    {
        if (need[n][i] < request[n][i])
        {
            printf("\n----------------------------------当前资源分配情况----------------------------------\n");
            display();
            printf("请求的资源数已超过所宣布的最大值!\n");
            return;
        }
    }

    for (int i = 0; i < resource; i++)
    {
        if (available[i] < request[n][i])
        {
            printf("\n----------------------------------当前资源分配情况----------------------------------\n");
            display();
            printf("当前尚无足够资源,请等待其它进程完成释放资源后执行\n");
            return;
        }
    }

    //试分配资源给请求进程，并做安全性检查
    for (int i = 0; i < resource; i++)
    {
        available[i] -= request[n][i];
        allocation[n][i] += request[n][i];
        need[n][i] -= request[n][i];
    }
    printf("\n----------------------------------预分配后的资源情况----------------------------------\n");
    display();
    int isSafe = safeCheck();

    if (isSafe == 1)
    {
        printf("若分配资源,系统仍将处于安全状态！故分配资源！\n");
        printf("\n----------------------------------正式完成分配后的资源情况----------------------------------\n");
        display();
    }
    else
    {
        printf("找不到安全序列,若分配资源,系统将处于不安全状态！故不分配资源！恢复至原来状态! \n");
        //恢复试分配之前的现场
        for (int i = 0; i < resource; i++)
        {
            available[i] += request[n][i];
            allocation[n][i] -= request[n][i];
            need[n][i] += request[n][i];
        }
        printf("\n----------------------------------恢复预分配前的资源情况----------------------------------\n");
        display();
    }

}

int main() {
    int choose;
    while (1)
    {
        int flag = 0;
        menu();
        scanf("%d", &choose);
        switch (choose)
        {
            case 1:
                flag = init();
                if (flag == 1)
                {
                    printf("初始化成功,此时刻存在安全序列,且安全序列为: ");
                    for (int i = 0; i < length; i++)
                    {
                        if (i != length - 1)	printf("P%d->", safe[i]);
                        else printf("P%d ,故系统是安全的\n", safe[i]);
                    }

                }
                else printf("初始化失败,找不到此时刻的安全序列,故系统不安全\n");
                getchar();
                break;
            case 2:
                req();
                getchar();
                break;
            case 3:
                printf("\n----------------------------------当前资源分配情况----------------------------------\n");
                display();
                getchar();
                break;
            case 4:
                printf("程序已退出！\n");
                getchar();
                return 0;
            default:
                printf("不存在此选项,请重新输入！\n");
                getchar();
                break;
        }
    }

    return 0;
}