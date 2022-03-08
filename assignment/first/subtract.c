#include<stdio.h>
#include<string.h>

int findEndOfZero(char[], int[]);//可以检测两种类型数组,不想检测类型传入null即可
int digits(char[]);//利用findendofzero函数,反馈真是数字位数
int length(char[]);
int compare(char[], char[]);//比较两字符串代表的数大小,没有前导0
void turnIntoNum(char[], int[]);//将字符数组转化为数字数组; 并去除前导0
char *pretreatment(char[], int[]);
void preSubtract(int[], int[]);//前减后,负数保留
void carryBit(int[]);//将直接相减的数进行进位,得到最终结果

int main(){
    char *P_A, *P_B;
    char AStr[100], BStr[100];
    int ANum[100], BNum[100];
    int i;

//这个封装起来.传入str和num两个地址即可. 然后将前导0地址返回.
    P_A= pretreatment(AStr, ANum);
    P_B= pretreatment(BStr, BNum);

    if (compare(P_A, P_B) == 1)//strcmp有问题,当一个字符串到头了它就停止了
    {
        preSubtract(ANum, BNum);
        carryBit(ANum);
        for (i = findEndOfZero(NULL, ANum); ANum[i] != 10; i++)
        {
            printf("%d", ANum[i]);
        }
    }
    else if (compare(P_A, P_B) == 0)//!负数处理上还是有问题,预测是34,35行两函数的细节问题
    {
        preSubtract(BNum, ANum);
        carryBit(BNum);
        printf("-");
        for (i = findEndOfZero(NULL, BNum); BNum[i] != 10; i++)
        {
            printf("%d", BNum[i]);
        }
    }
    else
        printf("0");

    return 0;
}


char *pretreatment(char Str[], int Num[]){
    int Length, Digits;

    gets(Str);
    Length= length(Str);
    Digits= digits(Str);
    turnIntoNum(Str, Num);

    return &Str[Length - Digits];
}

//寻找前导零结束位置
int findEndOfZero(char Str[], int Num[])
{
    int i = 0;
    if(Num == NULL)
    {
        for (;;i++)
        {
            if(Str[i] != '0')
                break;
        }
    }
    else
    {
        for (;;i++)
        {
            if(Num[i] != 0)
                break;
        }
    }
    return i;
}

//反馈数字真实位数(即不计前导0)
int digits(char Str[])
{
    int i;
    char *P;

    i = findEndOfZero(Str, NULL);
    P = &Str[i];
    return strlen(P);
}

//返回长度
int length(char Str[])
{
    return strlen(Str);
}

//将字符数组转化为数字数组
void turnIntoNum(char Str[], int Num[])
{
    int i = findEndOfZero(Str, NULL), n = 0;
    for(;i < strlen(Str); i++, n++)
    {
        Num[n] = Str[i] - '0';
    }
    Num[n] = 10;//标识出数据结尾,前面一定为个位
    return;
}

//按位相减,简单粗暴
void preSubtract(int A[], int B[])
{
    int i = 0, n, EndOfA, EndOfB;
    while(1)
    {
        if (A[i++] == 10)
            break; 
    }
    EndOfA= i-1;
    i = 0;
    while(1)
    {
        if (B[i++] == 10)
            break; 
    }
    EndOfB= i-1;

    for (i= EndOfB-1, n= EndOfA-1; i>=0  ; i--, n--)
    {
        A[n] -= B[i];
    } 
    return;
}

//核心-进位机制
void carryBit(int Str[])
{
    int i;
    for (i=0;; i++)
    {
        if (Str[i] == 10)
            break;
    }

    for (i--;i>=0;i--)
    {
        if (Str[i] >= 0)
            continue;
        else 
        {
            Str[i] = 10 + Str[i];
            Str[i-1] = Str[i-1] - 1;
        }
    }
    return;
}

//比较两字符串数字大小,返回1代表前面的大
//因为数据可能阴间,所以谨慎起见用递归验证到最后 
int
compare(char Str1[], char Str2[])
{
    int i= strlen(Str1) - strlen(Str2);
    if (strlen(Str1) == 0 || strlen(Str2) == 0)//返回-1代表完全相同
        return -1;
        
    if (i > 0)
    {
        return 1;
    }
    else if (i < 0)
    {
        return 0;
    }
    else
    {
        if(Str1[0] > Str2[0])
            return 1;
        else if(Str1[0] < Str2[0])
            return 0;
        else
            return compare(&Str1[1], &Str2[1]);
    }
}