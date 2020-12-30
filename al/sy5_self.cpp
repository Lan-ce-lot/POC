#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctime>


#define INVALID -1
#define total_instruction 320
#define total_vp 32 //最大页数
int a[total_instruction];//指令序号数组

void createRandom() {
    srand(10 *getpid()); //每次运行时进程号不同，用来作为初始化随机数队列的"种子
    int s = (int)((float)(total_instruction - 1) * (rand() / (RAND_MAX + 1.0)));
    for (int i = 0; i < total_instruction; i += 4) //产生指令队列
    {
        a[i] = s;            //任选一指令访问点m
        a[i + 1] = a[i] + 1; //顺序执行一条指令

        a[i + 2] =(int)((float)a[i] * (rand() / (RAND_MAX + 1.0))); //执行前地址指令m'
        a[i + 3] = a[i + 2] + 1; //顺序执行一条指令
        if ((i) % 8 == 0) {
            printf("\n");
        }
        printf("%5d%5d%5d%5d", a[i], a[i + 1], a[i + 2], a[i + 3]);
        s = (int)((float)((total_instruction - 1) - a[i + 2]) *(rand() / (RAND_MAX + 1.0))) + a[i + 2];
    }
}
typedef struct
{
    int pn,  //页面序号
    pfn, //页面所在内存区的页框号
    counter, time;
} pl_type;

pl_type pl[total_vp]; //页面结构数组

struct pfc_struct { //页面控制结构
    int pn,           //页面号
    pfn;          //内存区页面的帧号
    struct pfc_struct *next;
};

typedef struct pfc_struct pfc_type;
pfc_type pfc[total_vp], *freepf_head, *busypf_head, *busypf_tail;
int diseffect;

int page[total_instruction];
int offset[total_instruction];


// FIFO     LRU    OPT    CLOCK
float FIFO_sum = 0, LRU_sum = 0, OPT_sum = 0, CLOCK_sum = 0;
float FIFO_average = 0, LRU_average = 0, OPT_average = 0, CLOCK_average = 0;


//初始化页面结构数组和页面控制结构数组
// total_pf;  用户进程的内存页面数
int initialize(int total_pf) {
    int i;
    diseffect = 0;
    for (i = 0; i < total_vp; i++) {//对所有的页
        pl[i].pn = i;
        pl[i].pfn = INVALID;
        pl[i].counter = 0;//访问次数置0
        pl[i].time = -1;//存在时间设为-1
    }

    for (i = 0; i < total_pf - 1; i++) {//所有的页块进行链式链接
        pfc[i].next = &pfc[i + 1];
        pfc[i].pfn = i;
    }//默认选择的是前i个页面共存于内存中

    pfc[total_pf - 1].next = NULL;//最后一页不链接其他页框
    pfc[total_pf - 1].pfn = total_pf - 1;//最后一个页框，pfn设为编号值，VALID化
    freepf_head = &pfc[0];//指向第一个页框的指针
    return 0;
}

int LRU(int total_pf) {
    int MinT;
    int MinPn; //最小访问时间对应的叶号
    int i, j;
    int CurrentTime;
    initialize(total_pf);//初始化
    CurrentTime = 0;
    diseffect = 0;

    for (i = 0; i < total_instruction; i++) {
        if (pl[page[i]].pfn == INVALID) {
            diseffect++;//产生一次缺页
            if (freepf_head == NULL) {//说明内存中一页都没有空闲
                MinT = 100000;//保证这一次读取到的页能够进入内存

                for (j = 0; j < total_vp; j++) {
                    if (MinT > pl[j].time && pl[j].pfn != INVALID) {
                        MinT = pl[j].time;//最小访问时间
                        MinPn = j;
                    }//通过便利，找出最小访问时间的夜
                }

                freepf_head = &pfc[pl[MinPn].pfn];
                pl[MinPn].pfn = INVALID;//内存中无该页面，换出l
                pl[MinPn].time = -1;
                freepf_head->next = NULL;
            }

            pl[page[i]].pfn = freepf_head->pfn;//换入，同时修改信息
            pl[page[i]].time = CurrentTime;
            freepf_head = freepf_head->next;
        } else
            pl[page[i]].time = CurrentTime;
        CurrentTime++;
    }
    LRU_sum += (320 - diseffect);
    printf("%7.3f%\t", (1 - (float) diseffect / 320) * 100);//用1减去缺页率；
    return 0;
}

