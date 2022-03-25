/* 第二次作业第四题 电话簿储存与排序 
核心是 单词字典序排序的比较函数编写 与 快排函数应用
构造储存信息结构体 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*例程*/
struct PERSON{
    char Name[30];
    char Num[10][15];
    int height;//存储已经有几个电话了
}people[100];
int NumberOfPeople = 0;//用于实时记录数组中有效的人数, 是实际人数减一

int cmp(const void *str1, const void *str2);
int check(struct PERSON *);//查找人名, 返回位于数组中的位置.如果没有则返回-1, -2代表重复, -3代表第一个

int main()
{
    int k, i = 0, flag = 0, n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s%s", people[NumberOfPeople].Name
            , people[NumberOfPeople].Num[0]);//people[NumberOfPeople].Num[ people[NumberOfPeople].height ]);
        k = check(&people[NumberOfPeople]);
        if (k == -1 || k == -3)
        {
            people[NumberOfPeople].height++;
            NumberOfPeople++;
        }
        else if (k == -2)
            continue;
        else
        {
            strcpy(people[k].Num[ people[k].height ], 
                people[NumberOfPeople].Num[ people[NumberOfPeople].height ]);
            people[k].height++;
        }
    }
    qsort(people, NumberOfPeople, sizeof(struct PERSON), cmp); //结束后,numberofpeople会变成真实人数
    
    while (i < NumberOfPeople)
    {
        for (k = 0; k < people[i].height; k++)
        {
            if (k == 0)
                printf("%s %s\n", people[i].Name, people[i].Num[flag++]);
            else
                printf("%s_%d %s\n", people[i].Name, k, people[i].Num[flag++]);
        }
        flag = 0;
        i++;
    }
    
    return 0;
}

int cmp(const void *str1, const void *str2)
{
    struct PERSON A = *(struct PERSON *)str1, B = *(struct PERSON *)str2;
    int i, len = (strlen(A.Name)<strlen(B.Name)?strlen(A.Name):strlen(B.Name));

    for (i = 0; i < len; i++)
    {
        if (A.Name[i] > B.Name[i])
            return 1;
        else if (A.Name[i] < B.Name[i])
            return -1;
    }
    return 0;//完全相同, 或者还有只有前一段相同??
}

int check(struct PERSON *P)
{
    int i, j, k, len = 11, flag;
    for (i = 0; i < NumberOfPeople; i++)
    {
        j = cmp(P->Name, people[i].Name);
        if (j == 0)
        {
            for (k = 0; k < people[i].height; k++)
            {
                for (flag = 0; flag < len; flag++)
                {
                    if (people[i].Num[k][flag] != P->Num[0][flag])
                        return i;
                }
            }
            return -2;//指全部重复
        }
        else
            continue;
    }
    if (i == 0)
        return -3;
    else
        return -1;
}