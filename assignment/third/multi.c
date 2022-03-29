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
    fa_ = initialPoly();//input
    fb_ = initialPoly();

    Result_ = multiPoly(fa_, fb_);
    output(Result_);

    //由于各链表之间有交叉指向, 所以删除很有问题,需要研究.
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
    double num, exp, coff;

    L_->next_ = NULL;
    Last_ = L_;
    gets(tmp);
    for (i = 0; i < strlen(tmp); i+=len)
    {
        if (isNum(&tmp[i]))
        {
            while(isNUm(&tmp[i + len]))
                len++;

            for (k = 0; k < len; k++)
                num += pow(10.0, len - k - 1.0) * tmp[i + k];

            if (type)
                exp = num;
            else
                coff = num;
            type = (++type)%2;
        }
        else
            len = 1;
        
        if(!type)
            Last_ = insertAfter((int)coff, (int)exp, Last_, L_);
    }
    return L_;
}


int isNUm(char *p)
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
    Position_ Tmpa_ = fa_->next_, Tmpb_ = fb_->next_, TmpL_ = L_;
    while (Tmpa_ != NULL && Tmpb_ != NULL)
        if (Tmpa_->Exponent == Tmpb_->Exponent)
        {
            TmpL_ = insertAfter(Tmpa_->Coefficient + Tmpb_->Coefficient
                , Tmpa_->Exponent, TmpL_, L_);
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
        TmpL_->next_ = Tmpb_;
    else
        TmpL_->next_ = Tmpa_;

    return L_;
}

Poly_ multiPoly(Poly_ f1, Poly_ f2_)
{
    
}