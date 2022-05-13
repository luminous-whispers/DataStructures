#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define ELEMENTTYPE int
#ifndef _TREE_H
#define _TREE_H
/* |left_h - right_h|<=1 */
    struct GATE;
    typedef struct GATE *POSITION_;
    typedef struct GATE *AVL_TREE_;

    static int Height(POSITION_ p);
    int Max(int a, int b);
    static POSITION_ SingleRotateLeft(AVL_TREE_ t);
    static POSITION_ DoubleRotateLeft(AVL_TREE_ t);
    static POSITION_ SingleRotateRight(AVL_TREE_ t);
    static POSITION_ DoubleRotateRight(AVL_TREE_ t);

    AVL_TREE_ MakeEmpty(AVL_TREE_ T);
    POSITION_ Find(ELEMENTTYPE, AVL_TREE_ T);
    POSITION_ FindMin(AVL_TREE_ T);
    POSITION_ FindMax(AVL_TREE_ T);
    AVL_TREE_ Insert(ELEMENTTYPE, AVL_TREE_ T);
    AVL_TREE_ Delete(ELEMENTTYPE, AVL_TREE_ T);
    ELEMENTTYPE Retrieve(POSITION_ P);

    struct GATE{
        ELEMENTTYPE value;
        AVL_TREE_ left;
        AVL_TREE_ right;
        int height;
        int deleted;
    };
#endif
/*height of empty tree is -1*/
static int 
Height(POSITION_ p)
{
    if (p == NULL)
        return -1;
    else 
        return p->height;
}

/*do nothing while x existed already*/
AVL_TREE_
Insert(ELEMENTTYPE x, AVL_TREE_ t)
{
    if (t == NULL)
    {
        /*create and return a one-node tree*/
        t= (AVL_TREE_)malloc(sizeof(struct GATE));
        if (t == NULL)
            return NULL;//"out of space"
        else
        {
            t->value = x;
            t->height = 0;
            t->left= t->right = NULL;
        }
    }
    else
    if (x < t->value)
    {
        t->left = Insert(x, t->left);
        if (Height(t->left) - Height(t->right) == 2 || Height(t->left) - Height(t->right) == -2)
        {
            if (x < t->left->value)
                t = SingleRotateLeft(t);
            else //not equal
                t = DoubleRotateLeft(t);
        }
    }
    else
    if (x > t->value)
    {
        t->right = Insert(x, t->right);
        if (Height(t->left) - Height(t->right) == 2 || Height(t->left) - Height(t->right) == -2)
        {
            if (x > t->right->value)
                t = SingleRotateRight(t);
            else //not equal
                t = DoubleRotateRight(t);
        }
    }

    t->height = 
        Max(Height(t->left), Height(t->right)) + 1;
    return t;
}

/*the func can be called only if t has a left child*/
/*perform a retate between a node (k1) and its left child*/
/*update heights, then return new root*/
static POSITION_ 
SingleRotateLeft(POSITION_ k2)
{
    POSITION_ k1;//k1's past child
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
    k1->height = Max(Height(k1->left), k2->height) + 1;
    
    return k1;//new root
}

static POSITION_ 
SingleRotateRight(POSITION_ k2)
{
    POSITION_ k1;//k1's past child
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = Max(Height(k2->left), Height(k2->right)) + 1;
    k1->height = Max(Height(k1->right), k2->height) + 1;
    
    return k1;//new root
}

/*The func can be called only if k3 has a left-
    child(k1) and k3's left child has a right child(k2). */
/*Do the left-right double rotation. */
/*Update heights , then return new root. */
static POSITION_
DoubleRotateLeft(POSITION_ k3)
{
    /*rotate between k1 and k2*/
    k3->left = 
        SingleRotateRight(k3->left);
    
    /*rotate between k3 and k2*/
    return SingleRotateLeft(k3);
}

/*Only if k3 has a right child(k1)
And k1 has a right child(k2)*/
/*left-right double bottom-up rotation*/
static POSITION_
DoubleRotateRight(POSITION_ k3)
{
    /*rotate between k1 and k2*/
    k3->right = 
        SingleRotateLeft(k3->right);
    
    /*rotate between k3 and k2*/
    return SingleRotateRight(k3);
}
int main()
{
    
    return 0;
}
#define ElementType int
#ifndef _List_H 

    struct NODE;
    typedef struct NODE *PTR_TO_NODE;
    typedef PTR_TO_NODE LIST_;
    typedef PTR_TO_NODE POSITION_;
    struct NODE{
        ElementType value;
        POSITION_ p;
    };

    LIST_ MakeEmpty( LIST_ L );
    int IsEmpty( LIST_ L ); 
    int IsLast( POSITION_ P, LIST_ L);

    POSITION_ Find( ElementType X, LIST_ L );
    POSITION_ FindPrevious( ElementType X, LIST_ L);
    void Delete( ElementType X, LIST_ L);
    void Insert( ElementType X, LIST_ L, POSITION_ P);
    
    void DeleteList( LIST_ L );
    POSITION_ Header( LIST_ L );
    POSITION_ First( LIST_ L);
    POSITION_ Advance(POSITION_ P);
    ElementType Retrieve( POSITION_ P);

