/*v0-0
此版本数据结构: 三个字典树, 未使用topk算法仅qsort全部数据
不打印时间大致在0.2s左右
数据计算出现问题, 尚未定位问题, simd大致趋势正确, 但准确数值不正确
可能是某处逻辑低级错误*/
// #define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
// #include<windows.h>
#include<math.h>
// #include<time.h>

//size部分
#define KEY_SIZE 100
#define LINE_SIZE 5000
#define DOC_SIZE 3000
#define KEY_TRIE_SIZE 10000
#define DICT_TRIE_SIZE 3000000
#define STOP_TRIE_SIZE 100000
#define WORD_SIZE 200//字典中单词长度
typedef int POS;
#define EPSILON 1e-6//比较浮点数

//info部分
int key_num;
int doc_num;
struct KEY_WORD {
    //固有数据
    char word[30];
    int key_appear_doc_num;
    double anti_key_freq;
    //浮动数据
    int single_doc_key_num;
    int single_state;//现在记录的是哪篇文章
}key[KEY_SIZE];//以key_num为游标, 从1开始
double single_doc_key_freq[DOC_SIZE][KEY_SIZE];

struct WEBSITE {
    int no_num;//编号
    char no_serial[30];//文档内编号
    double doc_sim;
}doc[DOC_SIZE];//从1开始

//预处理部分: 构建词典 字典树
enum BOOL { F, T };
enum BOOL InDict( char * );
enum BOOL InStopDict( char * );
void CreateDictTrie( );
void CreateStopTrie( );
int dict_trie[DICT_TRIE_SIZE][30];
int stop_trie[KEY_TRIE_SIZE][30];
enum BOOL flag_dict_trie[DICT_TRIE_SIZE];
enum BOOL flag_stop_trie[STOP_TRIE_SIZE];
int total_dict_trie;
int total_stop_trie;

//关键词公用trie部分
int key_public_trie[KEY_TRIE_SIZE][30];
enum BOOL flag_key_trie[KEY_TRIE_SIZE];
int key_ptr[KEY_TRIE_SIZE];//记录字典树末数据域的地址
int total_key_trie;
//字典树例程
void CleanTrie( int( *trie )[30], enum BOOL *flag, int *total );
int Insert( int( *trie )[30], enum BOOL *flag, int *total, char *str );
int Find( int( *trie )[30], enum BOOL *flag, int *total, char *str );
//处理文章例程
char *StrConstCpy( char *source, int len );
/* cmp func for qsort */
int Cmp( const void *a, const void *b ) {
    double gap = ( ( struct WEBSITE * )a )->doc_sim - ( ( struct WEBSITE * )b )->doc_sim;
    if ( gap < 0 && fabs(gap)>EPSILON )
        return 1;
    else if ( gap > 0 && fabs(gap)>EPSILON)
        return -1;
    else {
        gap = ( ( struct WEBSITE * )a )->no_num - ( ( struct WEBSITE * )b )->no_num;
        if ( gap > 0 )
            return 1;
        else
            return -1;
    }
}


int main( int argc, char *argv[] ) {//"100","edu","news","article"
    char str[LINE_SIZE];
    int result_num, tail, len, word_num=0;
    int i, j;
    FILE *fp_in_article, *fp_out;
    char *p, *tmp;
    /*测时结构*/
    /* clock_t start, end;
    start = clock( ); */
    CreateDictTrie( );
    CreateStopTrie( );
    // fp_in_article = fopen( "F:\\notes\\assign\\bonus\\reference\\article.txt", "r" );
    fp_in_article = fopen( "article.txt", "r" );
    fp_out = fopen( "results.txt", "w" );

    if ( argc >= 2 ) {
        sscanf( argv[1], "%d", &result_num );
        for ( i = 2; i < argc; i++) {
            //构建公用keyTrie
            if ( !InStopDict( argv[i] ) && InDict( argv[i] ) ) {
                key_num++;                 
                tail = Insert( key_public_trie, flag_key_trie, &total_key_trie, argv[i] );
                key_ptr[tail] = key_num;
                strcpy( key[key_num].word, argv[i] );
            }
        }
    }
    
    doc_num = 1;
    fscanf( fp_in_article, "%s", doc[doc_num].no_serial );
    while ( fgets( str, 4900, fp_in_article ) != NULL ) {
        if ( str[0] == '\f' ) {
            //上一文章相关计算
            doc[doc_num].no_num = doc_num;
            for ( i = 1; i <= key_num; i++ )
                if (key[i].single_state==doc_num)
                    single_doc_key_freq[doc_num][i] = 100 * ( double )key[i].single_doc_key_num / word_num;

            //新文章周期
            doc_num++;
            fscanf( fp_in_article, "%s", doc[doc_num].no_serial );//向下读入下一文章序号
            word_num = 0;//重置词数
        }
        for ( p = str; *p != 0; p += len ) {
            //读入并处理单词
            for ( len = 0; isalpha( *( p + len ) ); len++ )
                *( p + len ) = tolower( *( p + len ) );//tolower
            if ( isalpha( *p ) ) {
                tmp = StrConstCpy( p, len );
                if ( !InStopDict( tmp ) && InDict( tmp ) ) {
                    word_num++;
                    tail = Find( key_public_trie, flag_key_trie, &total_key_trie, tmp );
                    if ( tail ) {//非0, 即出现
                        if ( key[key_ptr[tail]].single_state < doc_num ) {
                            key[key_ptr[tail]].key_appear_doc_num++;
                            key[key_ptr[tail]].single_state = doc_num;
                            key[key_ptr[tail]].single_doc_key_num = 0;//将本文章出现该词次数重置
                        }
                        key[key_ptr[tail]].single_doc_key_num++;
                    }
                }
            }else
                len = 1;//p not alpha
        }
    }
    //计算idf, 逆向词频
    for ( i = 1; i <= key_num; i++ ) {
        if (key[i].key_appear_doc_num!=0)
            key[i].anti_key_freq = log10( ( double )doc_num / key[i].key_appear_doc_num );
    }
    //计算simd
    for ( i = 1; i <= doc_num; i++ ) {
        for ( j = 1; j <= key_num; j++ ) {
            doc[i].doc_sim += (double)key[j].anti_key_freq * single_doc_key_freq[i][j];
        }
    }
    //topk & top_result
    qsort( &doc[1], doc_num, sizeof( struct WEBSITE ), Cmp );

    //输出部分
    j = 5 < doc_num ? 5 : doc_num;
    for ( i = 1; i <= j; i++ ) {
        printf( "%.6lf %d %s\n", doc[i].doc_sim, doc[i].no_num, doc[i].no_serial );
    }
    j = result_num < doc_num ? result_num : doc_num;
    for ( i = 1; i <= j; i++ ) {
        fprintf( fp_out, "%.6lf %d %s\n", doc[i].doc_sim, doc[i].no_num, doc[i].no_serial );
    }
    fclose( fp_out );
    fclose( fp_in_article );
    /* end = clock( );
    printf( "time=%f\n", ( double )( end - start ) / CLOCKS_PER_SEC ); */
    return 0;
}

