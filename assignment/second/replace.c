//核心考点:
//1.对文件中多行字符串的读取,处理,储存. 注意,标准c中没有getline函数,gcc自己加的
//  将全小写字符串单独存放,通过标记变换位置和偏移量来实现字符数组和常量字符串的配合
//2.寻找,kmp算法

/*这个文件可以作为以上两个问题的参考*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char * textFileInput(char *);//char可以指向字符串
void toLower(char *);
int KMPindex(char S[], char T[]);//魔改成char *, 方便交换指针进行查找.
void getnext(char T[], int next[]);

int main()
{
    char * P_, str[3][100]; //数据变量. 
    char * flag; //操作变量
    P_ = textFileInput("filein.txt");
    memset(str[0], 0, sizeof(str[0]));
    memset(str[1], 0, sizeof(str[1]));
    memset(str[2], 0, sizeof(str[2]));
    strcpy(str[3], P_);
    toLower(str[3]);
    gets(str[0]);
    gets(str[1]);


    
    free(P_);
    return 0;
}


char* 
textFileInput(char* filename)
{
    char* text;
    long lSize;

    FILE *pf = fopen(filename,"r");
    if (pf == NULL)
        return NULL;

    fseek(pf,0,SEEK_END);//将位置指针移动到最后
    lSize = ftell(pf);//找出位置指针偏移量,这是地址的实际偏移量
    // 用完后需要将内存free掉
    text=(char*)malloc(lSize+1);//流出\0
    rewind(pf); //将指针回调至文件首,方便fread函数
    fread(text,sizeof(char),lSize,pf);
    fclose(pf);
    text[lSize] = '\0';
    return text;
}

void toLower(char * p)
{
    int i = 0;
    while (*(p + i) != '\0')
    {
        if( *(p + i) >= 'A' && *(p + i) <= 'Z')
            *(p + i) +=  'a' - 'A';
    }
} 

int KMPindex(char S[ ], char T[ ]) 
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
        return i - j; 
    else 
        return -1; 
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


//下面是早期的一种尝试,因为弄不明白file指针的移动放弃了.目前方法是整个读入
/*    
fscanf(fp, "%[^\n]%*c", str[i]);

或
while (!feof(fp))
    {
        memset(str[i], 0, sizeof(str[i]));
        fgets(str[i], sizeof(str[i]) - 1, fp);
        fseek(fp, strlen(str[i]), SEEK_CUR);
        printf("%s", str[i]);
        i++;
    }
        rewind(fp);
    */