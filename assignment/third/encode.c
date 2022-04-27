/* 第三次作业第四题 文件加密(升级版)
考察链表的基本操作, 核心是环形表
有一个有意思的错误是, 优化约瑟夫问题减少循环次数时要注意取余时逻辑的坑
较简单*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 150
#define VISIBLE_BEGIN 32//非可见字符原样输出
#define VISIBLE_END 126

struct Node;
typedef struct Node * POSITION_;
typedef struct Node * L_;//头指针需要储存信息
struct Node{
    int element;   
    POSITION_ next;
};

void deWeight(char *Key);//去重同时去非可见字符
L_ initialKey(char *Key);
POSITION_ delete(POSITION_ P);//删除P位置, 并将P下一位置返回
POSITION_ findPrevious(POSITION_ P);//找不着返回null. 因为是环表, 所以不需要额外传入链表
void encode(char *CipherKey);//将加密哈希数组传入
// 无用函数int getLen(L_ Key);//返回当前环的长度

int main()
{
    char Key[40], CipherKey[SIZE];//哈希值存储原字符, 内容存储加密后字符
    POSITION_  Last;
    int i, k, len, first;
    gets(Key);
    deWeight(Key);
    Last = initialKey(Key);
    first = (int)Last->element;
    len = VISIBLE_END - VISIBLE_BEGIN + 1;
    //以上正确
    while (Last != NULL)
    {
        i = (int)Last->element;
        Last = delete(Last);//此处已经向后移1位    
        if (Last == NULL)//最后的情况
        {
            CipherKey[i] = first;
            break;
        }
        if (i%(len -1 ))
            for (k = 1; k < i%(len-1); k++, Last = Last->next);//? %可能是潜在的问题 i%(len-1)
        else    //注意i%(len-1)这点, 当i%(len-1)=0时,因为已经移动了一位,会造成程序错误. 
            Last = findPrevious(Last);
        CipherKey[i] = Last->element;
        len--;
    }
    encode(CipherKey);
    return 0;
}


void deWeight(char *Key)//去重
{
    int Hash[SIZE], i, k = 0;
    memset(Hash, 0, sizeof(Hash));
    for (i = 0; i < strlen(Key); i++)
    {
        if (!Hash[Key[i]] && VISIBLE_BEGIN<=Key[i] && VISIBLE_END >= Key[i])
        {
            Hash[Key[i]] = 1;
            Key[k] = Key[i];
            k++;
        }
    }
    Key[k] = '\0';
}

L_ initialKey(char *Key)
{
    L_ Head = (L_)malloc(sizeof(struct Node));
    POSITION_ P = Head, Tmp;
    int Hash[SIZE], i, len = strlen(Key);
    memset(Hash, 0, sizeof(Hash));
    for (i = 0; i < len; i++)
    {
        Hash[Key[i]] = 1;
        P->element = Key[i];
        P->next = (POSITION_)malloc(sizeof(struct Node)); 
        P = P->next;
    }

    for (i = VISIBLE_BEGIN; i <= VISIBLE_END; i++)
    {
        if (!Hash[i])
        {
            P->element = i;
            if (i < VISIBLE_END)//??如果126位已经出现过该怎么办??
            {
                P->next = (POSITION_)malloc(sizeof(struct Node));
                P = P->next;
            }
            else
                P->next = Head;
        }

        if (Hash[126])//这是避免126~已经在key中出现的情况, 这种情况下上述对环结束的判断会不准确.
        {
            Tmp = findPrevious(P);
            free(P);
            Tmp->next = Head;
        }
    }
    return Head;
}

POSITION_ delete(POSITION_ P)
{
    POSITION_ Tmp;
    Tmp = findPrevious(P);
    if (Tmp == NULL)
        return NULL;
    else if (Tmp == P)//这是针对仅剩一个的情况
        return NULL;
    else
    {
        Tmp->next = P->next;
        free(P);
    }
    return Tmp->next;
}

POSITION_ findPrevious(POSITION_ P)
{
    POSITION_ Tmp = P->next;//正常表不能这样写, 反正P是最后一个传回null
    while(Tmp != NULL)//虽然这种情况肯定不会出现..
    {
        if (Tmp->next == P)
            break;
        Tmp = Tmp->next;
    }
    return Tmp;
}

void encode(char *CipherKey)
{
    FILE * fp_in, * fp_out;
    char Str[500];
    int i;
    fp_in = fopen("in.txt", "r");
    freopen("in_crpyt.txt", "w", stdout);
    while(fgets(Str, 500, fp_in) != NULL)
    {
        Str[strlen(Str)] = '\0';
        for (i = 0; i < strlen(Str); i++)
        {
            if (Str[i] >= VISIBLE_BEGIN && Str[i]<= VISIBLE_END)
                Str[i] = CipherKey[Str[i]];
        }
        printf("%s", Str);
    }
}
/*
规划失误, 无用函数
int getLen(L_ Key)
{
    POSITION_ P = Key->next;
    int i = 1;
    while(P != NULL)//虽然环表肯定不会用上
    {
        if (P == Key)
            break;
        i++;
        P = P->next;
    }
    return i;
}
*/