//返回该单词最终位置
int Insert( int( *trie )[30], enum BOOL *flag, int *total, char *str ) {
    int len = strlen( str );
    int i, id;
    int parent = 0;
    //!未检查是否溢出
    for ( i = 0; i < len; i++ ) {
        id = str[i] - 'a' + 1;
        if ( !trie[parent][id] )
            trie[parent][id] = ++*total;
        parent = trie[parent][id];//ptr down
    }
    flag[parent] = T;
    return parent;
}

int Find( int( *trie )[30], enum BOOL *flag, int *total, char *str ) {
    int len = strlen( str );
    int parent = 0, i, id;
    for ( i = 0; i < len; i++ ) {
        id = str[i] - 'a' + 1;
        if ( !trie[parent][id] )
            return 0;//0空间没有用, 代表空
        parent = trie[parent][id];//游标下沉
    }
    if ( flag[parent] )//是词尾
        return parent;
    else
        return 0;
}

/*清空树*/
void CleanTrie( int( *trie )[30], enum BOOL *flag, int *total ) {
    int i, j;
    for ( i = 0; i < *total; i++ ) {
        flag[i] = F;
        for ( j = 1; j < 27; j++ )
            trie[i][j] = 0;
    }
    total = 0;
}

void CreateDictTrie( ) {
    FILE *fp_in_dict;
    char word[WORD_SIZE];
    //fp_in_dict = fopen( "F:\\notes\\assign\\bonus\\reference\\dictionary.txt", "r" );
    fp_in_dict = fopen( "dictionary.txt", "r" );
    while ( fscanf( fp_in_dict, "%s", word ) != EOF )
        Insert( dict_trie, flag_dict_trie, &total_dict_trie, word );
    fclose( fp_in_dict );
    return;
}

void CreateStopTrie( ) {
    FILE *fp_in_stop;
    char word[WORD_SIZE];
    // fp_in_stop = fopen( "F:\\notes\\assign\\bonus\\reference\\stopwords.txt", "r" );
    fp_in_stop = fopen( "stopwords.txt", "r" );
    while ( fscanf( fp_in_stop, "%s", word ) != EOF )
        Insert( stop_trie, flag_stop_trie, &total_stop_trie, word );
    fclose( fp_in_stop );
    return;
}

enum BOOL InDict( char *word ) {
    int in = Find( dict_trie, flag_dict_trie, &total_dict_trie, word );
    if ( in )
        return T;
    else
        return F;
}
enum BOOL InStopDict( char *word ) {
    int in = Find( stop_trie, flag_stop_trie, &total_stop_trie, word );
    if ( in )
        return T;
    else
        return F;
}
char *StrConstCpy( char *source, int len ) {
    char *ptr;
    int i;
    ptr = ( char * )malloc( len );
    if ( ptr == NULL ) {
        printf( "Memory allocation failed!\n" );
        exit( 0 );
    }

    for ( i = 0; i < len; i++ )
        *( ptr + i ) = *( source + i );
    *( ptr + i ) = 0;
    return ptr;
}