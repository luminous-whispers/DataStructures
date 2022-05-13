#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* 
textFileInput(char* filename)
{
    char* text;
    long lSize;

    FILE *pf = fopen(filename, "r");
    if (pf == NULL)
        return NULL;

    fseek(pf,0,SEEK_END);//将位置指针移动到最后
    lSize = ftell(pf);//找出位置指针偏移量,这是地址的实际偏移量
    // 用完后需要将内存free掉
    text = (char*)calloc(lSize, 1);//留出\0位置
    rewind(pf); //将指针回调至文件首,方便fread函数
    fread(text, sizeof(char), lSize, pf);//始终记得检查fread返回值 (看和lsize是否一致)
    fclose(pf);
    text[lSize] = '\0';//!这条语句为什么没有正常执行??
    return text;
}

int main()
{
    char *str[500];
    textFileInput("filein.txt");

    printf("%s", str);
    return 0;
}