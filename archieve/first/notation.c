//file info: filename, author, date of modification, version
//brief dexcription.
#include<stdio.h>
#include<string.h>

int findComma(char[]);//检测逗号,返回其在数组中的位置
int ifSingle(char[]);//如果只有一个非零数字, 返回1

main(){
    char Str[101];
    int Position, flag;
    char *P1_, *P2_, *P0_;

    gets(Str);

    Position= findComma(Str);
    if (Position == 1){
        if (Str[0] == '0'){
            flag= Position+ 1;
            while (1){
                if (Str[flag] != '0')
                    break;
                flag++;
            }
            P0_= &Str[flag+ 1];
            if(ifSingle(Str) == 1)
                printf("%ce-%d", Str[flag], flag- 1);
            else
                printf("%c.%se-%d", Str[flag], P0_, flag- 1);
        }
        else{
            printf("%se0", Str);
        }
    }
    else{
        P2_= &Str[Position+ 1];
        P1_= &Str[1];
        Str[Position]= '\0';
        if(ifSingle(Str) == 1)
                printf("%ce%d", Str[0], Position- 1);
        else
            printf("%c.%s%se%d", Str[0], P1_, P2_, Position- 1);

    }

}

int findComma(char Str[]){
    int flag= 0;
    while (1){
        if (Str[flag] == '.')
            break;
        flag++;
    }
    return flag;
}


int ifSingle(char Str[]){
    int len= strlen(Str), flag= 0;
    while (len--){
        if(Str[len] != '0' && Str[len] != '.')
            flag++;
    }
    return flag;
} 