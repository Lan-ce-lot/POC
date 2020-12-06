#include<stdio.h>
#include<stdlib.h>
//Unix,Linux related System call functions
#include<unistd.h>
#include<time.h>
//header files of basic system data types for Unix and Linux systems
#include<sys/types.h>
//Unix, Linux system wait function
#include<sys/wait.h>
//Correlation function of semaphor e operation
#include<linux/sem.h>
//Number of subprocesses
#define NUM_PROCS 5
//Semaphore ID
#define SEM_ID 250
#define FILE_NAME "/tmp/sem_aaa"
#define DELAY 4000000
void update_file(int sem_set_id, char *file_path, int number)
{
    struct sembuf sem_op;
    FILE *file;
    sem_op.sem_num = 0;//标识信号量集中的第几个信号量
    sem_op.sem_op = -1;//P操作
    sem_op.sem_flg = 0;//为0表示正常操作
    semop(sem_set_id, &sem_op, 1);
    file = fopen(file_path, "w");
    if(file)
    {
        fprintf(file, "%d\n", number);//传进来的进程号
        printf("%d\n",number);
        fclose(file);
    }
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;//V操作
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}
//SUbprocesses write files
void do_child_loop(int sem_set_id, char *file_name)
{
    //进程标识符 sem_set_id
    pid_t pid = getpid();//get current processs's id
    int i, j;
    for(i = 0; i < 3; i++)//0, 1, 2
    {
        update_file(sem_set_id, file_name, pid);
        for(j = 0; j < 4000000; j++);
    }
}
int main(int argc, char **argv)
{
    int sem_set_id;//进程标识符
    union senum sem_val;//Semaphore value, for semctl()信号量数值
    int child_pid;
    int i, rc;
    //建立信号量集
    sem_set_id = semget(SEM_ID, 1, IPC_CREAT|0600);
    //调用失败
    if(sem_set_id == -1)
    {
        perror("main: semget");
        exit(1);
    }
    //把第一个信号量的数值设为1
    sem_val.val = 1;
    rc = semctl(sem_set_id, 0, SETVAL, sem_val);
    if(rc == -1)
    {
        perror("main:semctl");
        exit(1);
    }
    //建立子进程，竞争的方式访问信号量

    for(i = 0; i < NUM_PROCS; i++)//0，1，2，3，4
    {
        child_pid = fork();//成功返回0，否则返回-1
        switch(child_pid)
        {
            case -1:
                perror("fork");
            case 0://子进程写文件
                do_child_loop(sem_set_id, FILE_NAME);
                exit(0);
            default:
                break;
        }
    }
    //等待子进程结束
    for(i = 0; i < NUM_PROCS; i++)
    {
        int child_status;
        wait(&child_status);
    }
    printf("main:we're done!\n");
    fflush(stdout);
    return 0;
}