#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
long Index[150];

int main()
{
    int i;
    FILE  *fp;
    char str[50], flag = 'a';
    fp = fopen("F:\\notes\\assign\\bonus\\dictionary.txt", "r");
    while (flag != 'z'+1)
    {
        fgets(str, 50, fp);
        if (str[0] == flag)
        {
            Index[(int)flag] = ftell(fp);
            flag ++;
            printf("%ld\n", ftell(fp));
        }
    }

    freopen("dictResult.txt", "w",  stdout);
    for (i=0; i<150; i++)
    {
        if (Index[i] != 0)
            printf("%ld\n", Index[i]);
    }
    return 0;
}
