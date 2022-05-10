/*
第一次作业读入和计算复杂表达式问题
核心是利用栈对数字和符号进行分别处理
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void preTreatment(char[], char[], int[]);//并记录栈顶(能否这样写形参??)
void insertSign();
void popNumberStack();
int operation(int, int, char);
int len(char[]);//等号判断Str有多长
int judgeSign(char SignIn, char SignOut);//判断符号级别, 需要弹出返回1, 不需要弹出返回0;
int turnNumber(char[], int);
int powOfInt(int, int index);
int jumpNumber(char[], int);

int NumberStackIn[100], NumberStackOut[100];
//stack后入先出,0最后出; 
char SignStackIn[100], SignStackOut[100];
char Str[200];
int StackNI= 0, StackNO= 0, StackSI= 0, StackSO= 0;



main()
{

    gets(Str);
    preTreatment(Str, SignStackIn, NumberStackIn);

    while (1){
        //以栈清空为结束条件
        NumberStackOut[ StackNO++ ]= NumberStackIn[ --StackNI ];//数字无障碍填入, 填完后栈顶上移
        if (StackNI == 0)//当全部填入后, 退出, 在外部进行下一步计算.放这里是因为数字是最后一个填入的
            break;
        insertSign();
    }
    
    //just operate
    while(1){
        if (StackSO == 0)
            break;
        popNumberStack();
    }

    printf("%d", NumberStackOut[StackNO- 1]);
}


void insertSign(){

    if (SignStackIn[0] == '\0')
        return;
    else if (StackSO == 0)
        SignStackOut[ StackSO++ ]= SignStackIn[ --StackSI ];
    else if (judgeSign(SignStackIn[ StackSI- 1 ], SignStackOut[ StackSO- 1 ]) == 0)
        SignStackOut[ StackSO++ ]= SignStackIn[ --StackSI ];
    else {
        //不填入字符, 弹出上一符号, 运算后数字再次填入数字栈中.
        popNumberStack();
        insertSign();
    }
}


void popNumberStack(){
    NumberStackOut[ StackNO- 2 ]=
            operation(NumberStackOut[ StackNO- 1 ], NumberStackOut[ StackNO- 2 ], SignStackOut[ StackSO- 1 ]);
    StackNO -= 1;
    StackSO -= 1;
}


int operation(int num1, int num2, char sign){
    //just operate
    if (sign == '+'){
        return num1+ num2;
    }
    else if (sign == '-'){
        return num1- num2;
    }
    else if (sign == '*'){
        return num1* num2;
    }
    else if (sign == '/'){
        return num1/num2;
    }
}


// int len(char str[]){
//     //return the length of the input string.
//     //!注意, 和其他形参不同的是,数组名作为形参,不会进行值的传递,只进行地址传递. 并且无法一并传递下标
//     int n= 1;
//     while ( str[n- 1] != '=')
//         n++;
//     //the real length ignoring the excursion of 0 in nomarl array.
//     return n;
// }


int judgeSign(char SignIn, char SignOut){
    if (SignIn == '+' || SignIn == '-'){
        if (SignOut == '+' || SignOut == '-')
            return 0;
        else return 1;
    }
    else
        return 0;
}


void preTreatment(char Str[], char SignStackIn[], int NumberStackIn[]){
    //对读入字符串预先处理, 去除空格, 数字/符号分别存入对应栈中, 然后修改栈顶指向.
    int i= 0, n= 0, s= 0;
    
    while(Str[i] != '='){
        //注意跳步
        if (Str[i] >= '0' && Str[i] <= '9'){
            NumberStackIn[n++]= turnNumber(Str, i);
            i= jumpNumber(Str, i);
        }
        else if(Str[i] == '+' || Str[i] == '-' || Str[i] == '*' ||Str[i] == '/'){
            SignStackIn[s++]= Str[i];
            i++;
        }
        else
            i++;

    }
    StackNI= n;
    StackSI= s;
}


int turnNumber(char Str[], int i){
    //将此位置的字符转化为数字
    int Position= i, Index, Number= 0; 
    while (1){
        if (Str[Position+ 1] >= '0' && Str[Position+ 1] <= '9')
            Position++;
        else    
            break;
    }

    Index= Position- i+ 1;
    while (Index--){
        Number += powOfInt(10, Index)* (int)( Str[i++]- '0' );
    }
    return Number;

}


int powOfInt(int num, int index){

    int result= 1;
    while (index--)
        result *= num;
    return result;
}


int jumpNumber(char Str[], int i){
    //跳过字符中的当前数字
        int Position= i; 
    while (1){
        if (Str[Position+ 1] >= '0' && Str[Position+ 1] <= '9')
            Position++;
        else    
            break;
    }
    return Position+ 1;

}