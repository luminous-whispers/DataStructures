#include<CursorListArgument.h>

struct Node
{
    _ELEMENT_TYPE_ Element;
    POSITION Next;
};

struct Node CursorSpace[  _SPACE_SIZE_ ];

//! 链表的重要特性是: 1.数据存储在结构体中,并通过指针指向下一单元 2.结构体可以调用malloc从系统全局内存中得到,调用free释放
//! 下面进行2特性的游标实现, Kernel
static POSITION
cursorAlloc( void )
{
    POSITION P;

    P = CursorSpace[ 0 ].Next;
    CursorSpace[ 0 ].Next = CursorSpace[ P ].Next;
//注意这里漏洞是并没有判断是否溢出提前开辟的空间
//整个过程中CursorSpace[0]是没有动的,浪费了一个空间

    return P;
}


static void//static 限制函数作用域,作为静态函数只作用于本文件
cursorFree( POSITION P )
{
    CursorSpace[ P ].Next = CursorSpace[ 0 ].Next;
    CursorSpace[ 0 ].Next = P;
}
//*核心是,将创建的freelist表当作栈来处理,之储存尚未使用的结构体.
//*所有结构体都是提前准备好的,但存在两种状态.


//其他部分与普通列表类似
// return true if L is empty
int
isEmpty( LIST L )
{
    return CursorSpace[ L ].Next == 0;
}


void 
initializeCursorSpace( void )
{
    int i= 0;

    while (i < _SPACE_SIZE_)
        CursorSpace[ i ].Next= ++i;

    CursorSpace[ _SPACE_SIZE_ ].Next= 0;
}


//return true if P is the last position in list L
//Parameter L is unused in this implementation
int 
isLast( POSITION P, LIST L )
{
    return CursorSpace[ P ].Next == 0;
}


//return POSITION of X in L; 0 if not found
//Uses a header node

POSITION
find( _ELEMENT_TYPE_ X, LIST L )
{
    POSITION P;

    P= CursorSpace[ L ].Next;
    while( P && CursorSpace[ P ].Element != X )
        P = CursorSpace[ P ].Next;
    
    return P;
}


POSITION
findPrevious( _ELEMENT_TYPE_ X, LIST L )
{
    POSITION P= L;

    while( CursorSpace[P].Next && CursorSpace[ CursorSpace[P].Next ].Element != X )
        P = CursorSpace[ P ].Next;
    
    return P;
}


//delete first occurrence of X from a list
//assume use of a header node
void
deleteElement( _ELEMENT_TYPE_ X, LIST L )
{
    POSITION P, TmpCell;

    P= findPrevious( X, L );
    
    if ( !isLast(P, L) ) //assumption of header use
    {   //X is found; delete it 
        TmpCell = CursorSpace[ P ].Next;
        CursorSpace[P].Next= CursorSpace[ TmpCell ].Next;
        cursorFree( TmpCell );
    }
}


//inser after legal position P
//header implementation assumed
//parameter L is unused in this implementation, just to sign it out
void
insert( _ELEMENT_TYPE_ X, LIST L, POSITION P )
{
    POSITION TmpCell;

    TmpCell= cursorAlloc();
    if( TmpCell == 0 )
        printf("out of space!!");
    
    CursorSpace[ TmpCell ].Element= x;
    CursorSpace[ TmpCell ].Next= CursorSpace[ P ].Next;
    CursorSpace[ P ].Next= TmpCell;
}






















