/*字典树例程-普通实现
参考: https://www.cnblogs.com/PokimonMaster/p/12188791.html
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define MAX_SIZE 26//字典宽度
enum BOOL{true, false};

struct TRIE;
typedef struct TRIE *TREE_;
typedef struct TRIE *POSITION_;
struct TRIE{
    int count;
    enum BOOL isEnd;
    POSITION_ p[MAX_SIZE];//0代表a, 和二维数组实现不同
    //char str[50]; //*如果需要频繁读取整个单词, 可以在末端直接储存
};

//需要头节点, 储存初始26个字母
TREE_ Init(){
    int i;
    POSITION_ pos;
    TREE_ t;
    t = (TREE_)malloc(sizeof(struct TRIE));
    memset(t, 0, sizeof(struct TRIE));
    pos = (POSITION_)malloc(sizeof(struct TRIE)*(MAX_SIZE));//到时候释放一定要从最底层;
    memset(pos, 0, sizeof(struct TRIE)*(MAX_SIZE));
    for (i=0; i<26; i++)
        t->p[i] =  pos + i;
    return t;
}

/*访问树时, 确保其子节点皆存在*/
void Insert(char * str, TREE_ t)
{
    POSITION_ p;
    int len = strlen(str);
    if (t == NULL)
    {
        p = (TREE_)malloc(sizeof(struct TRIE));
        memset(p, 0, sizeof(struct TRIE));
    }
}