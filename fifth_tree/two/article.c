#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//#include<windows.h>

#define ELEMENTTYPE_ char*
#ifndef _TREE_H
#define _TREE_H
    struct NODE;
    typedef struct NODE *POSITION_;
    typedef struct NODE *TREE_;
    TREE_ Insert(ELEMENTTYPE_, TREE_ T);

    struct NODE{
        ELEMENTTYPE_ value;
        TREE_ left;
        TREE_ right;
        int count;
    };
#endif

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
    char str[200], *p, *tmp;
    int len;
    fp = fopen("article.txt", "r");
    //fp = fopen("F:\\notes\\assign\\fifth\\two\\article.txt", "r");
    while ( fgets(str, 150, fp) != NULL )
    {
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

/*insert element, but not dispose repeated item*/
TREE_ Insert(ELEMENTTYPE_ x, TREE_ t)
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
            t->count = 1;
        }
    }
    else
    if (strcmp(x, t->value) < 0)
        t->left = Insert(x, t->left);
    else
    if (strcmp(x, t->value) > 0)
        t->right = Insert(x, t->right);
    else
        t->count++;
    return t;
}
