#include"BinarySearchTreeArgument.h"

struct TreeNode
{
    ELEMENTTYPE Element;
    SEARCHTREE_ Left_ ;
    SEARCHTREE_ Right_ ;
};

/* 为了递归的一致性，选择初始化为null而不是单节点 */
SEARCHTREE_ 
makeEmpty( SEARCHTREE_ T){

    if( T != NULL )
    {
        makeEmpty( T->Left_ );
        makeEmpty( T->Right_ );
        free( T );
    }
    return NULL; 
}

POSITION_
findElement( ELEMENTTYPE X, SEARCHTREE_ T){
    if( T == NULL ){
        printf( "error find, empty tree " );
        return NULL;
    }
    else if( T->Element < X )
        findElement( X, T->Right_ );
    else if( T->Element > X)
        findElement( X, T->Left_ );
    else
        return T;
}

/* 最左侧的结点必定是最小的 
    递归实现 */
POSITION_
findMin( SEARCHTREE_ T){
    if( T == NULL ){
        printf( "error findMin, empty tree!");
        return NULL;
    }
    else if( T->Left_ == NULL )//基准情形
        return T;
    else   
        return FindMin( T->Left_ );
}

/* 非递归实现 findMax
注意T自身赋值或赋值操作没有问题， 但是不要改变T指向的内容比如给T->right赋值就是根本错误的 */
POSITION_
findMax( SEARCHTREE_ T){
    if( T != NULL )
        while( T->Right_ != NULL )
            T= T->Right_;
    return T;
}

/* 插入
对于重复元，本实现方法遇到重复元不会进行任何处理
但另一种方法是在树结点中增加重复信息，这样的好处是删除也更加方便了。 如果重复的关键字是更大结构的一部分，那么就可以将具有i选哪个如关键字的所有结构保留在一个辅助数据结构中 */
/* 插入原理：
不断向下寻找空位， 直至寻找到合适的位置 */
SEARCHTREE_
insertElement( ELEMENTTYPE X, SEARCHTREE_ T){
    if( T == NULL )
    {
        /* create and return a one-node tree */
        T= malloc( sizeof( struct TreeNode ) );
        if( T == NULL )
            printf(" error insert a new node, out of space \n");
        else
        {
            T->Element= X;
            T->Left_= T->Right_= NULL;
        }
    }
    else 
    if( X < T->Element )
        T->Left_= insertElement( X, T->Left_ );
    else
    if( X > T->Element )
        T->Right_= insertElement( X, T->Right_ );
    /* Else X is in the tree already; we'll do noting */

    return T;//注意T在例程中并没有被修改，认识该子树的根。返回树的根，是为了方便递归
}

/* 删除操作：（树最困难例程）
考虑两种情况：
    1. 要删除的结点只有一个分支。那么只需要调整该分支的父节点绕过该指针即可
    2. 要删除的节点有两个分支。 直接把这个节点释放了不大现实，因为他的子节点不一定能够替代它。什么能够完美替代它的位置呢？只有右子树的最小值（或左子树的最小值）
        因此， 需要先找到右子树的最小值进行替换，又因为右子树的最小值一定只有一个右节点，所以利用第一种情况删掉即可。
这里仍然使用递归的办法，因为是递归，所以一次只能处理树的一层。这样每个节点只需要关注他的两个子节点就可以，并且需要保证函数回调值也是子树。
 */
SEARCHTREE_
deleteElement( ELEMENTTYPE X, SEARCHTREE_ T ){
    POSITION_ TmpCell;
    if( T == NULL )
        printf( " Element not found, delete error " );
    else
    if( X < T->Element )
        T->Left_= deleteElement( X, T->Left_ );//postorder后序遍历， 浅层等待深层
    else
    if( X > T->Element )
        T->Right_= deleteElement( X, T->Right_ );
    else
    if( T->Left_ && T->Right_ )/* 有两个节点  */
    {
        /* replace with smallest in right subtree */
        TmpCell= findMin( T->Right_ );//记录最小值位置
        /* 在这颗右子树上因为有findmin和deleteelement操作，所以相当于进行了两遍重复的查找操作。这其实是可以合并的，这里是为了简洁性，  */
        T->Element= TmpCell->Element;
        T->Right_= deleteElement( T->Element, T->Right_ );//删除最小值， 并返回更新后的右子树
    }
    else /* One or zero children */
    {
        TmpCell= T; //记录T的值， 以便后续将T此时指向的无用节点释放掉。注意，不能先释放，否则就出现了NULL指针
        if( T->Left_ == NULL ) /* 同时处理了没有分支的情况 */
            T= T->Right_;
        else if( T->Right_ == NULL )
            T= T->Left_;
        free( TmpCell );
    }

    return T;
}
/* 删除操作中， 我们既可以选择右子树最小元素作为该结点的替代值，也可以选择左子树最大元素作为该结点的替代值。
但是这样有一个问题，就是当数据很大时，会导致树的不平衡，左边子树会明显更加庞大。 解决办法可以是随机交替使用上述两种方案。
当然，如果直接使用平衡树（ 如avl ）更好，因为可以顺便解决数据输入时按序输入的不平衡问题 */
/* 还有另一种删除思路， 就是不删除节点，只将出现等 频率数减一（做个记号）。 特别是有重复关键字时这种方案很好用
如果树中的实际简单树和“被删除”的节点数相同，那么树的深度也预计只上升一个小的阐述。 因此懒惰删除时间开销极小，且如果重新插入，就避免分配一个新单元的开销了。 */