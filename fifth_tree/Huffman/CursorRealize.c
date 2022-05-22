/*游标实现-基础哈夫曼树*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define WEIGHT_TYPE int
struct HUFFMAN_NODE;
typedef struct HUFFMAN_NODE *TREE_;
typedef struct HUFFMAN_NODE *POSITION_;
struct HUFFMAN_NODE{
    WEIGHT_TYPE weight;
    int parent;
    int left, right;
    //int info;//ELEMENT
};
/*永远以最小的两个权值进行树组合*/
//!游标形式, 非链形式

#define MAX_WGHT 1000
//0位置不储存任何值是因为需要0来标识未入树子节点
void Select(TREE_ t, int n, int *least, int *second)
{
    int min[2], i, j;
    min[0] = min[1] = 0;
    t[min[0]].weight = MAX_WGHT;
    for (i=1; i<=n; i++)//n代表当前非零值
    {
        if (t[i].weight < t[min[1]].weight && t[i].parent == 0)
        {
            if (t[i].weight < t[min[0]].weight)
                min[0] = i;
            else
                min[1] = i;
        }
    }
    *least = min[0];
    *second = min[1];
}

/*only need weight and its size, weight default in an array*/
/*just REWRITE it by yourself in need for other info*/
TREE_
Init(WEIGHT_TYPE *wght, int n)
{
    int total = n * 2 -1;//预期总节点数, n为实际数据数
    int i, s1, s2;//权值最小的s1和s2
    TREE_ t = (TREE_)malloc(sizeof(struct HUFFMAN_NODE)*(total + 1));
        //saze a size for empty [0]
    memset(t, 0, sizeof(struct HUFFMAN_NODE)*(total + 1));
    for (i=1; i<=n; i++)
        t[i].weight = wght[i-1];//为新空间赋初值
    for (i= n+1; i <= total; i++)
    {
        Select(t, i-1, &s1, &s2);//!出错

        t[i].weight = t[s1].weight + t[s2].weight;
        t[s1].parent = t[s2].parent = i;
        t[i].left = s1, t[i].right = s2;
    }
    return t;//数组头
}

//指向各字符huffman_code的指针哈希表
typedef char ** HUFFMAN_CODE__;

HUFFMAN_CODE__
HuffCoding(TREE_ t, int n)
{
    int i, cursor, c, p;
    HUFFMAN_CODE__ hList = 
        (HUFFMAN_CODE__)malloc(sizeof(char *)*(n+1));
        //同样舍弃0空间 
    char * assit = (char *)malloc(sizeof(char *)*n);
        //辅助空间
        //最长编码长度为n-1, n处存放0标识结尾
    assit[n-1] = 0;
    for (i=1; i<=n; i++)
    {
        c = i;//正在进行第i个数据的编码
        cursor= n- 1;//最初游标指向\0, 后向前移动
        p = t[c].parent;
        while (p)//到根节点为止, 根节点父节点为0
        {
            if (t[p].left == c)
                assit[--cursor] = '0';
            else
                assit[--cursor] = '1';
            c = p;
            p = t[c].parent;//继续向上扫描
        }
        hList[i] = (char *)malloc(sizeof(char)*(n-cursor));
        strcpy(hList[i], &assit[cursor]);
    }
    free(assit);
    return hList;
}

int main()
{
    int wght[] = {1, 2, 2, 3, 4, 5};
    TREE_ t;
    HUFFMAN_CODE__ hList;
    t = Init(wght, 6);
    hList = HuffCoding(t, 6);
    puts(hList[6]);
    return 0;
}