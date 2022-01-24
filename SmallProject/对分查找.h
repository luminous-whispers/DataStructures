#define notFound -1
/* 三种方法最核心的差异体现在对" A[Mid] == X这种情况的处理上, 当出现该情况选择直接退出, 就是准确查找; 
如果出现这种情况, 选择令High= Mid-１,　则是大于等于Ｘ的近似查找;
如果出现该情况,　选择令Low= Mid+ 1,则是大于Ｘ的近似查找;
要理解后两种方式的原理,　只需记住最后输出的是Ｌｏｗ,一旦出现了Ａ[Ｍｉｄ]＝＝Ｘ的情况,　固定为Ｍｉｄ＋－１的那个变量就不会再变了,　另一变量不断接近该变量. */

int
binarySearch( const int A[ ], int X , int N )
{
    int Low, Mid, High;

    Low= 0; High= N- 1; 
    while( Low <= High )
    {
        Mid= ( Low + High )/ 2;
        
        if( A[ Mid ] < X )
            Low= Mid+ 1;
        else if ( A[ Mid ] > X )
            High= Mid- 1;
        else
            return Mid;
    }
    return notFound;
}

int
binaryMoreOrEqualSearch( const int A[ ], int X , int N )//>=
{
    int High= N- 1, Low= 0;
    int Mid= ( Low + High )/ 2;
    while( Low <= High )
    {
        Mid=( Low + High )/ 2;

        if( A[ Mid ] >= X )
            High = Mid- 1;
        else   
            Low= Mid+ 1;
    }

    if( Low == N + 1 )//唯一的找不到的情况是, X比数组中任意数都大, 即数组中没有>=X的数据
        return notFound;
    else   
        return Low;
}

int
binaryMoreSearch( const int A[ ], int X , int N )//>=
{
    int High= N- 1, Low= 0;
    int Mid= ( Low + High )/ 2;
    while( Low <= High )
    {
        Mid=( Low + High )/ 2;

        if( A[ Mid ] > X )
            High = Mid- 1;
        else   
            Low= Mid+ 1;
    }

    if( Low == N + 1 )
        return notFound;
    else   
        return Low;
}