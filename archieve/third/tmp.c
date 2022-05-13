#include<stdio.h>
#include<string.h>

int main()
{
    int i=1; 
    int j=0; 
    int n =10, count = 0;
    while(i+j<=n)
    { 
        if(i>j) 
        {
            count++;
            j++;
        }
        else 
            i++; 

    }
    printf("%d", count);
    return 0;
}
