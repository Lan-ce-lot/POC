#include<stdio.h>
#include <stdlib.h>

#define MAX 10//最大进程数目
#define MIN 65535//判断到达时间最小值
struct task_struct //进程
{
    int number;//进程编号
    int come_time;//到达时间
    int run_begin_time;//开始运行时间
    int run_time;//运行时间
    int run_end_time;//运行结束时间
    int priority;//优先级
    int run_flag;//调度标志
    int fin_flag;//结束标志
} tasks[MAX], task_temp[MAX], t;
int counter;//进程个数

int fcfs()//先来先服务算法
{
    float time_temp = 0;
    int i, j, k;
    int number_schedul;
    for (i = 0; i < counter; i++) {
        int min = MIN;
        for (j = 0; j < counter; j++) {
            if (tasks[j].come_time < min && tasks[j].run_flag == 0) {
                min = tasks[j].come_time;
                k = j;
            }
        }
        if (i == 0) {
            time_temp = tasks[k].come_time;
        }
        tasks[k].run_begin_time = time_temp;
        tasks[k].run_end_time = tasks[k].run_begin_time + tasks[k].run_time;
        tasks[k].run_flag = 1;
        time_temp = tasks[k].run_end_time;
    }
    return 0;
}

int ps()//优先级调度算法
{
    float temp_time = 0;
    int i = 0, j;
    int number_schedul, temp_counter;
    int max_priority;
    int min = MIN;
    for (j = 0; j < counter; j++) {
        if (tasks[j].come_time < min && tasks[j].run_flag == 0) {
            min = tasks[j].come_time;
            i = j;
        }
    }
    max_priority = tasks[i].priority;
    j = 0;
    while ((j < counter) && (tasks[i].come_time == tasks[j].come_time)) {
        if (tasks[j].priority > tasks[i].priority) {
            max_priority = tasks[j].priority;
            i = j;
        }
        j++;
    }
//对第一个被调度的进程求相应的参数
    number_schedul = i;
    tasks[number_schedul].run_begin_time = tasks[number_schedul].come_time;
    tasks[number_schedul].run_end_time = tasks[number_schedul].run_begin_time + tasks[number_schedul].run_time;
    tasks[number_schedul].run_flag = 1;
    temp_time = tasks[number_schedul].run_end_time;
    temp_counter = 1;
    while (temp_counter < counter) {
        max_priority = 0;
        for (j = 0; j < counter; j++) {
            if ((tasks[j].come_time <= temp_time) && (!tasks[j].run_flag))
                if (tasks[j].priority > max_priority) {
                    max_priority = tasks[j].priority;
                    number_schedul = j;
                }

        }
        //查找下一个被调度的进程
        //对找到的下一个被调度的进程求相应的参数
        tasks[number_schedul].run_begin_time = temp_time;
        tasks[number_schedul].run_end_time = tasks[number_schedul].run_begin_time + tasks[number_schedul].run_time;
        tasks[number_schedul].run_flag = 1;
        temp_time = tasks[number_schedul].run_end_time;
        temp_counter++;
    }
    return 0;
}

void sortTasks()//临时对进程的进入时间排序
{
    int i, j;
    for (i = 0; i < counter; i++) {
        for (j = i + 1; j < counter; j++) {
            if (tasks[j].come_time < tasks[i].come_time) {
                t = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = t;
            }
        }
    }
}