#endif
#define ElementType int
struct NODE;
typedef struct NODE *PTR_TO_NODE;
typedef PTR_TO_NODE LIST_;
typedef PTR_TO_NODE POSITION_;
struct NODE{
    ElementType value;
    POSITION_ p;
};

LIST_ InitList();
void DeleteList( LIST_ L );
#define ElementType int
#define STK_SIZE 100
#ifndef _STACK_H_
#define _STACK_H_

    struct S_NODE{
        ElementType value;
    }stack[STK_SIZE];
    int sTop = -1;
    struct S_NODE StackPop(){
        if (sTop == -1)
        {
            printf("error! out of space with index -1");
        }
        return stack[sTop--];
    }
    void StackPush(struct S_NODE tmp){
        if (sTop == STK_SIZE)
        {
            printf("error! out of space with overflow");
        }
        stack[++sTop].value = tmp.value;
        return;
    }

#endif  //_STACK_H_
#define ElementType int
#define Q_SIZE 100
#ifndef _QUEUE_H_
#define _QUEUE_H_

    struct Q_NODE{
        ElementType value;
    }queue[Q_SIZE];
    int rear = Q_SIZE;//同时处理循环情况和为空情况
    int front = Q_SIZE;
    int count = 0;//记队元素总数

    struct Q_NODE QueuePop(){
        if (count-1 <0)
        {
            printf("error! queue already empty");
            exit(1);
        }
        else
            count--;
        front %= Q_SIZE;//给上一次擦屁股
        return queue[front++];
    }
    void QueuePush(struct Q_NODE tmp){
        if (count+1 > Q_SIZE)
        {
            printf("error! overflow the queue");
            return ;
        }
        count++;
        rear++;
        rear %= Q_SIZE;
        queue[rear].value = tmp.value;
        return;
    }

#endif  //_QUEUE_H_
#define ELEMENTTYPE int
#ifndef _TREE_H
#define _TREE_H
    struct NODE;
    typedef struct NODE *POSITION_;
    typedef struct NODE *TREE_;

    TREE_ MakeEmpty(TREE_ T);
    POSITION_ Find(ELEMENTTYPE, TREE_ T);
    POSITION_ FindMin(TREE_ T);
    POSITION_ FindMax(TREE_ T);
    TREE_ Insert(ELEMENTTYPE, TREE_ T);
    TREE_ Delete(ELEMENTTYPE, TREE_ T);
    ELEMENTTYPE Retrieve(POSITION_ P);

    struct NODE{
        ELEMENTTYPE value;
        TREE_ left;
        TREE_ right;
    };
#endif#define ELEMENTTYPE int
#ifndef _TREE_H
#define _TREE_H
    struct NODE;
    typedef struct NODE *POSITION_;
    typedef struct NODE *TREE_;

    TREE_ MakeEmpty(TREE_ T);
    POSITION_ Find(ELEMENTTYPE, TREE_ T);
    POSITION_ FindMin(TREE_ T);
    POSITION_ FindMax(TREE_ T);
    TREE_ Insert(ELEMENTTYPE, TREE_ T);
    TREE_ Delete(ELEMENTTYPE, TREE_ T);
    ELEMENTTYPE Retrieve(POSITION_ P);

    struct NODE{
        ELEMENTTYPE value;
        TREE_ left;
        TREE_ right;
    };
