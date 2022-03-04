#include<stdio.h>
#include<string.h>

typedef char *POSITION;
typedef int *EXCURSION;

void printUntilFindSign(EXCURSION X_, char *P);//P会返回-坐标值,之前一直打印
void checkOut(EXCURSION X_, char *P);//1代表成功， 0代表不是
void printSpecial(int X, char *P);//展开破折号


main()
{
    POSITION P ;
    int X= 0;
    EXCURSION X_= &X;
    char str[100];

    gets(str);
    P= str;

    do{
        printUntilFindSign(X_,P);
        checkOut(X_, P);
    }
    while (*(P + X) != '\0');

}


//! 这里有个大坑,c语言不能进行传址,只能传递数值,仅仅将数据拷贝一份而已. 
//要做到传址,需将地址传递过去后,对同一地址进行修改,从而做到跨域进行变量修改的目的
//但这样不能改变指向这个地址的指针!!!这很容易造成混淆,也就是说指针本身也是一个储存地址的变量而已,我们对指针指向的地址可以修改,但不能修改指针的值
//要改变这个指针的值,需要利用二级指针. 但使用二级指针进行偏移时会按照一级指针的大小偏移,这可能会造成困扰
//如果一定要按一级指针的偏移量来改变第一指针
void printUntilFindSign(EXCURSION X_, char *P){
    
    int X= *X_;
    for (; *(P + X) != '-' && *(P+ X) != '\0' ; X++)
        printf("%c", *(P + X));//注意-之前的一个也打印出来了

    *X_= X;
}


void checkOut(EXCURSION X_, char *P){
    
    int X= *X_;
    char C1= *(P +X -1), C2= *(P +X +1);

    if (*(P+ X) == '\0')
        return ;
    if ((C2- C1) <= 0){
        printf("-");
        X++;
        *X_= X;
        return ;
    }

    if (C1 <= 'Z' && C1 >= 'A'){
        if (C2 <= 'Z' && C2 >= 'A'){
            printSpecial(X, P);
            X++;
        }
        else{
            printf("-");
            X++;
        }
    }
    else if (C1 <= 'z' && C1 >= 'a'){
        if (C2 <= 'z' && C2 >= 'a'){
            printSpecial(X, P);
            X++;//原本基础不扎实犯了个错: *X_++这样写意思和(*X_)++完全不同,和*(X_++)也不同
            //注意*和++的优先级相同，运算顺序从右向左，所以*p++就相当于*(p++)；
            //但后自加本身的性质又决定了, 先执行前面的*p, 后执行p++
            //*(++p)是先加地址再取值； ++(*p)和(*p)++才是对内存指向内容进行修改

        }
        else{
            printf("-");
            X++;
        }
    }
    else if (C1 <= '9' && C1 >= '0'){
        if (C2 <= '9' && C2 >= '0'){
            printSpecial(X, P);
            X++;
        }
        else{
            printf("-");
            X++;
        }
    }
    else{
        printf("-");
        X++;
    }

    *X_= X;
}


void printSpecial(int X, char *P){
    
    char C1= *(P+ X- 1), C2= *(P +X +1), C3;
    for (C3= C1+1; C3 != C2; )
        printf("%c", C3++);
}