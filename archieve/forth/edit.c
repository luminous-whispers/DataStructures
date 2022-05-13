/*
第四次作业第四题, 文本编辑模拟
主要考察的是将每步操作存储在栈中, 方便撤回操作
debug了两天, 最后发现是数组开小了哈哈, 裂开
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct OPERATOR{
    int in_op;//当返回的op置0时, 代表此时栈中已经没有操作
    int pos;
    union INFO{
        char * str;
        int n;
    }info;
}opStack[100];
int top=-1;

char str[520];
int sum;//字符数总数

void Undo();
void Delete(int pos, int n);//注意, 撤销删除就是插入, 撤销插入就是删除n=sizeof(str)
void Insert(int pos, char *str);


//操作栈
void Push(struct OPERATOR);//push只接受info.str(不接受info.n)
struct OPERATOR Pop();//并检查-1, 记op=0

int main()
{
    
    int i, j, k;
    struct OPERATOR item;
    char op[100], deleted[100], *p;

    gets(str);
    sum = strlen(str);

    scanf("%d", &j);
    getchar();//!scanf和gets一起用的神坑, scanf不读入\n, 会坑掉后面一个gets
    k = j;
    for (i=0; i<k; i++)
    {
        gets(op);
        p = (char *)malloc(sizeof(char)*100);
        sscanf(op,"%d %d %s", &item.in_op, &item.pos, p);
        item.info.str = p;  
        Push(item);
    }
    gets(op);
    while (gets(op) != NULL)
    {
        sscanf(op, "%d", &item.in_op);
        if (item.in_op == -1)
            break;//结束
        else if (item.in_op == 3)
            Undo();
        else if (item.in_op == 1)
        {
            p = (char *)malloc(sizeof(char)*100);
            sscanf(op,"%d %d %s", &item.in_op, &item.pos, p);
            item.info.str = p;  
            Insert(item.pos, item.info.str);
            Push(item);
        }
        else if (item.in_op == 2)
        {
            p = (char *)malloc(sizeof(char)*100);
            sscanf(op,"%d %d %d", &item.in_op, &item.pos, &item.info.n);
            for (i=0; i<item.info.n; i++)
                deleted[i] = str[item.pos+i];
            deleted[i] = 0;
            Delete(item.pos, item.info.n);
            strcpy(p, deleted);
            item.info.str = p;
            Push(item);
        }
    }
    printf("%s", str);
}

void Undo()
{
    struct OPERATOR unOp;
    int num;
    unOp = Pop();
    if (unOp.in_op == 0)//栈空则操作无效
        return;
    else if (unOp.in_op == 1)
    {
        num = strlen(unOp.info.str);
        Delete(unOp.pos, num);
    }
    else
        Insert(unOp.pos, unOp.info.str);
    free(unOp.info.str);
}

void Delete(int pos, int n)
{
    int i, j;
    i = pos;
    j = pos + n;
    if (j >= sum)
    {
        str[i] = 0;
        return ;
    }
    while (j != sum)
    {
        str[i++] = str[j++];
    }
    str[i] = 0;
    sum = strlen(str);
}

void Insert(int pos, char *in)
{
    int i, len, j;
    char tmp;
    if (sum == pos)
    {
        strcpy(&str[pos], in);
    }
    else
    {
        len = strlen(in);
        for (i=sum-1, j=sum+len-1; i!=pos-1; i--, j--)
            str[j] = str[i];
        str[sum+len] = 0;
        tmp = str[i+1];
        strcpy(&str[pos], in);
        str[i+1+len] = tmp;//防止strcpy自动补零导致错误
    }
    sum = strlen(str);
}  

void Push(struct OPERATOR element)
{
    top++;
    opStack[top].in_op = element.in_op;
    opStack[top].pos = element.pos;
    opStack[top].info.str = element.info.str;
    return;
}

struct OPERATOR Pop()
{
    struct OPERATOR tmp;
    if (top == -1)
    {
        tmp.in_op = 0;
        return tmp;
    }
    return opStack[top--];
}