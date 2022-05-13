#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

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

