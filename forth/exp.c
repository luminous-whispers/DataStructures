#include<stdio.h>
#include<string.h>

char str[50];
void Delete(int pos, int n, int sum)
{
    int i, j;
    i = pos;
    j = pos + n;
    if (j >= sum)
    {
        str[i] = 0;
        return ;
    }
    while (j != sum)
    {
        str[i++] = str[j++];
    }
    str[i] = 0;
    sum = strlen(str);
}

int main()
{
    char azhe[]="hhoh", tmp;
    int sum ;
    gets(str);
    sum = strlen(str);
    Delete(2, 2, sum);
    return 0;
}