int OPT(int total_pf) {//最理想的结果
    int i, j;
    int MaxD;
    int MaxPn;
    int dis;
    int dist[total_vp];
    initialize(total_pf);
    diseffect = 0;
    for (i = 0; i < total_instruction; i++) {
        if (pl[page[i]].pfn == INVALID) //页面失效
        {
            diseffect++;
            if (freepf_head == NULL) {
                for (j = 0; j < total_vp; j++) {
                    if (pl[j].pfn != INVALID)
                        dist[j] = 100000;
                    else
                        dist[j] = 0;
                }
                dis = 1;
                for (j = i + 1; j < total_instruction; j++) {
                    if (pl[page[j]].pfn != INVALID && pl[page[j]].counter == 0) {
                        dist[page[j]] = dis;
                        pl[page[j]].counter = 1;
                    }
                    dis++;
                }
                MaxD = -1;
                for (j = 0; j < total_vp; j++) {
                    pl[j].counter = 0;
                    if (MaxD < dist[j]) {
                        MaxD = dist[j];
                        MaxPn = j;
                    }
                }
                freepf_head = &pfc[pl[MaxPn].pfn];
                freepf_head->next = NULL;
                pl[MaxPn].pfn = INVALID;
            }
            pl[page[i]].pfn = freepf_head->pfn;
            freepf_head = freepf_head->next;
        } // if
    }   // for
    OPT_sum += (320 - diseffect);
    printf("%7.3f%\t", (1 - (float) diseffect / 320) * 100);
    return 0;
}

int CLOCK(int total_pf) {
    int i;
    int use[total_vp];
    int swap;
    swap = 0;
    initialize(total_pf);
    pfc_type *pnext;
    pfc_type *head;
    pnext = freepf_head;
    head = freepf_head;
    for (i = 0; i < total_vp; i++) {
        use[i] = 0;
    }//都没有使用过
    diseffect = 0;
    for (i = 0; i < total_instruction; i++) {
        if (pl[page[i]].pfn == INVALID) {
            diseffect++;//缺页
            if (freepf_head == NULL) {
                while (use[pnext->pfn] == 1) {//访问过，就改为0
                    use[pnext->pfn] = 0;
                    pnext = pnext->next;//下一页
                    if (pnext == NULL)
                        pnext = head;
                }
                pl[pnext->pn].pfn = INVALID;
                swap = 1;
            }
            if (use[pnext->pfn] == 0) {
                pl[page[i]].pfn = pnext->pfn;
                pnext->pn = page[i];
                use[pnext->pfn] = 1; //重置使用位为
                pnext = pnext->next;
                if (pnext == NULL)
                    pnext = head;
                if (swap == 0) {
                    freepf_head = freepf_head->next;
                }
            }

        } else { //页面在主存中
            use[pl[page[i]].pfn] = 1;
        }
    }
    CLOCK_sum += (320 - diseffect);;
    printf("%7.3f%\t", (1 - (float) diseffect / 320) * 100);
    return 0;
}

int FIFO(int total_pf) {
    int i;
    int use[total_vp];
    int swap = 0;
    initialize(total_pf);

    pfc_type *pnext, *head;
    pnext = freepf_head;
    head = freepf_head;
    for (i = 0; i < total_vp; i++) {
        use[i] = 0;
    }
    diseffect = 0;

    for (i = 0; i < total_instruction; i++) {//开始对每一条指令进行操作
        if (pl[page[i]].pfn == INVALID) {
            diseffect++;//缺页
            if (freepf_head == NULL) {
                while (use[pnext->pfn] == 1) {
                    use[pnext->pfn] = 0;
                    pnext = pnext->next;
                    if (pnext == NULL)
                        pnext = head;
                }

                pl[pnext->pn].pfn = INVALID;
                swap = 1;//标记一下，要被换出了
            }
            if (use[pnext->pfn] == 0) {
                pl[page[i]].pfn = pnext->pfn;
                pnext->pn = page[i];
                use[pnext->pfn] = 1;

                pnext = pnext->next;
                if (pnext == NULL)
                    pnext = head;
                if (swap == 0) {
                    freepf_head = freepf_head->next;
                }
            }
        }
        //访问成功，不进行任何操作
    }
    FIFO_sum += (320 - diseffect);;
    printf("%7.3f%\t", (1 - (float) diseffect / 320) * 100);
    return 0;
}



int main() {
    printf("\n########320条随机指令序列############\n");
    createRandom();

    printf("\n#####################################\n");
    for (int i = 0; i < total_instruction; i++) {
        page[i] = a[i] / 10; //第几页
        offset[i] = a[i] % 10;
    }

    printf("\n##不同页面工作区各种替换策略的命中率表##\n");
    printf("Page\t\tOPT \t\tFIFO\t\tLRU\t\t CLOCK\n");
    for (int i = 4; i <= 32; i++) {
        printf(" %2d \t", i);
        OPT(i);
        FIFO(i);
        LRU(i);
        CLOCK(i);
        printf("\n");
    }
    printf("\n#############31次测试的平率命中率#############\n");
    printf("OP平均均命中率为  %.3f%\n", OPT_sum / 320.0 / (32 - 1) * 100);
    printf("FIFO平均命中率为  %.3f%\n", FIFO_sum / 320.0 / (32 - 1) * 100);
    printf("LRU平均命中率为   %.3f%\n", LRU_sum / 320.0 / (32 - 1) * 100);
    printf("CLOCK平均命中率为 %.3f%\n", CLOCK_sum / 320.0 / (32 - 1) * 100);
    printf("############################################\n");
    return 0;
}