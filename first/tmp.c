#include<stdio.h>
#include<string.h>

main(){
    char str[]= "hello", str1[]= "emmmm";
    if(strcmp(str, str1) > 0)
        printf("1");
    else    
        printf("hello");
    return;
}