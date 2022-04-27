/*
也可用于寻找中位数
也称为BFPRT算法.
除此之外, 拆半寻中位数的方法也比较巧妙
https://codeantenna.com/a/3W9TMD9FDo
*/
#include<stdio.h>

int *insertSort(int *Data, int Len, int Mode);//mode1代表升序, 0代表降序
int bfprt(int *Data, int Len);

int bfprt(int *Data, int Len)
{
    const int Size = 5;
    int i;
    if (Len <= Size)//递归结束条件
    {
        insertSort(Data, Len, 1);
        return *(Data + Len/2);
    }
    for (i = 0; i < Len-5; i += Size)
    {
        insertSort(Data+i, Size, 1);
        *(Data+i/Size) = *(Data+i+Size/2+1);
    }
    insertSort(Data+i-Size, Len-i+Size+1, 1);
    *(Data+i/Size) = *(Data+i-Size/2);
    return bfprt(Data, Len/5+1);
}

int * insertSort(int *Data, int Len, int Mode)
{
    int i, j, Tmp = 0;
    if (Mode)
    {
        for (i=1; i<Len; i++)
        {
            for (j=0; j<i; j++)
            {
                if (*(Data+j) > *(Data+i))
                {
                    Tmp = *(Data+i);
                    *(Data+i) = *(Data+j);
                    *(Data+j) = Tmp;
                }
            }
        }
    }
    else if(!Mode)
    {
        for (i=1; i<Len; i++)
        {
            for (j=0; j<i; j++)
            {
                if (*(Data+j) < *(Data+i))
                {
                    Tmp = *(Data+i);
                    *(Data+i) = *(Data+j);
                    *(Data+j) = Tmp;
                }
            }
        }       
    }
    else
        printf("please input correct mode1");

}

int main()
{
    int i, array[]={1, 2};
    printf("%d", bfprt(array, 2));
    return 0;
}
