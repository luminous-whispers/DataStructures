/*字典树例程-普通实现
参考: https://www.cnblogs.com/PokimonMaster/p/12188791.html
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

#define MAX_SIZE 26//字典宽度
enum BOOL{true, false};

struct TRIE;
typedef struct TRIE *TREE_;
typedef struct TRIE *POSITION_;
struct TRIE{
    //int count;
    enum BOOL isEnd;
    POSITION_ p[MAX_SIZE];//0代表a, 和二维数组实现不同
    //char str[50]; //*如果需要频繁读取整个单词, 可以在末端直接储存
};

POSITION_ CreateNode()
{
    TREE_ t;
    t = (TREE_)malloc(sizeof(struct TRIE));
        memset(t, 0, sizeof(struct TRIE));
    return t;
}

//需要头节点, 储存初始26个字母
TREE_ Init(){
    return CreateNode();
}

/*need empty head!
not recursive, always start from head*/
void Insert(char * str, TREE_ root)
{
    POSITION_ pos = root;
    int len = strlen(str), index, i;
    for (i=0; i<len; i++)
    {
        index = str[i] - 'a';
        if (pos->p[index] == NULL)
            pos->p[index] = CreateNode();
        pos = pos->p[index];
        //pos->count++;
    }
    pos->isEnd = true;//或存储整个单词
    return ;
}

enum BOOL Find(char * str, TREE_ root)
{
    POSITION_ pos = root;
    int len = strlen(str), i, index;
    for (i=0; i<len; i++)
    {
        index = str[i] - 'a';
        if (pos->p[index] == NULL)
            return false;
        pos = pos->p[index];
    }
    if (pos->isEnd)//要注意存在前缀,但单词不存在的情况
        return true;
    else
        return false;
}

int main()
{
    clock_t start, end; 
    start = clock(); 
    char str[50];
    int inDict = 0, len;
    TREE_ t;
    FILE *fp_dict;
    fp_dict = fopen("F:\\notes\\assign\\bonus\\reference\\dictionary.txt", "r");
    t = Init();
    while (fgets(str, 49, fp_dict) != NULL)
    {
        len = strlen(str);
        str[len - 1] = 0;//将\n置为0
        Insert(str, t);
    }
    inDict = Find("hello", t);
    printf("%d", inDict);
    end = clock();
    printf("time = %f (s)\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}

