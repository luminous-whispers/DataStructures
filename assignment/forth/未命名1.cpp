/*
第四次作业第四题, 文本编辑模拟
主要考察的是将每步操作存储在栈中, 方便撤回操作
*/
#include<stdio.h>
#include<string.h>

struct OPERATOR{
    int op;//当返回的op置0时, 代表此时栈中已经没有操作
    int pos;
    union INFO{
        char * str;
        int n;
    }info;
}opStack[50];
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
    
    int i, n;
    struct OPERATOR item;
    char op[50], deleted[50];
    freopen("in.txt", "r", stdin);

    gets(str);
    sum = strlen(str);

    scanf("%d", &n);
    while (n--)
    {
        gets(op);
        sscanf(op,"%d %d %s", &item.op, &item.pos, &item.info.str);
        Push(item);
    }
    getchar();//吃掉空行
    while (gets(op) != NULL)
    {
        sscanf(op, "%d", item.op);
        if (item.op == -1)
            break;//结束
        else if (item.op == 3)
            Undo();
        else if (item.op == 1)
        {
            sscanf(op,"%d %d %s", &item.op, &item.pos, &item.info.str);   
            Insert(item.pos, item.info.str);
            Push(item);
        }
        else if (item.op == 2)
        {
            sscanf(str,"%d %d %s", &item.op, &item.pos, &item.info.n);
            for (i=0; i<n; i++)
                deleted[i] = str[item.pos+i];
            deleted[i] = 0;
            Delete(item.pos, item.info.n);
            strcpy(item.info.str, deleted);
            Push(item);
        }
    }
    printf("%s", str);
}

void Undo()
{
    struct OPERATOR unOp;
    unOp = Pop();
    if (unOp.op == 0)//栈空则操作无效
        return;
    else if (unOp.op == 1)
        Delete(unOp.pos, sizeof(unOp.info.str));
    else
        Insert(unOp.pos, unOp.info.str);
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
}

void Insert(int pos, char *str)
{
    int i, len, j;
    char tmp;
    if (sum == pos)
    {
        strcpy(&str[pos], str);
    }
    else
    {
        len = strlen(str);
        for (i=sum-1, j=sum+len-1; i!=pos-1; i--, j--)
            str[j] = str[i];
        str[sum+len] = 0;
        tmp = str[i+1];
        strcpy(&str[pos], str);
        str[i+1] = tmp;//防止strcpy自动补零导致错误
    }
}  

void Push(struct OPERATOR element)
{
    top++;
    opStack[top].op = element.op;
    opStack[top].pos = element.pos;
    opStack[top].info.str = element.info.str;
    return;
}

struct OPERATOR Pop()
{
    struct OPERATOR tmp;
    if (top == -1)
    {
        tmp.op = 0;
        return tmp;
    }
    return opStack[top--];
}