int psa()//优先级调度（抢占式）
{
    float temp_time = 0;
    int i = 0, j;
    int number_schedul, temp_counter;
    int max_priority;
    sortTasks();
    max_priority = tasks[i].priority;
    j = 1;
    while ((j < counter) && (tasks[i].come_time == tasks[j].come_time)) {
        if (tasks[j].priority > tasks[i].priority) {
            max_priority = tasks[j].priority;
            i = j;
        }
        j++;
    }
    temp_counter = 1;
//对第一个被调度的进程求相应的参数
    number_schedul = i;
    tasks[number_schedul].run_begin_time = tasks[number_schedul].come_time;
    tasks[number_schedul].run_end_time = tasks[number_schedul].run_begin_time + tasks[number_schedul].run_time;
    tasks[number_schedul].run_flag = 1;
    for (i = 0; i < counter; i++) {
        if (tasks[i].come_time < tasks[number_schedul].run_end_time &&
            tasks[i].priority > tasks[number_schedul].priority) {
            tasks[number_schedul].run_end_time += tasks[i].run_time;
            tasks[i].run_begin_time = tasks[i].come_time;
            tasks[i].run_flag = 1;
            tasks[i].run_end_time = tasks[i].run_begin_time + tasks[i].run_time;
            for (j = i; j < counter; j++) {
                if (tasks[j].come_time < tasks[i].run_end_time && tasks[j].priority > tasks[i].priority) {
                    tasks[i].run_end_time += tasks[j].run_time;
                }
            }
            tasks[i].fin_flag = 1;
            temp_counter++;
        }
    }
    tasks[number_schedul].fin_flag = 1;
    temp_time = tasks[number_schedul].run_end_time;

    while (temp_counter < counter) {
        max_priority = 0;
        for (j = 0; j < counter; j++) {
            if ((tasks[j].come_time <= temp_time) && (!tasks[j].fin_flag))
                if (tasks[j].priority > max_priority) {
                    max_priority = tasks[j].priority;
                    number_schedul = j;
                }

        }
        tasks[number_schedul].run_begin_time = temp_time;
        tasks[number_schedul].run_end_time = tasks[number_schedul].run_begin_time + tasks[number_schedul].run_time;
        tasks[number_schedul].run_flag = 1;
        for (i = 0; i < counter; i++) {
            if (tasks[i].come_time < tasks[number_schedul].run_end_time &&
                tasks[i].priority > tasks[number_schedul].priority && tasks[i].fin_flag == 0) {
                tasks[number_schedul].run_end_time += tasks[i].run_time;
                tasks[i].run_begin_time = tasks[i].come_time;
                tasks[i].run_flag = 1;
                tasks[i].run_end_time = tasks[i].run_begin_time + tasks[i].run_time;
                for (j = i; j < counter; j++) {
                    if (tasks[j].come_time < tasks[i].run_end_time && tasks[j].priority > tasks[i].priority) {
                        tasks[i].run_end_time += tasks[j].run_time;
                    }
                }
                tasks[i].fin_flag = 1;
                temp_counter++;
            }
        }
        tasks[number_schedul].fin_flag = 1;
        temp_time = tasks[number_schedul].run_end_time;
        temp_counter++;
    }
    for (i = 0; i < counter; i++)//恢复原来排序
    {
        for (j = i + 1; j < counter; j++) {
            if (tasks[j].number < tasks[i].number) {
                t = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = t;
            }
        }
    }
    return 0;
}

int pinput()//进程参数输入
{
    int i;
    printf("输入进程的个数:\n");
    scanf("%d", &counter);
    for (i = 0; i < counter; i++) {
        printf("-----------------------------------------------\n");
        printf("输入第%d个进程的相关信息 :\n", i + 1);
        printf("进程编号:\n");
        scanf("%d", &tasks[i].number);
        printf("进程的到达时间:");
        scanf("%d", &tasks[i].come_time);
        printf("这个进程运行所需时间:");
        scanf("%d", &tasks[i].run_time);
        printf("进程的优先级别:\n");
        scanf("%d", &tasks[i].priority);
        tasks[i].run_begin_time = 0;
        tasks[i].run_end_time = 0;
        tasks[i].run_flag = 0;
        tasks[i].fin_flag = 0;
    }
    return 0;
}

int poutput()//调度结果输出
{
    int i;
    float turn_round_time = 0, f1, w = 0;
    printf("进程编号\t到达时间\t运行时间\t运行开始时间\t运行结束时间\t优先级\t周转时间\n");
    for (i = 0; i < counter; i++) {
        f1 = tasks[i].run_end_time - tasks[i].come_time;
        turn_round_time += f1;
        w += (f1 / tasks[i].run_time);
        printf("   %d  \t\t%d\t\t%d\t\t%d\t\t %d\t\t%d  \t%5.2f\n", tasks[i].number, tasks[i].come_time,
               tasks[i].run_time, tasks[i].run_begin_time, tasks[i].run_end_time, tasks[i].priority, f1);
    }
    printf("平均周转时间=%5.2f\n", turn_round_time / counter);
    printf("平均带权周转时间=%5.2f\n", w / counter);
    return 0;
}

int main() {
    int choose;
    pinput();
    printf("选择调度算法：1.先来先服务；2.优先级调度;3.优先级调度（抢占式）;0.退出\n");
    scanf("%d", &choose);
    switch (choose) {
        case 0:
            printf("运行结束\n");
            exit(0);
        case 1:
            printf("先来先服务\n");
            fcfs();
            poutput();
            break;
        case 2:
            printf("优先级调度\n");
            ps();
            poutput();
            break;
        case 3:
            printf("优先级调度（抢占式）\n");
            psa();
            poutput();
            break;
    }
}
