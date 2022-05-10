/*
第三次作业第五题, 读取文章中单词,并统计频次
考察点是链表的构造, 查找和删除
较大借鉴second/replace.c的函数算法
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _LIST_WORD_H_
#define _LIST_WORD_H_

    struct NODE;
    typedef struct NODE *POSITION_;
    typedef POSITION_ LIST_;
    typedef POSITION_ PTR_WORD_;

    struct NODE{
        char Words[20];
        int Frequence;
        PTR_WORD_ Next_;
    };
    void toLower(char *);
    int isLetter(char *);//看是否是字母
    int readWord(char * restr, char *src);//向后读取一个单词, 并返回该单词的长度

    void insert(char *, LIST_, POSITION_ Last);//在last后插入表元, 并完成相应初始化
     POSITION_ find(char *Str, LIST_);//找不到会返回近似上一位置, 需要再比较一次,字典序一旦大于就会立刻停止查找
    int isLast(LIST_, POSITION_);
    LIST_ initial();//开辟一个头指针,头指针不存储任何值
 
#endif

int main()
{
    FILE *fp;
    char Tmp[200], Word[20];
    POSITION_ p, L;
    int i = 0, len = 0;
    L = initial();

    fp = fopen("article.txt", "r");
    while (fgets(Tmp, 200, fp) != NULL)//按行读入
    {
        Tmp[ strlen(Tmp) ] = '\0';//!这是什么智障操作?? fgets函数会自动添加\0, 
        //!坑是会将末尾\n也读进来, 尤其是win下会读入\r\n,输出时就是两个换行了..
        toLower(Tmp);

        for (i = 0; Tmp[i] != '\0'; i+=len)//按单词往后跳
        {
            if (isLetter(&Tmp[i]))
            {
                len = readWord(Word, &Tmp[i]);
                p = find(Word, L);
                if (!strcmp(p->Words, Word))
                    p->Frequence++;
                else
                    insert(Word, L, p);//p后插入word表元
            }
            else
                len = 1;//!
        }
    }

    p = L->Next_;//之后L扮演上一个地址的角色
    free(L);//释放头链表元
    while (p != NULL)//默认必须至少有一个单词吧
    {
        printf("%s %d\n", p->Words, p->Frequence);
        L = p;
        p = p->Next_;
        free(L);
    }
    return 0;
}

int readWord(char *restr, char *src)//有错, 读入了want;
{
    int len;
    for (len = 1; isLetter(src + len); len++);
    strncpy(restr, src, len);//千万注意strncpy不会自动添加\0(一般主动规定长度的函数都不会自动加\0)
    *(restr + len) = '\0';
    return len;
}

void toLower(char * p)
{
    int i = 0;
    while (*(p + i) != '\0')
    {
        if( *(p + i) >= 'A' && *(p + i) <= 'Z')
            *(p + i) +=  'a' - 'A';
        i++;
    }
} 

int isLetter(char * p)
{
    if (*p >= 'a' && *p <= 'z')
        return 1;
    return 0;
}

LIST_ initial()
{
    /*
    注意开辟一个表的操作不能在函数域内声明一个结构体
    只能使用malloc操作, 才能传出一块内存
    声明的结构体在函数结束时生命也会结束.
    */
   LIST_ L;
   L = (PTR_WORD_)malloc(sizeof(struct NODE));
   L->Frequence = 0;
   L->Next_ = NULL;
   memset(L->Words,0,sizeof(L->Words));
   return L;
}

int isLast(LIST_ L, POSITION_ P)
{
    return P->Next_ == NULL;
}

void insert(char * Word, LIST_ L, POSITION_ Last)//last <=> previous
{
    PTR_WORD_ P;
    P = (PTR_WORD_)malloc(sizeof(struct NODE));
    strcpy(P->Words, Word);

    P->Frequence = 1;
    P->Next_ = Last->Next_;
    Last->Next_ = P;
}

/*
模糊查找
如果查找值存在, 则返回查找值位置
如果查找值不存在, 则按字典序返回上一个最接近的值
*/
POSITION_ find(char *Str, LIST_ L)
{
    POSITION_ P = L;//之后L负责记录的是P上一个表元;
    while (P->Next_ != NULL)
    {
        L = P;
        P = P->Next_;
        if (!strcmp(Str, P->Words))//精确值
            return P;
        else if(strcmp(Str, P->Words) < 0)//模糊值
            return L;
    }
    return P;//?末尾也没有找到
}