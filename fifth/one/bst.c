#define _CRT_SECURE_NO_WARNINGS
/*第五次作业: 树 第一题
构造二叉查找树, 然后利用层次遍历打印入数组中即可
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<windows.h>

#define ELEMENTTYPE int

struct NODE;
typedef struct NODE * TREE_;
typedef struct NODE * POSITION_;
struct NODE{
    ELEMENTTYPE num;
    int h;
    TREE_ left;
    TREE_ right;
};
int height;
int maxHeight;
POSITION_ Insert(ELEMENTTYPE num, TREE_ t, int h);
void OutputFloor(int height, TREE_ t);

int main()
{
    int n=0, tmp;
    TREE_ t = NULL;
    scanf("%d", &n);
    while (n--)
    {
        height = 1;
        scanf("%d", &tmp);
        t = Insert(tmp, t, height);
        if (height >=maxHeight)
            maxHeight = height;
    }
    OutputFloor(maxHeight, t);
    return 0;
}

POSITION_ Insert(ELEMENTTYPE num, TREE_ t, int h)
{
    if (t == NULL)
    {
        t = (struct NODE *)malloc(sizeof(struct NODE));
        t->h = height;
        t->num = num;
        t->left = t->right = NULL;
    }
    else if (num < t->num)
        t->left = Insert(num, t->left, height++);
    else if (num >= t->num)
        t->right = Insert(num, t->right, height++);

    return t;
}

void OutputFloor(int height, TREE_ t)
{
    if (t->left==NULL && t->right==NULL)
    {
        printf("%d %d\n", t->num, t->h);
        return;
    }
    if (t->left != NULL)
        OutputFloor(maxHeight, t->left);
    if (t->right != NULL)
        OutputFloor(maxHeight, t->right);
}