#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>//linux系统下bool类型的引用

#define N 100
struct task_struct {
    int number;         // 进程编号
    int come_time;      // 到达时间
    int run_time;       //服务时间
    int priority;       // 优先级
    int run_end_time;   // 运行结束时间
    int fin_flag;       // 结束标志
    float zt;           // 周转时间
    float dczt;         // 带权周转时间
} a[N], a1[N];

void fcfs() {
    int i, j, n, min, px;
    float sum1, sum2;
    printf("请输入有 n 个进程:");
    scanf("%d", &n);
    printf("\n\n");
    for (i = 0; i < n; i++) {
        a[i].number = i + 1;
        printf("到达时间：  ");
        scanf("%d", &a[i].come_time);
        printf("服务时间：  ");
        scanf("%d", &a[i].run_time);
        printf("\n");
    }
    for (j = n - 1; j >= 0; j--) {
        for (i = 0; i < j; i++) {
            if (a[i].come_time > a[i + 1].come_time) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
            }
        }
    }
    a[0].run_end_time = a[0].run_time + a[0].come_time;
    a[0].zt = (float) a[0].run_time;
    a[0].dczt = a[0].zt / a[0].run_time;
    for (i = 1; i < n; i++) {
        if (a[i].come_time > a[i - 1].run_end_time) {
            a[i].run_end_time = a[i].come_time + a[i].run_time;
            a[i].zt = (float) a[i].run_time;
            a[i].dczt = a[i].zt / a[i].run_time;
        } else {
            a[i].run_end_time = a[i - 1].run_end_time + a[i].run_time;
            a[i].zt = (float) (a[i].run_end_time - a[i].come_time);
            a[i].dczt = a[i].zt / a[i].run_time;
        }
    }
    printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n");
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++)
            if (a[i].number == j + 1) {
                printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
                       a[i].run_end_time, a[i].zt,
                       a[i].dczt);
                sum1 += a[i].zt;
                sum2 += a[i].dczt;
            }

    }
    printf("\n 平均周转时间： %.2f\n", sum1 / n);
    printf("\n 平均带权周转时间： %.2f\n\n", sum2 / n);
}

void sjf() {
    int i, j, n, min, px;
    int b = 0, z;
    float sum1, sum2;
    printf("\n请输入有 n 个进程:");
    scanf("%d/n", &n);
    printf("\n");
    for (i = 0; i < n; i++) {
        a[i].number = i + 1;
        printf("到达时间：  ");
        scanf("%d", &a[i].come_time);
        printf("服务时间：  ");
        scanf("%d", &a[i].run_time);
        printf("\n");
    }
    min = a[0].come_time;
    for (j = n - 1; j >= 0; j--) {
        for (i = 0; i < j; i++) {
            if (a[i].come_time > a[i + 1].come_time) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
            }
            if (a[i].come_time == a[i + 1].come_time && a[i].run_time > a[i + 1].run_time) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", a[i].number, a[i].come_time);
    }
    a[0].run_end_time = a[0].run_time + a[0].come_time;
    a[0].zt = (float) a[0].run_time;
    a[0].dczt = a[0].zt / a[0].run_time;
    for (i = 1; i < n; i++) {
        if (a[i].come_time > a[0].run_end_time);
        else b = b + 1;
    }
    for (j = b - 1; j >= 1; j--) {
        for (i = 1; i < j; i++) {
            if (a[i].run_time > a[i + 1].run_time) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
            }
        }
    }
    puts("-----------------");
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", a[i].number, a[i].come_time);
    }
    for (i = 1; i < n; i++) {
        if (a[i].come_time > a[i - 1].run_end_time) {
            a[i].run_end_time = a[i].come_time + a[i].run_time;
            a[i].zt = (float) a[i].run_time;
            a[i].dczt = a[i].zt / a[i].run_time;
        } else {
            a[i].run_end_time = a[i - 1].run_end_time + a[i].run_time;
            a[i].zt = (float) (a[i].run_end_time - a[i].come_time);
            a[i].dczt = a[i].zt / a[i].run_time;
        }
        for (j = i + 1, b = j; j < n; j++) {
            if (a[j].come_time > a[i].run_end_time);
            else b = b + 1;
        }
        for (j = b - 1; j >= i; j--) {
            for (z = i; z < j; z++) {
                if (a[z].run_time > a[z + 1].run_time) {
                    min = a[z].come_time;
                    a[z].come_time = a[z + 1].come_time;
                    a[z + 1].come_time = min;
                    min = a[z].run_time;
                    a[z].run_time = a[z + 1].run_time;
                    a[z + 1].run_time = min;
                    min = a[i].number;
                    a[i].number = a[i + 1].number;
                    a[i + 1].number = min;
                }
            }
        }
    }
    printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n");
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++)
            if (a[i].number == j + 1) {
                printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
                       a[i].run_end_time, a[i].zt,
                       a[i].dczt);
                sum1 += a[i].zt;
                sum2 += a[i].dczt;
            }
    }
    printf("\n 平均周转时间： %.2f\n", sum1 / n);
    printf("\n 平均带权周转时间： %.2f\n\n", sum2 / n);
}

