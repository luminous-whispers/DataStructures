#include"Polynomial.h"

struct Node
{
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};

//kernel
/* void zeroPolynomial( Polynomial Poly )
{
    Position P;
    P= Poly->Next;
    while( P != NULL )
    {
        P->Coefficient= 0;
        P->Exponent= 0;
        P= P->Next;
    }
} */

void addPolynomial( const Polynomial Poly1, 
    const Polynomial Poly2, Polynomial PolySum )//注意这三形参都是假想的多项式链表，需要外部定义
{
    Position P1, P2, P;
    P1= Poly1->Next;
    P2= Poly2->Next;
    P= PolySum;
    if( !isEmpty( PolySum ) ) 
    {
        printf(" error, PolySum isn't empty !!");
        return;
    }

    while( P1 != NULL && P2 != NULL )
        if( P1->Exponent == P2->Exponent )
        {
            insertAfter( P1->Coefficient + P2->Coefficient, P1->Exponent, P, PolySum);      
            P1= P1->Next;
            P2= P2->Next;
            P= P->Next;
        }
        else if( P1->Exponent > P2->Exponent )
        {
            insertAfter( P2->Coefficient, P2->Exponent, P, PolySum);
            P= P->Next;
            P2= P2->Next;
        }
        else
        {
            insertAfter( P1->Coefficient, P1->Exponent, P, PolySum);
            P= P->Next;
            P1= P1->Next;            
        }

    if( P1 == NULL)
        P->Next= P2;
    else
        P->Next= P1;

    PolySum= P;

}

void multPolynomial( const Polynomial Poly1, 
    const Polynomial Poly2, Polynomial PolyProd )
{

    Position P1= Poly1->Next, P2= Poly2->Next, P, TmpP;
    Polynomial Tmp1, Tmp2;

        if( !isEmpty( PolyProd ) ) //检验乘法结果储存链表是否为空
    {
        printf(" error, PolyProd isn't empty !!");
        return;
    }
    Tmp1= malloc( sizeof( struct Node ) );
    Tmp2= malloc( sizeof( struct Node ) );
    Tmp2->Next= NULL;
    Tmp1->Next= NULL;

    P= Tmp1;

    while( P1 != NULL )
    {
        while( P2 != NULL)
        {
            //相乘,本轮乘的结果储存再Tmp1
            insertAfter( P1->Coefficient * P2->Coefficient, 
                P1->Exponent + P2->Exponent, P, Tmp1);
            P= P->Next;
            P2= P2->Next;
        }
        PolyProd->Next= NULL;
        addPolynomial( Tmp1, Tmp2, PolyProd );
        Tmp1->Next= NULL;//不要轻易用删除链表例程，如果两个表头指向了同一个表呢？多项式加法实现中其实就是改变了指针的指向
        //但是这样的代价是部分malloc开辟的空间就被丢弃了，而没有被释放。 大型程序内存可能会出现问题，
        Tmp2->Next= PolyProd->Next;//表头互换， 将和赋值给Tmp2，并清空PolyProd方便后续叠加
        

        P2= Poly2->Next;
        P1= P1->Next;
    }
    free( Tmp1 );
    free( Tmp2 );
}





//common

int isEmpty( Polynomial L )
{
    return L->Next == NULL;
}

int isLast( Position P, Polynomial L){
    return P->Next == NULL;
}

Position findExponent( int ToFindExponent, Polynomial L){
    Position P;
    P= L->Next;//表头无用
    
    while( P != NULL && P->Exponent != ToFindExponent)
        P= P->Next;
    
    return P;
}

Position findPrevious( int ToFindExponent, Polynomial L){
    Position P;
    P= L;

    while( P->Next != NULL && P->Next->Exponent != ToFindExponent)
        P= P->Next;
    
    return P;
}

void insertAfter( int Coefficient, int Exponent, Position P, Polynomial L){
    Position Tmp;
    Tmp= ( Position )malloc( sizeof( struct Node ) );
    if( Tmp == NULL )
        printf(" error in insert, fail to malloc ");
    Tmp->Next= P->Next;
    P->Next= Tmp;

    Tmp->Coefficient= Coefficient;
    Tmp->Exponent= Exponent;
}

void delete( int Exponent, Polynomial L ){
    Position Tmp, P;
    P= findPrevious( Exponent, L );
    
    if( !isLast( P, L ) )
    {
        Tmp= P->Next;
        P->Next= Tmp->Next;
        free( Tmp );
    }
}

/* 不要轻易使用删除链表，谨防不同含义的多个指针共用了相同的内容 */
void deletePolynomial( Polynomial L )//留了个表头
{
    Position P, Tmp;
    P= L->Next;
    L->Next= NULL;
    while( P != NULL )
    {
        Tmp= P->Next;
        free( P );
        P=Tmp;
    }
}

void 
input( Polynomial L){
    int TmpCoeff= 0, TmpExp= 0;
    Position P= L;
    if( !isEmpty( L ) )
        printf(" error, wrong input!! ");

    while( ~ scanf("%d%d", &TmpCoeff, &TmpExp ))
    {
        insertAfter( TmpCoeff, TmpExp, P, L);
        P= P->Next;
    }
}

void
output( Polynomial L)
{
    Position P= L->Next;
    while( P != NULL)
    {
        printf("%d %d\n", P->Coefficient, P->Exponent);
        P= P->Next;
    }
}

/* 很容易产生的印象是，Polynomial P声明一个指针就是创造了一个链\表
，也就是创造了一个表头. 但这是因为混淆了typedef定义Polynomial的初衷
单纯声明一个指针，但是这个指针并没有初始化是愚蠢的做法，此时P除了类型外，并没有任何实际的意义
表头并不能凭空出现，需要malloc开辟一块一致（ 和insert例程思路一致） */
Polynomial createPolynomial( )
{
    Polynomial P;
    P= ( Polynomial )malloc( sizeof( struct Node ) );
    if( P == NULL )
        printf(" error in insert, fail to malloc");
    P->Next= NULL;//要注意这个隐藏的野指针

    P->Coefficient= -1;//这个以防万一
    P->Exponent= -1;

    return P;
}


