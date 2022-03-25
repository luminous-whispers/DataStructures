/*第三次作业第一道题
本节课已经学到链表,本道题没有利用链表,考察的是结构体.
简单的匹配和排序, 比较值得一想的是存入数据后先排一下序,就可以有效提升运行效率
    这是因为这道题规定了起点的横坐标一定比终点提前,并且连续线段的横坐标都是递增的,这避免了一些迂回情况*/
#include<stdio.h>
#include<stdlib.h>
struct NODE{
    int x1;
    int y1;
    int x2;
    int y2;
    int mode;//0代表未筛查, 1代表已经在某个线段中不必再次检查
} Line[120];

int cmp(const void *str1, const void *str2);

int main()
{
    int n, i, j;
    int MaxNum = 0, MaxBegin = 0, TmpNum, TmpBegin, TmpLast;//TmpNum存储的是当前的线段数
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d%d%d%d", &Line[i].x1, &Line[i].y1, &Line[i].x2, &Line[i].y2);
    }
    qsort(Line, n, sizeof(struct NODE), cmp);

    for (i = 0; i < n && Line[i].mode == 0; i++)
    {
        //Max = 0, Begin = i;
        TmpNum = 1;
        TmpBegin = i;
        TmpLast = i;
        Line[i].mode = 1;
        for (j = i+1; j < n; j++)
        {
            if (Line[TmpLast].x2 == Line[j].x1 && Line[TmpLast].y2 == Line[j].y1 && Line[j].mode != 1)
            {
                TmpLast = j;
                TmpNum++;
                Line[j].mode = 1;
            }
        }
        if (TmpNum > MaxNum)
        {
            MaxNum = TmpNum;
            MaxBegin = TmpBegin; 
        }
    }
    printf("%d %d %d", MaxNum, Line[MaxBegin].x1, Line[MaxBegin].y1);
    return 0;
}

int cmp(const void *str1, const void *str2){
    struct NODE A = *(struct NODE *)str1, B = *(struct NODE *)str2;
    return A.x1 - B.x1;
}