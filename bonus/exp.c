#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

int main()
{
    FILE * fp;
    char a;
    fp = fopen("bonus\\reference\\dictionary.txt", "r");
    fsetpos(fp, 3);
    
    a = fgetc(fp);
    printf("%c", a);
    return 0;
}