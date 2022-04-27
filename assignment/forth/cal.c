/*第四次作业 栈与队的第三题
即老师上课讲的后缀表达式转换与计算的升级版
本题调试过程中被指点了一个新方法, 在可能越界访问的地方输出查看一个访问值可以有效验证
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum SYMBOL {OP, NUM, ELSE, EQ};
enum OPERATOR {ADD, SUB, DIV, MUL, L_BRA, R_BRA};//和键类似
int Pri[] = {0,0,1,1,2,3};//!规定优先级

enum OPERATOR signStack[300];
int sTop = -1;
float numStack[300];
int nTop = -1;
//!约定, 对栈的操作默认为全局变量, 对栈顶和栈的"操作和调用"都"在最底层进行
//这样牺牲了可维护性和可读性, 便捷了程序编写

union ELEMENT
{
    /* 这里使用联合体是为了配合上面对symbol的划分,将对符号类型的判断隐藏在底层
    这样,提高上层程序的扩展性,因为能用一个参数传递多种类型的变量 */
    float num;
    enum OPERATOR op;
};

//kernel
enum SYMBOL IdentifySym(union ELEMENT *);//同时读取入地址
float Compute(float top, float bottom, enum OPERATOR);//返回结果
void Operator(enum OPERATOR);//后缀表达式逻辑判断, 符号入栈并进行一系列计算

//normal
enum OPERATOR PopS();//仅移动栈顶,数据直接覆盖
float PopN();

void PushS(enum OPERATOR);
void PushN(float);

int main()
{
    enum SYMBOL sym;
    union ELEMENT item;
    float top, bottom;
    while((sym=IdentifySym(&item)) != EQ)
    {
        if (sym == OP)
        {
            Operator(item.op);
        }
        else if (sym == NUM)
        {
            PushN(item.num);
        }
    }
    if (sTop != -1)
    {
        while (nTop)
        {
            top = PopN();
            bottom = PopN();
            item.num = Compute(top, bottom, PopS());//!
            PushN(item.num);
        }
    }
    printf("%.2f", PopN());
}

enum SYMBOL 
IdentifySym(union ELEMENT * s)
{
    char c;
    float n;
    while ((c=getchar()) != '=')
        if (c>='0' && c<='9')
        {
            for (n=0; c>='0' && c<='9'; c=getchar())
                n = n*10 + (float)(c-'0');
            ungetc(c, stdin);
            s->num = n;
            return NUM;
        }
        else
        {
            switch (c)
            {
                case '+':
                    s->op = ADD;
                    return OP;
                case '-':
                    s->op = SUB;
                    return OP;
                case '*':
                    s->op = MUL;
                    return OP;
                case '/':
                    s->op = DIV;
                    return OP;
                case '(':
                    s->op = L_BRA;
                    return OP;
                case ')':
                    s->op = R_BRA;
                    return OP;
                default :
                    continue;
            }
        }

    return EQ;
}

float 
Compute(float top, float bottom, enum OPERATOR sign)
{
    switch (sign)
    {
        case ADD:
            return top + bottom;
        case SUB:
            return bottom - top;
        case DIV:
            return bottom / top;
        case MUL:
            return bottom * top;
    }
}

void 
Operator(enum OPERATOR sign)
{
    float n = 0, top, bottom;
    enum OPERATOR op;
    if (sign == R_BRA)
    {
        for (op=PopS(); op!=L_BRA; op=PopS())
        {
            top = PopN();
            bottom = PopN();
            n = Compute(top, bottom, op);//这里出栈好像是个大坑, 参数出栈的顺序是从右向左
            PushN(n);
        }
    }
    else
    {
        if (sTop == -1)
            PushS(sign);
        else
        {
            //!注意这里第一个判断条件, 循环pop可能导致stop出现-1,如果不加这个就会越界访问[-1]
            //!并且这个错误不会报错! 越界访问时会直接终止循环, 这个错误非常隐蔽
            while (sTop != -1 && Pri[signStack[sTop]] >= Pri[sign] && signStack[sTop] != L_BRA)
            {
                op = PopS();
                top = PopN();
                bottom = PopN();
                n = Compute(top, bottom, op);
                PushN(n);
            }
            PushS(sign);
        }
    }
}

enum OPERATOR PopS()
{
    return signStack[sTop--];
}

float PopN()
{
    //! printf("%d", nTop);这招用来快速检查程序是否越界
    //? 有时候即使越界了,但不明显, 程序也不会报错
    return numStack[nTop--];
}

void PushS(enum OPERATOR s)
{
    signStack[++sTop] = s;
}

void PushN(float num)
{
    numStack[++nTop] = num;
}