/*插入排序很像打扑克牌, 挨个判断顺序, 即轮到插入P时, 假定前P-1个已经排好序*/
#define ELEMENT_TYPE int

void UpInsertionSort( ELEMENT_TYPE a[], int n)
{
    int j, p;
    ELEMENT_TYPE Tmp;
    for (p = 1; p < n; p++)
    {
        Tmp = a[p];
        for (j = p; (j > 0) && (a[j-1] > Tmp); j--)
            a[j] = a[j-1];
        a[j] = Tmp; 
    }
}