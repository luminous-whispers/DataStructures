#include<iostream>
#include<cstring>

using namespace std;
int a[1010],b[1010];         //用于存储拆解后的数字 
void dh()
{
    int an,bn,i;
    char ac[1010],bc[1010];
    cin >>ac>>bc;
    a[0]=strlen(ac);          //a高精度数的位数存在a[0]中 
    for(i=1; i<=a[0]; i++) a[i] = ac[a[0]-i] - '0'; //倒序存储数字（+、-\*）
    b[0]=strlen(bc);          //b高精度数的位数存在b[0]中 
    for(i=1;i<=b[0];i++) b[i] = bc[b[0]-i] - '0';//倒序存储数字（+、-\*）
    return;
}
int main()
{
    dh();
    return 0;
}
（二）、运算结果的