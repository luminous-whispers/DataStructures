#include<stdio.h>
#include<string.h>

typedef char *POSITION;
POSITION P ;

void printSpecial(char *P){
    char C1= *(P- 1), C2= *(P+ 1), C3;

    for(C3= C1+1; C3 != C2; )
        printf("%c", C3++);
}


void checkOut(char *P){
    char C1= *(P - 1), C2= *(P + 1);
    if((C2- C1) <= 0)
        return ;
    if(C1 <= 'Z' && C1 >= 'A'){
        if (C2 <= 'Z' && C2 >= 'A')
            printSpecial(P);
    }
    else if(C1 <= 'z' && C1 >= 'a'){
        if(C2 <= 'z' && C2 >= 'a')
            printSpecial(P);
    }
    else if(C1 <= '9' && C1 >= '0'){
        if(C2 <= '9' && C2 >= '0')
            printSpecial(P);
    }
}

void changeP(POSITION *PtrP_){
    *PtrP_++;
}

main(){
    char str[100];
    gets(str);
    P= str+3;
    POSITION *PtrP_= &P;
    changeP(PtrP_);
}