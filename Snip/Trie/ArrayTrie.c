/*用"二维数组"实现字典树*/

/*目前为小写字母字典树
稍微修改, 见?注释, 就可以变为数字的字典树*/

/*笔记详见: Obsidian/c/数据结构/树/字典树
obsidian://open?vault=c&file=%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%2F%E6%A0%91%2F%E5%AD%97%E5%85%B8%E6%A0%91*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

#define MAX_SIZE 10000000
int tree[MAX_SIZE][30];//tree[i][j]表示节点i的第j个儿子的节点编号

enum BOOL{false, true};
enum BOOL flag[MAX_SIZE];//标识单词结尾
int total; //总节点数

/*input word, and init or insert tree*/
void Insert(char *str)
{
    int len = strlen(str);
    int i, id;
    int parent = 0;
    if (total+1 == MAX_SIZE)
    {
        printf("error, out of memory with larger data!");
        return ;
    }
    for (i=0; i<len; i++)
    {
        //a->1...
        id = str[i] - 'a' + 1;//?str[i]-'0'
        if (!tree[parent][id])//尚不存在
            tree[parent][id] = ++total;
        parent = tree[parent][id];//游标下沉
    }
    flag[parent] = true;
}

enum BOOL Find(char *str)
{
    int len = strlen(str);
    int parent = 0, i, id;
    for (i=0; i<len; i++)
    {
        id = str[i]-'a'+1;//?str[i]-'0'
        if (!tree[parent][id])
            return false;
        parent = tree[parent][id];//游标下沉
    }
    return true;
}

/*清空树*/
void init(){
    int i, j;
    for (i=0; i<total; i++)
    {
        flag[i] = false;
        for (j=1; j<27; j++)//?j<10
            tree[i][j] = 0;
    }
    total = 0;
}
/*
int main()
{
    clock_t start, end; 
    start = clock(); 
    char str[50];
    int isDict = 0, isStop = 0;
    FILE *fp_dict, *fp_stop;
    fp_dict = fopen("F:\\notes\\assign\\bonus\\reference\\dictionary.txt", "r");
    fp_stop = fopen("F:\\notes\\assign\\bonus\\reference\\stopwords.txt", "r");
    init();
    while (fgets(str, 49, fp_dict) != NULL)
        Insert(str);
    isDict = Find("a");
    init();
    while (fgets(str, 49, fp_stop) != NULL)
        Insert(str);
    isStop = Find("a");
    printf("dict:%d, stop:%d\n", isDict, isStop);
    end = clock();
    printf("time = %f (s)\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

