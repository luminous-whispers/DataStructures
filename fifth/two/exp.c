#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

int main()
{
    char str1[]="hello", str2[]="hellohahah";
    printf("%d", strcmp(str1, str2));
    return 0;
}