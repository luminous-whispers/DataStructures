#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
/*读入文章程序, 目前仅处理一个文章
读入并识别word
使用avl平衡树*/

#define ELEMENTTYPE_ char*
#ifndef _TREE_H
#define _TREE_H
    struct NODE;
    typedef struct NODE *POSITION_;
    typedef struct NODE *TREE_;
    TREE_ Insert(ELEMENTTYPE_, TREE_ T);

    static int Height(POSITION_ p);
    static POSITION_ SingleRotateLeft(TREE_ t);
    static POSITION_ DoubleRotateLeft(TREE_ t);
    static POSITION_ SingleRotateRight(TREE_ t);
    static POSITION_ DoubleRotateRight(TREE_ t);

    struct NODE{
        ELEMENTTYPE_ value;
        TREE_ left;
        TREE_ right;
        int height;
        int count;
    };
#endif

/*not sign the equal situation*/
int Max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

char * StrConstCpy(char * source, int len);//从源中读取len个字符作为常量
void InOrder(TREE_ t)
{
    if (t!=NULL)
    {
        InOrder(t->left);
        printf("%s %d\n", t->value, t->count);
        InOrder(t->right);
    }
}
void TurnRight(TREE_ t, int num)
{
    if (t!=NULL && num!=0)
    {
        printf("%s ", t->value);
        TurnRight(t->right, --num);
    }
}

int main()
{
    FILE *fp;
    TREE_ t = NULL;
    char str[500], *p, *tmp;
    int len;
    fp = fopen("F:\\notes\\assign\\bonus\\article.txt", "r");
    //fp = fopen("F:\\notes\\assign\\fifth\\two\\article.txt", "r");
    while ( fgets(str, 500, fp) != NULL )
    {
        if (str[0] == '\f')
            break;
        for (p = str; *p != 0; p+=len)
        {   
            for (len=0; isalpha(*(p+len)); len++)
            {
                *(p+len) = tolower(*(p+len));//转换小写
            }
            if (isalpha(*p))
            {
                tmp = StrConstCpy(p, len);
                t = Insert(tmp, t);//always return root;
            }
            else
                len = 1;//p not alpha
        }
    }
    TurnRight(t, 3);
    printf("\n");
    InOrder(t);
    return 0;
}

char * StrConstCpy(char *source, int len)
{
    char *ptr;
    int i;

    ptr = (char *)malloc(len);
    if (ptr == NULL)
    {
      printf("Memory allocation failed!\n");
      exit(0);
    }

    for (i=0; i<len; i++)
        *(ptr+i) = *(source+i);
    *(ptr+i) = 0;
    return ptr;
}




/*height of empty tree is -1*/
static int 
Height(POSITION_ p)
{
    if (p == NULL)
        return -1;
    else 
        return p->height;
}

TREE_
Insert(ELEMENTTYPE_ x, TREE_ t)
{
    if (t == NULL)
    {
        /*create and return a one-node tree*/
        t= (TREE_)malloc(sizeof(struct NODE));
        if (t == NULL)
            return NULL;//"out of space"
        else
        {
            t->value = x;
            t->height = 0;
            t->count = 1;
            t->left= t->right = NULL;
        }
    }
    else
    if (strcmp(x, t->value) < 0)
    {
        t->left = Insert(x, t->left);
        if (Height(t->left) - Height(t->right) == 2 
            || Height(t->left) - Height(t->right) == -2)
        {
            if (strcmp(x, t->left->value) < 0)
                t = SingleRotateLeft(t);
            else //not equal
                t = DoubleRotateLeft(t);
        }
    }
    else
    if (strcmp(x, t->value) > 0)
    {
        t->right = Insert(x, t->right);
        if (Height(t->left) - Height(t->right) == 2 
            || Height(t->left) - Height(t->right) == -2)
        {
            if (strcmp(x, t->right->value) > 0)
                t = SingleRotateRight(t);
            else //not equal
                t = DoubleRotateRight(t);
        }
    }
    else
        t->count++;

    t->height = Max(Height(t->left), Height(t->right)) + 1;
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