/*第四次作业第五题 银行排队模拟
这个题重要的是读题, 让模拟程序尽可能贴合题干!
其次就是简单的队列操作*/
#include<stdio.h>
#include<stdlib.h>
#define MAX 5
#define MIN 3 //最大和最小窗口数

struct CUS
{
    int no;
    int in_time;//入队时间
}customer[100];
int front = 100;//方便构造循环队列, 同时处理开始和循环
int rear = 100;
void Push(struct CUS);
struct CUS Pop();

int cus_num = 0, id = 0;//顾客总数, 注意此变量不归队列函数处理
int now_time, total_time;
int win_num = MIN;//窗口数
void WinAdd();
void WinSub();
void Service();
void CusIn(int new);

int main()
{
    int new_cus;
    scanf("%d", &total_time);
    for (now_time=1; now_time<=total_time || cus_num != 0; now_time++)
    {
        if (now_time <= total_time)
            scanf("%d", &new_cus);
        else
            new_cus = 0;
        CusIn(new_cus);//in queue
        if (new_cus > 0)
            WinAdd();
        Service();
        WinSub();
    }
    return 0;
}

void WinAdd()
{
    int ave;
    ave = cus_num/win_num;
    while (ave >= 7)
    {
        if (win_num == MAX)
            break;
        win_num++;
        ave = cus_num/win_num;
    }
}

void CusIn(int new)
{
    struct CUS person;
    cus_num += new;
    while (new--)
    {
        id++;
        person.in_time = now_time;
        person.no = id;
        Push(person);
    }
}

void WinSub()
{
    int ave;
    ave = cus_num/win_num;
    while (ave < 7)
    {
        if (win_num == MIN)
            break;
        win_num--;
        ave = cus_num/win_num;
    }
}

void Service()
{
    int i;
    struct CUS person;
    for (i=0; i<win_num; i++)
    {
        if (cus_num == 0)
            break;
        cus_num--;
        person = Pop();
        printf("%d : %d\n", person.no, now_time-person.in_time);
    }
}

void Push(struct CUS person)
{
    if (cus_num > 100)
        exit(1);//检测溢出
    if (rear == 100)
    {
        rear = 0;//回到开头
        //注意同时处理了起始的情况
    }
    else
        rear++;
    customer[rear].in_time = person.in_time;
    customer[rear].no = person.no;
}

struct CUS Pop()
{
    if (front == 100)
        front  = 0;//这是处理上次的旧账,这次就应该在0
    return customer[front++];
}