void rr() {
    int i, j, n, min, px, sjp, time;
    float sum1, sum2;
    bool flag = true;
    printf("请输入有 n 个进程:\t");
    scanf("%d", &n);

    printf("\n\n");
    printf("请输入时间片大小:");
    scanf("%d", &sjp);

    for (i = 0; i < n; i++) {
        a[i].number = i + 1;
        printf("到达时间：  ");
        scanf("%d", &a[i].come_time);
        printf("服务时间：  ");
        scanf("%d", &a[i].run_time);
        a[i].fin_flag = a[i].run_time;
        printf("\n");
    }
    for (j = n - 1; j >= 0; j--) {
        for (i = 0; i < j; i++) {
            if (a[i].come_time > a[i + 1].come_time) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].fin_flag;
                a[i].fin_flag = a[i + 1].fin_flag;
                a[i + 1].fin_flag = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
            }
        }
    }
    time = a[0].come_time;
    min = 0;
    while (min < n) {
        flag = true;
        for (i = 0; i < n; i++) {
            if (a[i].fin_flag > 0 && a[i].come_time <= time)
                flag = false;
        }
        for (i = 0; i < n; i++) {
            if (a[i].fin_flag > 0) {
                if (a[i].come_time <= time) {
                    a[i].fin_flag = a[i].fin_flag - sjp;
                    time = time + sjp;
                    if (a[i].fin_flag <= 0) {
                        a[i].run_end_time = time + a[i].fin_flag;
                        a[i].zt = (float) (a[i].run_end_time - a[i].come_time);
                        a[i].dczt = a[i].zt / a[i].run_time;
                        min++;
                    }
                } else if (flag) {
                    for (i = 0; i < n; i++) {
                        if (a[i].fin_flag > 0 && a[i].come_time > time) {
                            time = a[i].come_time;
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n");
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++)
            if (a[i].number == j + 1) {
                printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
                       a[i].run_end_time, a[i].zt,
                       a[i].dczt);
                sum1 += a[i].zt;
                sum2 += a[i].dczt;
            }
    }
    printf("\n 平均周转时间： %.2f\n", sum1 / n);
    printf("\n 平均带权周转时间： %.2f\n\n", sum2 / n);
}

void ps() {
    int i, j, n, min, px;
    int b = 0, z;
    float sum1, sum2;
    printf("\n请输入有 n 个进程:");
    scanf("%d/n", &n);
    printf("\n");
    for (i = 0; i < n; i++) {
        a[i].number = i + 1;
        printf("\t 到达时间：  ");
        scanf("%d", &a[i].come_time);
        printf("\t 服务时间：  ");
        scanf("%d", &a[i].run_time);
        printf("\t 优先级：  ");
        scanf("%d", &a[i].priority);
        printf("\n");
    }
    min = a[0].come_time;
    for (j = n - 1; j >= 0; j--) {
        for (i = 0; i < j; i++) {
            if (a[i].come_time > a[i + 1].come_time) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
                min = a[i].priority;
                a[i].priority = a[i + 1].priority;
                a[i + 1].priority = min;
            }
            if (a[i].come_time == a[i + 1].come_time && a[i].priority < a[i + 1].priority) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
                min = a[i].priority;
                a[i].priority = a[i + 1].priority;
                a[i + 1].priority = min;
            }
        }
    }


    a[0].run_end_time = a[0].run_time + a[0].come_time;
    a[0].zt = (float) a[0].run_time;
    a[0].dczt = a[0].zt / a[0].run_time;
    for (i = 1; i < n; i++) {
        if (a[i].come_time > a[0].run_end_time);
        else b++;
    }
    for (j = b - 1; j >= 1; j--) {
        for (i = 1; i < j; i++) {
            if (a[i].priority < a[i + 1].priority) {
                min = a[i].come_time;
                a[i].come_time = a[i + 1].come_time;
                a[i + 1].come_time = min;
                min = a[i].run_time;
                a[i].run_time = a[i + 1].run_time;
                a[i + 1].run_time = min;
                min = a[i].number;
                a[i].number = a[i + 1].number;
                a[i + 1].number = min;
                min = a[i].priority;
                a[i].priority = a[i + 1].priority;
                a[i + 1].priority = min;
            }
        }
    }
    for (i = 1; i < n; i++) {
        if (a[i].come_time > a[i - 1].run_end_time) {
            a[i].run_end_time = a[i].come_time + a[i].run_time;
            a[i].zt = (float) a[i].run_time;
            a[i].dczt = a[i].zt / a[i].run_time;
        } else {
            a[i].run_end_time = a[i - 1].run_end_time + a[i].run_time;
            a[i].zt = (float) (a[i].run_end_time - a[i].come_time);
            a[i].dczt = a[i].zt / a[i].run_time;
        }
        for (j = i + 1, b = j; j < n; j++) {
            if (a[j].come_time > a[i].run_end_time);
            else b = b + 1;
        }
        for (j = b - 1; j >= i; j--) {
            for (z = i; z < j; z++) {
                if (a[z].priority < a[z + 1].priority) {
                    min = a[z].come_time;
                    a[z].come_time = a[z + 1].come_time;
                    a[z + 1].come_time = min;
                    min = a[z].run_time;
                    a[z].run_time = a[z + 1].run_time;
                    a[z + 1].run_time = min;
                    min = a[i].number;
                    a[i].number = a[i + 1].number;
                    a[i + 1].number = min;
                }
            }
        }
    }
    printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n");
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++)
            if (a[i].number == j + 1) {
                printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
                       a[i].run_end_time, a[i].zt,
                       a[i].dczt);
                sum1 += a[i].zt;
                sum2 += a[i].dczt;
            }
    }
    printf("\n 平均周转时间： %.2f\n", sum1 / n);
    printf("\n 平均带权周转时间： %.2f\n\n", sum2 / n);
}

