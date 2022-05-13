//the forth assign's bonus, simulate the real func stack in program
//simple, but data structure is interesting
//require stack and list
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//*线性表, 用以体现出现顺序
struct L_NODE;
typedef struct L_NODE *FUN_;
struct L_NODE{
    char * name;//函数名
    int n;//子函数个数
    char * f[15];
}list[120];
int rear = -1;//表尾
int Find(char *index);//没有则返回-1
int FindChild(char *index, FUN_ parent);
void InsertEnd(char *);
void DeleteList();
int Cmp(char *str1, char *str2);//-1代表相等

//*栈
char * stack[120];
int top = -1;
char * Pop();
void Push(char *);

int main()
{
    char str[25], *f;
    int flag, len, i;
    int pos;
    while (scanf("%d", &flag)!=EOF)
    {
        if (flag == 8)
        {
            scanf("%s", str);
            len = strlen(str);
            f = (char *)malloc(sizeof(char)*len);
            strcpy(f, str);

            if (top != -1)
            {
                pos = Find(stack[top]);
                if (pos == -1)
                    printf("error, fun not existed");
                //防重
                if (FindChild(f, &list[pos]) == -1)
                {
                    list[pos].f[list[pos].n] = f;
                    list[pos].n++;
                }
            }
            Push(f);
            if ((pos= Find(f)) == -1)
                InsertEnd(f);
        }
        else if (flag == 0)
            Pop();
    }
    for (flag = 0; flag <= rear; flag++)
    {
        if (list[flag].n == 0)
            continue;
        else 
        {
            printf("%s:", list[flag].name);
            for (i = 0; i < list[flag].n-1; i++)
            {
                printf("%s,", list[flag].f[i]);
            }
            printf("%s\n", list[flag].f[i]);
        }
    }
    DeleteList();
    return 0;
}

int Find(char *index)
{
    int pos;
    if (rear == -1)
        return -1;
    for (pos = 0; pos <= rear; pos++)
    {
        if (Cmp(index, list[pos].name) == -1)
            return pos;
    }
    return -1;
}

int FindChild(char *index, FUN_ parent)
{
    int i;
    if (parent->n == 0)
        return -1;
    for (i=0; i<parent->n; i++)
    {
        if (Cmp(index, parent->f[i]) == -1)
            return i;
    }
    return -1;
}

void InsertEnd(char * str)
{
    rear++;
    list[rear].name = str;//千万不能用strcpy, 还没开辟空间呢
    list[rear].n = 0;
    return;
}

void DeleteList()
{
    /*这个函数能实现的原因是所有函数都在表里, 否则会指针交叉引用*/
    int i;
    for (i=0; i<=rear; i++)
    {
        free(list[i].name);
    }
    return;
}

char *Pop()
{
    if (top == -1)
        printf("error, array overflow with -1");
    return stack[top--];
}

void Push(char * str)
{
    stack[++top] = str;
    return;
}

int Cmp(char *str1, char *str2)
{
    int i;
    for (i=0; *(str1+i)!=0 && *(str2+i)!=0; i++)
        if (*(str1+i)!=*(str2+i))
            return i;
    if (*(str1+i) == *(str2+i))
        return -1;
    else 
        return 1;//随便什么吧, 代表前几个字符相同, 但是有一个比另一个长的情况. 比如calc 和 calculation
}
