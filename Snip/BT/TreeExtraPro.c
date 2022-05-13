#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
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

/*empty tree has -1 height*/
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