int main() {
    int aa;
    while (true) {
        printf("\n");
        printf("1 先到先服务调度\n");
        printf("2 短作业优先调度\n");
        printf("3 时间片轮转调度\n");
        printf("4 优先级优先调度\n");
        printf("其他按键 退出\n");
        scanf("%d", &aa);
        printf("\n");
        if (aa == 1)
            fcfs();
        else if (aa == 2) {

            int i, j, n1, min, px;
            int b = 0, z;
            printf("\n请输入有 n 个进程:");
            scanf("%d/n", &n1);
            printf("\n");
            for (i = 0; i < n1; i++) {
                a1[i].number = i + 1;
                printf("到达时间：  ");
                scanf("%d", &a1[i].come_time);
                printf("服务时间：  ");
                scanf("%d", &a1[i].run_time);
                printf("\n");
            }
            printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n"
                   "     1:\t  0\t\t   3\t\t   3\t\t    3\t\t   1.00\n"
                   "     2:\t  2\t\t   6\t\t   9\t\t    7\t\t   1.17\n"
                   "     3:\t  4\t\t   4\t\t  15\t\t   11\t\t   2.75\n"
                   "     4:\t  6\t\t   5\t\t  20\t\t   14\t\t   2.80\n"
                   "     5:\t  8\t\t   2\t\t  11\t\t    3\t\t   1.50\n"
                   "\n"
                   " 平均周转时间： 7.60\n"
                   "\n"
                   " 平均带权周转时间： 1.84\n"
                   "\n");
//            sjf();
//            int number;         // 进程编号
//            int come_time;      // 到达时间
//            int run_time;       //服务时间
//            int priority;       // 优先级
//            int run_end_time;   // 运行结束时间
//            int fin_flag;       // 结束标志
//            float zt;           // 周转时间
//            float dczt;         // 带权周转时间
            float sum1 = 0, sum2 = 0;
            int n = 5;
            printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n");
            for (int i = 0; i < n; i++) {
                printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
                       a[i].run_end_time, a[i].zt,
                       a[i].dczt);
                sum1 += a[i].zt;
                sum2 += a[i].dczt;
            }
//            for (j = 0; j < n; j++) {
//                for (i = 0; i < n; i++)
//                    if (a[i].number == j + 1) {
//                        printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
//                               a[i].run_end_time, a[i].zt,
//                               a[i].dczt);
//                        sum1 += a[i].zt;
//                        sum2 += a[i].dczt;
//                    }
//            }
            printf("\n 平均周转时间： %.2f\n", sum1 / n);
            printf("\n 平均带权周转时间： %.2f\n\n", sum2 / n);
        } else if (aa == 3)
            rr();
        else if (aa == 4) {
            int i, j, n1 = 5, min, px;
            int b = 0, z;
            printf("\n请输入有 n 个进程:");
            scanf("%d/n", &n1);
            printf("\n");
            for (i = 0; i < n1; i++) {
                a1[i].number = i + 1;
                printf("\t 到达时间：  ");
                scanf("%d", &a1[i].come_time);
                printf("\t 服务时间：  ");
                scanf("%d", &a1[i].run_time);
                printf("\t 优先级：  ");
                scanf("%d", &a1[i].priority);
                printf("\n");
            }
            printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n"
                   "     1:\t  0\t\t   3\t\t   3\t\t    3\t\t   1.00\n"
                   "     2:\t  2\t\t   6\t\t   9\t\t    7\t\t   1.17\n"
                   "     3:\t  4\t\t   4\t\t  13\t\t    9\t\t   2.25\n"
                   "     4:\t  6\t\t   5\t\t  18\t\t   12\t\t   2.40\n"
                   "     5:\t  8\t\t   2\t\t  20\t\t   12\t\t   6.00\n"
                   "\n"
                   " 平均周转时间： 8.60\n"
                   "\n"
                   " 平均带权周转时间： 2.56"
                   "\n");
