#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

/* 对分查找基本例程 */
#define ELEMENT_TYPE int
int BinSearch(ELEMENT_TYPE data[], int num, ELEMENT_TYPE key)
{
    int low, high = num- 1, mid;
    while (low <= high)
    {
        mid = (high+ low)/ 2;
        if (key < data[mid])
            high = mid - 1;
        else if (key > data[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;//查找失败
}

//recursion, 
//high = num-1,like index
int BinSearch_rec(ELEMENT_TYPE data[], int low, int high, ELEMENT_TYPE key)
{
    int mid = (low+ high)/ 2;
    if (key == data[mid])
        return mid;
    if (key < data[mid])
        return BinSearch_rec(data, low, mid-1, key);
    else
        return BinSearch_rec(data, mid+1, high, key);
}
//!注意这个没有处理查找值不存在的情况, 会造成递归无法停止