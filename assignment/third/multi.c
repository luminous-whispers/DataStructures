/*
第三次作业第三题 多项式相乘
寒假做过相似的例程, 是考察链表的经典题型
重点: 链表常规例程, 多项式结构的构造, 加法和乘法的配合
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#ifndef _Polynomial_H
#define _Polynomial_H_

    struct Node;
    typedef struct Node Cell;
    typedef struct Node * Poly_;
    typedef struct Node * Position_;

    Poly_ addPoly(Poly_ f1_, Poly_ f2_);
    Poly_ multiPoly(Poly_ f1, Poly_ f2_);

    Position_ findExp(int Exponent, Position_ P_);//从P_位置沿链表向下寻找, 需要回检null
    void deletePoly(Poly_ f_);
    void copyList(Position_ src_, Position_ restr_);//将src起的链表拷贝到restr位置后, 注意是拷贝内容不是交换指针
    Poly_ initialPoly();
    void output(Poly_ f_);
    int isNum(char *);//是数字返回1, 否则为0
    Position_ insertAfter(int Coefficient, int Exponent, Position_ P_, Poly_ f_); 

#endif

struct Node{
    int Coefficient;
    int Exponent;
    Position_ next_;
};

int main()
{
    Poly_ fb_, fa_, Result_;
    char In[50];
    fa_ = initialPoly();//input, 注意含头指针
    fb_ = initialPoly();//!输入错误

    Result_ = multiPoly(fa_, fb_);
    output(Result_);

    deletePoly(fb_);
    deletePoly(fa_);
    deletePoly(Result_);
    return 0;

}


Poly_ initialPoly()
{
    Poly_ Last_, L_ = (Poly_)malloc(sizeof(Cell));//注意强制类型转化需要"别名"也一致
    char tmp[50];
    int i, k, len = 1, type = 0;//type0代表是coff, 1代表是exp
    double num = 0, exp, coff;

    L_->next_ = NULL;
    Last_ = L_;
    gets(tmp);//老师推荐的方法是scanf("%d%d%c"), 判断何时c为\n即可判断输入的换行.
    for (i = 0; i < strlen(tmp); i+=len)
    {
        if (isNum(&tmp[i]))
        {
            while(isNum(&tmp[i + len]))
                len++;
            for (k = 0; k < len; k++)
                num += pow(10.0, len - k - 1.0) * (tmp[i + k] - '0');
            if (type)
                exp = num;
            else
                coff = num;
            type = (++type)%2;
            if(!type)
                Last_ = insertAfter((int)coff, (int)exp, Last_, L_);
        }
        else
            len = 1;
        
        num = 0;
    }
    return L_;
}


int isNum(char *p)
{
    if(*p >= '0' && *p <= '9')
        return 1;
    else
        return 0;
}

Position_ insertAfter(int Coefficient, int Exponent, Position_ P_, Poly_ f_)
{
    Position_ Tmp_;
    Tmp_ = (Position_)malloc(sizeof(Cell));
    P_->next_ = Tmp_;

    Tmp_->next_ = NULL;//!
    Tmp_->Coefficient = Coefficient;
    Tmp_->Exponent = Exponent;

    return Tmp_;
}

Position_ findExp(int Exponent, Position_ P_)
{
    while (P_ != NULL)
    {
        if (P_->Exponent == Exponent)
            return P_;
        else    
            P_ = P_->next_;
    }
    return P_;
}


Poly_ addPoly(Poly_ fa_, Poly_ fb_)//输入和存储顺序是从高到底
{
    Poly_ L_ = (Poly_)malloc(sizeof(Cell));//开辟头指针
    //!注意, 要检验传入的指针是否是空
    Position_ Tmpa_, Tmpb_, TmpL_ = L_;
    if (fa_ != NULL && fb_ != NULL)
    {
        Tmpa_ = fa_->next_;
        Tmpb_ = fb_->next_;
        while (Tmpa_ != NULL && Tmpb_ != NULL)
            if (Tmpa_->Exponent == Tmpb_->Exponent)
            {
                TmpL_ = insertAfter(Tmpa_->Coefficient + Tmpb_->Coefficient
                    , Tmpa_->Exponent, TmpL_, L_);//*隐含推进指针
                Tmpa_ = Tmpa_->next_;
                Tmpb_ = Tmpb_->next_;
            }
            else if (Tmpa_->Exponent > Tmpb_->Exponent)
            {
                TmpL_ = insertAfter(Tmpa_->Coefficient, Tmpa_->Exponent, TmpL_, L_);
                Tmpa_ = Tmpa_->next_;
            }
            else
            {
                TmpL_ = insertAfter(Tmpb_->Coefficient, Tmpb_->Exponent, TmpL_, L_);
                Tmpb_ = Tmpb_->next_;
            }

            if (Tmpa_ == NULL)
                copyList(Tmpb_, TmpL_);
            else
                copyList(Tmpa_, TmpL_);
    }
    else
    {
        if (fa_ == NULL)
            copyList(fb_->next_, TmpL_);
        else
            copyList(fa_->next_, TmpL_);
    }
    /*直接交换尾部的部分虽然方便, 但是会对内存的释放产生极大的混乱.
        代价是释放和申请内存操作变得更加频繁.
    if (Tmpa_ == NULL)
        TmpL_->next_ = Tmpb_;
    else
        TmpL_->next_ = Tmpa_;
    */
    return L_;
}

Poly_ multiPoly(Poly_ fa_, Poly_ fb_)
{
    Poly_ Mult_ = NULL, Tmp_;
    Position_ a = fa_->next_, b= fb_->next_, P_, Delete_;

    while (a != NULL)
    {
        Tmp_ = (Poly_)malloc(sizeof(Cell));
        memset(Tmp_, 0, sizeof(Cell));
        P_ = Tmp_;
        while (b != NULL)
        {
            P_ = insertAfter(a->Coefficient * b->Coefficient, 
                a->Exponent + b->Exponent, P_, Tmp_);//隐含推进p指针
            b = b->next_;
        }
        Delete_ = Mult_;
        Mult_ = addPoly(Mult_, Tmp_);//注意传出的全新表
        //! 这里有问题, 头链表出现了问题
        deletePoly(Delete_);
        deletePoly(Tmp_);
        
        b = fb_->next_;
        a = a->next_;
    }

    return Mult_;
}

void deletePoly(Poly_ f_)
{
    Position_ P_ = f_;
    if (f_ == NULL)
        return;
    else
        P_ = f_->next_;
    while (P_ != NULL)
    {
        free(f_);
        f_ = P_;
        P_ = P_->next_;
    }
    free(f_);
}

//在链表后插入新的复制元
void copyList(Position_ src_, Position_ restr_)
{
    Position_ Psrc_ = src_, Pre_ = restr_;
    while (Psrc_ != NULL)
    {
        Pre_ = insertAfter(Psrc_->Coefficient, Psrc_->Exponent
            , Pre_, restr_ );
        Psrc_ = Psrc_->next_;
    }
}

void output(Poly_ f_)
{
    Position_ P_ = f_->next_;
    while (P_ != NULL)
    {
        printf("%d %d ", P_->Coefficient, P_->Exponent);
        P_ = P_->next_;
    }
}
