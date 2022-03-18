/*第二次作业第二题
废弃方法, 这个方法出现了实在无法解决的问题, 问题已经定位(在3.)
核心考点:
1.对文件中多行字符串的读取,处理,储存. 注意,标准c中没有getline函数,gcc自己加的
  将全小写字符串单独存放,通过标记变换位置和偏移量来实现字符数组和常量字符串的配合
2.寻找,kmp算法
3.windows下和linux下的换行符有区别: windows下是\r\n,linux下是\n. 
    当输出到文件时, \n会被解读为\r\n, 而原本的\r也会被解读为\r\n,也就是说会凭空多出一行空行
    linux下用本文件方法没有问题, 可以用wsl验证
*/

/*这个文件可以作为以上两个问题的参考*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char * textFileInput(char *);//char可以指向字符串
void toLower(char *);
char * KMPindex(char S[], char T[]);//魔改成char *, 方便交换指针进行查找.
void getnext(char T[], int next[]);

int main()
{
    char * P_, str[3][500]; //数据变量. 
    char * flag,* k; //操作变量
    int i ,len, last_len = 0;
    freopen("output.txt", "w", stdout);

    P_ = textFileInput("filein.txt");
    memset(str[0], 0, sizeof(str[0]));
    memset(str[1], 0, sizeof(str[1]));
    memset(str[2], 0, sizeof(str[2]));
    strcpy(str[2], P_);
    str[2][strlen(P_)] = '\0';
    toLower(str[2]);
    fgets(str[0], 50, stdin);//被替换, 注意fgets虽然安全, 但是不会自动将\n替换为\0
    for (i = 0; str[0][i] != '\n'; i++);
    str[0][i] = '\0';
    fgets(str[1], 50, stdin);//替换者
    for (i = 0; str[1][i] != '\n'; i++);
    str[1][i] = '\0';

    flag = str[2]; 
    k = str[2];
    do
    {
        flag = KMPindex(flag, str[0]);//这样写第一次会出问题
        if (flag == NULL)
            break;
        else
            len = strlen(k) - strlen(flag);
        //strncpy(flag, str[0], sizeof(char)*strlen(str[1])); 实际上不用替换md
        for (i = last_len; i < len; i++)
        {
            printf("%c", *(P_ + i));
        }
        last_len = len + strlen(str[0]) ;
        flag += strlen(str[0]);
        printf("%s", str[1]);
    }
    while (1);

    printf("%s", &str[2][last_len]);

    fclose(stdout);
    free(P_);
    return 0;
}

char * textFileInput(char * filename)
{
    //remember to free buffer
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen( filename , "rb" );
    if ( !fp ) perror(filename),exit(1);

    fseek(fp , 0 , SEEK_END);//0L
    lSize = ftell(fp);
    rewind(fp);

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );//用calloc就不用末尾加\0了,自动初始化好了
    if ( !buffer ) fclose(fp), exit(1);//, fputs("memory alloc fails",stderr)

    /* copy the file into the buffer and meantime check it */
    if ( 1!=fread( buffer , lSize, 1 , fp) )
    fclose(fp), free(buffer), exit(1);//, fputs("entire read fails",stderr)

    fclose(fp);
    // free(buffer);
    return buffer;
}
/* 
这也是一种失败的读入文件方法, 问题在于无法处理文件末尾的奇妙字符. 可能是因为不初始化的问题
char* 
textFileInput(char* filename)
{
    char* text;
    long lSize;

    FILE *pf = fopen(filename, "r");
    if (pf == NULL)
        return NULL;

    fseek(pf,0,SEEK_END);//将位置指针移动到最后
    lSize = ftell(pf);//找出位置指针偏移量,这是地址的实际偏移量
    // 用完后需要将内存free掉
    text = (char*)malloc(lSize+1);//留出\0位置
    rewind(pf); //将指针回调至文件首,方便fread函数
    fread(text, sizeof(char), lSize, pf);
    fclose(pf);
    text[lSize] = '\0';//!这条语句为什么没有正常执行??
    return text;
} */

void toLower(char * p)
{
    int i = 0;
    while (*(p + i) != '\0')
    {
        if( *(p + i) >= 'A' && *(p + i) <= 'Z')
            *(p + i) +=  'a' - 'A';
        i++;
    }
} 

char * KMPindex(char S[ ], char T[ ]) 
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