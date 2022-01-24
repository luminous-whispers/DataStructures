int 
maxSubsequenceSum( const int A[ ], int N )
{
    int ThisSum, MaxSum, i;

    ThisSum= MaxSum= 0;
    for( i= 1; i< N; i++)
    {
        ThisSum += A[i];

        if(ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if (ThisSum < 0)
        //一旦前面的ｓｕｍ小于零，就说明它对后面的和就没有作用了。　
        //由于前面的ＭａｘＳｕｍ已经被记录，所以可以大胆的舍弃掉前面已经没有作用的和。
            ThisSum = 0;
            
    }
    return 0;

}