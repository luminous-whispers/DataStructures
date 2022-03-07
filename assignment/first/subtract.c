#include<stdio.h>
#include<string.h>

int digits(char[]);
int length(char[]);
char *checkWhichBigger(char[], char[], int, int);//从数字起始位置开始比较两数大小
void carryBit(char[]);//将直接相减的数进行进位,得到最终结果

main(){
    char *Max, *Min;
    char AStr[100], BStr[100], ResultStr[100];
    int LengthA, LengthB, DigitsA, DigitsB;

    gets(AStr);
    LengthA= length(AStr);
    DigitsA= digits(AStr);

    gets(BStr);
    LengthB= length(BStr);
    DigitsB= digits(BStr);

    if (checkWhichBigger(AStr, BStr, LengthA- DigitsA, LengthB- DigitsB) == AStr){
        
    }
    else{
        //printf(-)
    }




     
}