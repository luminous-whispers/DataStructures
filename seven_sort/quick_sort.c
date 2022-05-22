#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

#define ELEMENT_TYPE int
/*单次, 双向扫描*/
int Partion(ELEMENT_TYPE *array, int l, int r)
{
    int pivot = array[l];
    while (l < r)
    {
        while (pivot<=array[r] && l<r)
            r--;
        array[l] = array[r];
        while (array[l]<pivot && l<r)
            l++;
        array[r] = array[l];
    }
    array[l] = pivot;
    return l;//l = r
}
void QuickSort(ELEMENT_TYPE *array, int l, int r)
{
    int k;
    if (l < r){
        k = Partion(array, l, r);
        QuickSort(array, l, k-1);//divide->conquer
        QuickSort(array, k+1, r);
    }
}

int main()
{       
    clock_t start, end; 
    start = clock(); 
    
    end = clock();
    printf("time = %lf (s)\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}