/*数据结构第三次作业第二题, 猴子淘汰赛
n只猴子, 从q开始依次报数m次, 报m的退出,直至最后胜出
考察链表, 很简单*/
#include<stdio.h>
#include<stdlib.h>

struct MONKEY{
    int rank;
    struct MONKEY *next;
};

int main()
{
    int n, m, q, i;
    struct MONKEY *FakeHead, *Tmp, *Last, *Start;
    scanf("%d%d%d", &n, &m, &q);

    //构造环表
    FakeHead = (struct MONKEY *)malloc(sizeof(struct MONKEY));
    FakeHead->next = NULL;
    Last = FakeHead;
    FakeHead->rank = 1;
    if (q == 1)
        Start = FakeHead;
    for (i = 2; i <= n; i++)
    {
        Tmp = (struct MONKEY *)malloc(sizeof(struct MONKEY));
        Tmp->rank = i;
        Last->next = Tmp;
        Last = Tmp; 
        if (i == q)
            Start = Tmp;
    }
    Tmp->next = FakeHead;

    //开始报数
    for (i = 1; i < n; i++)
    {
        for (q = 1; q < m; q++)//多循环了一次, 7被拿走了
        {
            Last = Start;
            Start = Last->next;
        }
        Last->next = Start->next;
        free(Start);
        Start = Last->next;
    }
    printf("%d", Last->rank);
    return 0;
}