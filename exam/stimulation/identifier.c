#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

struct NODE;
struct NODE{
    char str[50];
}sign[60];

int IsLetter(char a)//必须以_或字母开头
{
    if (a>='a' && a<='z')
        return 1;
    else if (a>='A' && a<='Z')
        return 1;
    else 
        return 0;
}

int FindSign(char * p)//返回步长
{
    int i=0;
    if (!IsLetter(*p) || *p!='_')
        return 0;//错误, 肯定不是标识符开头
    while (1)
    {
        if (*(p+i)>='a' && *(p+i)<='z')
            i++;
        else if (*(p+i)>='A' && *(p+i)<='Z')
            i++;
        else if (*(p+i)>='0' && *(p+i)<='9')
            i++;
        else if (*(p+i)=='_')
            i++;
        else
            return i;
    }
}

int main()
{
    char content[150], *p;
    gets(content);
    //标识符包括: 自定义变量名, 函数名, 参数名, 自定类型名
    return 0;
}