/*diminishing increment sort*/
#define ELEMENT_TYPE int
void
ShellSort( ELEMENT_TYPE a[], int N )
{
    int i, j, increment;
    ELEMENT_TYPE Tmp;

    for (increment = N/2; increment > 0; increment /= 2)
        for (i = increment; i < N; i++)
        {
            Tmp = a[i];
            for (j = i; j >= increment; j -= increment)
                if (Tmp < a[j-increment])
                    a[j] = a[j-increment];
                else
                    break;
            a[j] = Tmp;
        }
}

/*希尔排序的复杂度很难计算
并且希尔本人使用的增量序列(N/2)也不是最佳的*/