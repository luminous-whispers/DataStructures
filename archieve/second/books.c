/* 第二次作业第五题 微型图书馆信息系统
本题例程多且复杂, 原本考虑使用链表, 由于排序难度较高作罢, 留待以后解决.
考点和例程有:
    1. 从书库中读入图书信息, 文件读入
    2. 录入单一信息, 定位插入
    3. 删除(模糊查找/可能涉及kmp)
    4. 查找(模糊查找)
    5. 录入信息到书库, 并保存退出 
    6. 排序, 字典排序
思考:　可不可以设计一种综合运行速度较快的查找算法：排序完后先读取已有书名关键词(以_分隔)进行储存.
    进行查找例程时, 检测是否是全名(含_), 不是则进入关键词系统进行查找?? 
    
    */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int POSITION;
struct BookInfo{
    char name[60];
    char author[30];
    char press[40];
    char date[20];
    int rank;//0代表尚未开辟, 其他代表真实排序, -1代表删除
} book[520];


int inputFile(char *FileName);//读入开好的全局结构体数组中, 返回有效的书数, 并自动排名
int BooksNum;//书数和排名相同, 都是从1开始.
void inputSingleBook(int BooksNum);//例程1, 仅附在结尾, 自动加rank
void deleteBooks(char *BookName, int BooksNum);//例程3. 懒惰删除, 将排名信息变为-1, 自动跳过
void findBook(char *BookName, int BooksNum);//例程2
void  outputFile(char *FileName, int BooksNum);//例程0, 不带结束程序

int cmp(const void *str1, const void *str2);
void resort(int BooksNum);//插入一本书后的简单冒泡排序
char * KMPindex(char S[], char T[]) ;
void getnext(char T[], int next[]);
void initialRank(int BooksNum);//仅按顺序重排

int main()
{
    int mode;
    char BookName[60];
    BooksNum = inputFile("books.txt");
    qsort(book, BooksNum, sizeof(struct BookInfo), cmp);
    initialRank(BooksNum);
    while(1)
    {
        scanf("%d", &mode);
        switch (mode)
        {
            case 0:
                qsort(book, BooksNum, sizeof(struct BookInfo), cmp);
                outputFile("ordered.txt", BooksNum);
                return 0;
            case 1:
                inputSingleBook(BooksNum);
                resort(BooksNum);
                BooksNum++;
                break;
            case 2:
                scanf("%s", BookName);
                findBook(BookName, BooksNum);
                break;
            case 3:
                scanf("%s", BookName);
                deleteBooks(BookName, BooksNum);
                break;
        }
    }
}

int inputFile(char *FileName){
    int i = 0;
    FILE * fp;
    fp = fopen(FileName, "r");
    while(fscanf(fp, "%s%s%s%s", book[i].name, book[i].author
        , book[i].press, book[i].date) != EOF)
        i++;
    fclose(fp);
    return i;
}

int cmp(const void *str1, const void *str2)//升序
{
    //? 注意A和B不能相同, 相同会出错??为什么呢
    struct BookInfo A = *(struct BookInfo *)str1, B = *(struct BookInfo *)str2;
    int i, len = (strlen(A.name)>strlen(B.name)?strlen(A.name):strlen(B.name));

    for (i = 0; i < len; i++)
    {
        if (A.name[i] > B.name[i])
            return 1;
        else if (A.name[i] < B.name[i])
            return -1;
    }
    return 0;//完全相同
}

void inputSingleBook(int BooksNum)
{
    //!仅仅追加在最后, 这需要最后输出时再次进行一次排序. 
    scanf("%s%s%s%s", book[BooksNum].name, book[BooksNum].author
        , book[BooksNum].press, book[BooksNum].date);
    //BooksNum++;这个放在外层, 不能隐藏
    book[BooksNum].rank = BooksNum + 1;//暂时放在最后
}

void resort(int BooksNum)
{
    int i;
    for (i = BooksNum - 1; i >= 0 && cmp(&book[BooksNum], &book[i]) < 0; i--)
    {
        //交换两者排序信息
        book[BooksNum].rank += book[i].rank;
        book[i].rank = book[BooksNum].rank - book[i].rank;
        book[BooksNum].rank = book[BooksNum].rank - book[i].rank;
    }
}

void findBook(char *BookName, int BooksNum)
{
    int i, p[520] = {0};
    for (i = 0; i < BooksNum; i++)
    {
        if (KMPindex(book[i].name, BookName) != NULL)
            p[book[i].rank] = i;  
        //注意, rank从1记, 所以没有0排位和初始化数值相同的问题
    }
    for (i = 0; i < BooksNum + 1; i++)//注意p用哈希表存储的rank信息是从1记的
    {
        if (p[i] != 0 && book[p[i]].rank != -1)
            printf("%-50s%-20s%-30s%-10s\n", book[p[i]].name, book[p[i]].author
                , book[p[i]].press, book[p[i]].date);
    }
}

char * KMPindex(char S[], char T[]) 
{
    int i = 0, j=0, *next;
    next = (int *)malloc(sizeof(int)*(strlen(T)+1));
    getnext(T, next); //求next
    while ( S[i]!='\0' && T[j]!='\0') 
    {
        if (S [i] == T[j] ) 
        {
            i++; 
            j++ ;
        } 
        else 
            (j == 0) ? i++ :(j = next[j]); //j回退到相应位置开始匹配，i不变
    }
    free(next);
    if ( T[j] == '\0') //匹配成功，返回匹配位置
        return &S[i - j]; 
    else 
        return NULL;
}

void getnext(char T[], int next[])
{ 
    int i=0, j=-1;
    next[0] = -1;
    while (T[i]!='\0')
    {
        if (j == -1 || T[i] == T[j])//i为后缀位置；j为前缀位置
        { 
            i++; 
            j++; 
            next[i]=j;  
        }
        else 
            j = next[j]; //若字符不同，则j值回溯
    } 
}

void deleteBooks(char *BookName, int BooksNum)
{
    int i;
    for (i = 0; i < BooksNum; i++)
    {
        if (KMPindex(book[i].name, BookName) != NULL)
            book[i].rank = -1;  
        //记为-1后, 不会再进行输出
    }
}

void outputFile(char *FileName, int BooksNum)
{
    int i;
    freopen(FileName, "w", stdout);
    for (i = 0; i < BooksNum; i++)
    {
        if (book[i].rank != -1)
        {
            printf("%-50s%-20s%-30s%-10s\n", book[i].name, book[i].author
                , book[i].press, book[i].date);//注意按字符宽度输出时空格也会有影响
        }
    }
    fclose(stdout);
}

void initialRank(int BooksNum)
{
    int i;
    for (i = 0; i < BooksNum; i++)
    {
        book[i].rank = i+1;
    }
}