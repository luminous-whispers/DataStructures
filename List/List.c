//本文档用以配合ListArgument.h给出链表的样例
#include"ListArgument.h"



struct Node
{
    ElementType Element;//这是表元
    Position Next;//这是指向下一个元素的指针
};



//return true if L is empty
int isEmpty( List L )
{
    return L->Next == NULL;//判断语句
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int
IsLast(Position P, List L)
{
    return P->Next == NULL;
}

/* return Position of X in L; 
NULL if not found */
Position
Find( ElementType X , List L)
{
    Position P;

    P= L-> Next;//本类型链表中，表头没有实际意义仅代表了代码的开始，所以查找内容需要从第二个开始;

    //第一条件是找不到就退出
    //第二条件是找到了也跳出
    while( P != NULL && P->Element != X )//注意第一个条件起到了短路作用，防止了P=NULL时错误的指针使用（NULL->X)
        P= P->Next; 
    return P;
}//注意递归地编写find历程是一个非常糟糕的想法


/* If X is not found, then Next field returned */
/* Position is NULL */
/* Assemes a header  */
Position
FindPrevious( ElementType X, List L)
{
    Position P;

    P= L;
    while( P->Next != NULL && P->Next->Element != X )//检测的是才一个元，非P本元( Find例程中是对P本身查找, 因为其目的不是保留前驱元位置)
        P= P->Next;

    return P;
}//但是，如果找不到，会返回最后一个元位置，要注意


/* Delete first occurrence of X from a List */
/* Assume use of a header node */
void
Delete(ElementType X, List L )
{
    Position P, TmpCell; 

    P= FindPrevious( X, L );

    if( !IsLast( P, L ) )//如果X找不到，就什么也不干
    {
        TmpCell= P->Next;
        P->Next= TmpCell->Next;//把前驱元的指针改到指向X元的下一个表元
        free( TmpCell );//然后释放X所在内存即可
    }
}

/* Insert after legal position P */
/* Header implementation assumes */
/* Parameter L is unesed in this implementation 标识作用 */
void
Insert( ElementType X, List L, Position P )
{
    Position TmpCell;

    //声明一个指针并不创建该结构,而只是给出足够的空间容纳结构可能会使用的地址
    //创建尚未被声明过的记录的唯一方法是使用malloc库函数
    /* 这时候TmpCell仅仅是个指针而已，虽然它有类型，但是实际上现在并没有新的内存地址被创建为struct类型
    这个类型声明仅仅是方便编译，但是容易造成人的误解。 */
    TmpCell= malloc( sizeof( struct Node ) );
    if( TmpCell == NULL )//判断是否开辟成功
        printf( "Out of space!!! " );
    
    TmpCell->Element= X;
    TmpCell->Next= P->Next;//插入一表元至P位置后
    P->Next= TmpCell;
}

void
DeleteList( List L )
{
    Position P, Tmp;

    P= L->Next;
    L->Next= NULL;//切断表头
    while( P!= NULL)
    {
        Tmp= P->Next;
        free( P );//注意free执行后, P就NULL了. 那么此时P->Next就完全没有意义(报错), 所以需要提前储存Next指针.
        //释放的是P指向的内存空间，不是P这个指针
        P=Tmp;
    }
}