#endif
TREE_ MakeEmpty(TREE_ T){
    if (T != NULL)
    {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

POSITION_ Find(ELEMENTTYPE x, TREE_ t)
{
    if (t == NULL)//empty tree!
        return NULL;
    else if (t->value < x)
        return Find(x, t->left);
    else if (t->value > x)
        return Find(x, t->right);
    else
        return t;
}

POSITION_ FindMin(TREE_ t)
{
    if (t == NULL)  
        return NULL;//error
    else if (t->left == NULL) 
        return t;
    else  
        return FindMin(t->left);
}

POSITION_ FindMax(TREE_ t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return FindMax(t->right);
}

/*insert element, but not dispose repeated item*/
TREE_ Insert(ELEMENTTYPE x, TREE_ t)
{
    if (t == NULL)
    {
        /*create and return a one-node tree*/
        t= (TREE_)malloc(sizeof(struct NODE));
        if (t == NULL)
            printf("error , unable to malloc a memory");
        else
        {
            t->value = x;
            t->left = t->right = NULL;
        }
    }
    else
    if (x < t->value)
        t->left = Insert(x, t->left);
    else
    if (x > t->value)
        t->right = Insert(x, t->right);
    /*else x is in the tree already; we'll do nothing*/
    return t;
}

//used in Delete to implement alternate substitution
int flag = 0;
/*find the least element in the right_tree( or the biggest in left) 
to replace the deleted item.
when possibly use the deleted item again, use the lazy delete*/
TREE_ Delete(ELEMENTTYPE x, TREE_ t)
{
    POSITION_ tmp;
    if (t == NULL)
        return NULL;//not found
    else
    if (x < t->value)
        t->left = Delete(x, t->left);
    else
    if (x > t->value)
        t->right = Delete(x, t->right);
    else
    if (t->left && t->right)//&&x==t->value; with two sons
    {
        /*replace in balance*/
        flag %= 2;
        if (flag)
        {
            tmp= FindMin(t->right);
            t->right= Delete(tmp->value, t->right);
        }
        else
        {
            tmp= FindMax(t->left);
            t->left= Delete(tmp->value, t->left); 
        }
        t->value = tmp->value;
    }
    else //one or zero son
    {
        tmp = t;
        if (t->left == NULL)
            t= t->right;
        else
        if (t->right == NULL)
            t= t->left;
        free(tmp);
    }
    return t;//return the new son
}
int Height(TREE_ t)
{
    int lh, rh;
    if (t == NULL)
        return -1;
    else
    {
        lh = Height(t->left);
        rh = Height(t->right);
        return 1 + (rh>lh?rh:lh);
    }
}

//树的遍历
void LevelOrder(TREE_ t)
{
    int h = Height(t), i, j, lvSize = 1;
    POSITION_ *current = &t;
    POSITION_ *p;
    for (i=0; i<h; i++)
    {
        for (j=0; j<lvSize; j++)
        {
            //*(current+j)->
            //do something in curr lv
        }
        lvSize *= 2;//binary tree only, for next level
        p = (POSITION_ *)malloc(lvSize * sizeof(POSITION_));
        for (j=0; j<lvSize; j++)
        {
            if (j%2 == 0)
            {
                if ((*current+j/2)->left != NULL)
                    *(p+j) = (*current+j/2)->left;
                else
                    memset(j+p, 0, sizeof(POSITION_));
            }
            else
            {
                if ((*current+j/2)->right != NULL)
                    *(p+j) = (*current+j/2)->right;
                else
                    memset(j+p, 0, sizeof(POSITION_));
            }
        }
        free(current);
        current = p;
    }
    return;
}

void PreOrder(TREE_ t)
{
    if (t!=NULL)
    {
        //current node, do sth
        PreOrder(t->left);
        PreOrder(t->right);
    }
}

void PostOrder(TREE_ t)
{
    if (t!=NULL)
    {
        PostOrder(t->left);
        PostOrder(t->right);
        //current node, do sth
    }
}

void InOrder(TREE_ t)
{
    if (t!=NULL)
    {
        InOrder(t->left);
        //current node, do sth
        InOrder(t->right);
    }
}
struct NODE *p;
p = (struct NODE *)malloc(sizeof(struct NODE) * n);
//input
qsort(p, n, sizeof(struct NODE), Cmp);
/*warning: instable, only available for continuous memory*/
int RiseCmp(const void *a, const void *b)
{
    return ((*(struct NODE *)a).value<(*(struct NODE *)a).value)?-1:1;
}


struct NODE *p;
int n;//数据块量
p = (struct NODE *)malloc(sizeof(struct NODE) * n);
//input
qsort(p, n, sizeof(struct NODE), Cmp);
/*warning: instable, only available for continuous memory*/
int RiseCmp(const void *a, const void *b)
{
    return ((*(struct NODE *)a).value<(*(struct NODE *)a).value)?-1:1;
}


struct NODE *p;
int n;//数据块量
p = (struct NODE *)malloc(sizeof(struct NODE) * n);
//input
qsort(p, n, sizeof(struct NODE), Cmp);