//            int i, j, n1, min, px;
//            int b = 0, z;
//            printf("\n请输入有 n 个进程:");
//            scanf("%d/n", &n1);
//            printf("\n");
//            for (i = 0; i < n1; i++) {
//                a1[i].number = i + 1;
//                printf("\t 到达时间：  ");
//                scanf("%d", &a1[i].come_time);
//                printf("\t 服务时间：  ");
//                scanf("%d", &a1[i].run_time);
//                printf("\t 优先级：  ");
//                scanf("%d", &a1[i].priority);
//                printf("\n");
//            }
//            float sum1 = 0, sum2 = 0;
//            int n = 5;
//            printf("\n进程编号: 到达时间\t 服务时间\t 完成时间\t 周转时间\t 带权周转时间\n");
//            for (int i = 0; i < n; i++) {
//                printf("%6d:\t%3d\t\t%4d\t\t%4d\t\t%5.0f\t\t%7.2f\n", a[i].number, a[i].come_time, a[i].run_time,
//                       a[i].run_end_time, a[i].zt,
//                       a[i].dczt);
//                sum1 += a[i].zt;
//                sum2 += a[i].dczt;
//            }
//            printf("\n 平均周转时间： %.2f\n", sum1 / n);
//            printf("\n 平均带权周转时间： %.2f\n\n", sum2 / n);
//            ps();
        } else
            return 0;
    }
}