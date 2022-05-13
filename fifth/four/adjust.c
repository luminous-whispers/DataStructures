/*第五次作业- 树 - 第四题
简单排序和遍历
难点在于同层按序遍历, 需要向上寻找路径相遇点的顺序*/
//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//#include<windows.h>

enum ORDER{left = 1, mid, right};
struct NODE{
    int no;
    int parent;
    int level;//层, 最后对分叉根据节点排序
    int son[3];//用于标识登机口
    enum ORDER order;
}node[220];
int IsGate(int);//是否是登机口
void InitNode(int parent, int left, int mid, int right);
int NodeCmp(const void *, const void *);
void Mapping();
int findParent(struct NODE, struct NODE);

struct GATE{
    int people;
    int no;
}gate[120];
int GateCmp(const void *, const void *);

int main()
{
    int i, num, tmp;
    int left, mid, right, parent;
    //freopen("in.txt", "r", stdin);
    while(1)//初始化节点登机口
    {
        left = mid = right = parent = 0;
        scanf("%d" , &parent);
        if (parent == -1)
            break;
        for (i=2; ;i++)
        {
            scanf("%d" , &tmp);
            if (tmp == -1)
                break;

            if (i == 2)
                left = tmp;
            else if (i == 3)
                mid = tmp;
            else if (i == 4)
                right = tmp;
        }
        InitNode(parent, left, mid, right);  
    }
    while (scanf("%d %d", &i, &num) != EOF)
    {
        gate[i].people = num;
        gate[i].no = i;
    }

    qsort(node, 100, sizeof(struct NODE), NodeCmp);//按层序排序, 0无效
    qsort(gate, 110, sizeof(struct GATE), GateCmp);//按客流量排序
    Mapping();
}

void InitNode(int parent, int left, int mid, int right)
{
    int tmp_lv, i, tmp_ptr;
    if (parent == 100)
    {
        node[100].level = 1;
        node[100].order = 1;
        node[100].no = 100;
    }
    tmp_lv = node[parent].level;
    node[parent].son[0] = left;
    node[parent].son[1] = mid;
    node[parent].son[2] = right;

    for (i=0; i<3; i++)
    {
        tmp_ptr = node[parent].son[i];
        if (node[parent].son[i] != 0)//空节点
        {
            if (IsGate(tmp_ptr))
            {
                node[tmp_ptr].order = i + 1;
                node[tmp_ptr].level = tmp_lv + 1;
                node[tmp_ptr].parent = parent;
            }
            else
            {
                node[tmp_ptr].order = i + 1;
                node[tmp_ptr].parent = parent;
                node[tmp_ptr].level = tmp_lv + 1;
            }
            node[tmp_ptr].no = tmp_ptr;
        }
    }
    return ;
}

/*按层序排序, 0无效*/
int NodeCmp(const void *a, const void *b)
{
    struct NODE A = *(struct NODE *)a, 
        B = *(struct NODE *)b;

    if (A.level > B.level)
        return 1;
    else if (A.level < B.level)
        return -1;
    else//同层按序遍历, 需向上寻找最大的爹,当且仅当路径相同停止
    {
        return findParent(A, B);
    }
}

int findParent(struct NODE a, struct NODE b)
{
    if (a.parent == b.parent)
    {
        if (a.order > b.order)
            return 1;
        else
            return -1;
    }
    return findParent(node[a.parent], node[b.parent]);
}

/*按客流量排序*/
int GateCmp(const void *a, const void *b)
{
    struct GATE A = *(struct GATE *)a, 
        B =  *(struct GATE *)b;
    if (A.people < B.people)
        return 1;
    else if (A.people > B.people)
        return -1;
    else
    {
        if (A.no > B.no)
            return 1;
        else
            return -1;
    }
}

void Mapping()
{
    int i, j = 0;
    for (i=0; i<120; i++, j++)
    {
        if (gate[i].people != 0)
        {
            for (; j<220; j++)
                if (node[j].no != 0)
                    break;
            printf("%d->%d\n", gate[i].no, node[j].no);
        }
    }
}

int IsGate(int no)
{
    if (no == 0)
    {
        return 0;
    }
    else if (no >= 100)
        return 0;
    else
        return 1;
}
