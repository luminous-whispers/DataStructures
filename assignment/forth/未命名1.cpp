/*
���Ĵ���ҵ������, �ı��༭ģ��
��Ҫ������ǽ�ÿ�������洢��ջ��, ���㳷�ز���
*/
#include<stdio.h>
#include<string.h>

struct OPERATOR{
    int op;//�����ص�op��0ʱ, �����ʱջ���Ѿ�û�в���
    int pos;
    union INFO{
        char * str;
        int n;
    }info;
}opStack[50];
int top=-1;

char str[520];
int sum;//�ַ�������

void Undo();
void Delete(int pos, int n);//ע��, ����ɾ�����ǲ���, �����������ɾ��n=sizeof(str)
void Insert(int pos, char *str);


//����ջ
void Push(struct OPERATOR);//pushֻ����info.str(������info.n)
struct OPERATOR Pop();//�����-1, ��op=0

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
    getchar();//�Ե�����
    while (gets(op) != NULL)
    {
        sscanf(op, "%d", item.op);
        if (item.op == -1)
            break;//����
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
    if (unOp.op == 0)//ջ���������Ч
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
        str[i+1] = tmp;//��ֹstrcpy�Զ����㵼�´���
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
