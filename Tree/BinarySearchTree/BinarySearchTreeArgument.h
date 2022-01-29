/* 二叉查找树：
    结点右侧全部节点元素都大于该结点, 结点左侧所有元素都小于该结点, 并且每个结点最多只能有两个分叉
    二叉查找树平均深度为 O( log N ) */

#include<stdio.h>
#include<stdlib.h>

typedef int ELEMENTTYPE;

#ifndef _Tree_H
#define _Tree_H

    struct TreeNode;
    typedef struct TreeNode * POSITION_;
    typedef struct TreeNode * SEARCHTREE_;

    SEARCHTREE_ makeEmpty( SEARCHTREE_ T );
    POSITION_ findElement( ELEMENTTYPE X, SEARCHTREE_ T );
    POSITION_ findMin( SEARCHTREE_ T );
    POSITION_ findMax( SEARCHTREE_ T );
    SEARCHTREE_ insertElement( ELEMENTTYPE X, SEARCHTREE_ T );
    SEARCHTREE_ deleteElement( ELEMENTTYPE X, SEARCHTREE_ T );
    ELEMENTTYPE retrieve( POSITION_ P);

#endif /*  _Tree_H */
