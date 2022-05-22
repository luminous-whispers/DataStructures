/*第六次作业第一题 综合考试四种基本查找方法*/
/*程序结构为:
1. 读入字典(已排序),  顺序查找
2. 拆半查找
3. 建立简单索引表
4. 简单hash表构建, 查找*/
#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>

char dict[3520][22];
char target[22];
struct HASH_ELEMENT {
    char *pos;
    struct HASH_ELEMENT *next;
};
struct HASH_ELEMENT  hashTable[3001];
int indx[26]; // index大概在某个库里被定义了
int sign[26]; //标记索引表这个字母是否存在
// char (*Index[26])[22];//是个26大小的数组, 数组类型是指针, 指针指向 char[22]

void OrderSearch( int *state, int *op_num, int size );
void BinSearch( int *state, int *op_num, int size );
void IndexSearch( int *state, int *op_num );
unsigned int Hash( char *str );
void HashSearch( int *state, int *op_num );

int main( ) {
    FILE *fp;
    int i, mod, state, op_num, len;
    unsigned int hash_indx;
    char flag = 'a'-1;
    struct HASH_ELEMENT *p;
    fp = fopen( "dictionary3000.txt", "r" );
    //fp = fopen( "F:\\notes\\assign\\six_search\\dictionary3000.txt", "r" );
    for ( i = 0; fscanf( fp, "%s", dict[i] ) != EOF; i++ ) {
        //fgets为什么不行?,这题不能用fgets的原因是出题人的txt字典文件是在windwos里写的, 然后未作处理直接放到了linux下, 导致\r无法处理
        //正常linux是没有\r而只有\n
        len = strlen( dict[i] );
        if ( dict[i][len - 1] == '\n' )
            dict[i][len - 1] = 0;
        
        //构建索引表
        if ( flag != dict[i][0] ) {
            for(flag++; flag != dict[i][0]; flag++)
                indx[flag - 'a'] = i;
            indx[flag - 'a'] = i;
            sign[flag - 'a'] = 1;
        }
        //构建hash表
        hash_indx = Hash( dict[i] );
        for ( p = &hashTable[(int)hash_indx];
            p->next != NULL; p = p->next );
        p->next = (struct HASH_ELEMENT *)malloc( sizeof( struct HASH_ELEMENT ) );
        p = p->next, p->next = NULL, p->pos = dict[i];
    }
    len = i; //字典总长, 非下标
    while ( scanf( "%s%d", target, &mod ) != EOF ) {
        switch ( mod ) {
        case 1:
            OrderSearch( &state, &op_num, len-1 );
            break;
        case 2:
            BinSearch( &state, &op_num, len - 1 );
            break;
        case 3:
            IndexSearch( &state, &op_num );
            break;
        case 4:
            HashSearch( &state, &op_num );
            break;
        }
        printf( "%d %d\n", state, op_num );
    }
    fclose( fp );
    return 0;
}

//1

//顺序查找
void OrderSearch( int *state, int *op_num, int size ) {
    int i, result;
    for ( i = 0; i <= size && ( result = strcmp( target, dict[i] ) ) > 0; i++ );
    *op_num = ++i;
    if ( i > size )
    {
        *state = 0;
        return;
    }
    if ( result == 0 )
        *state = 1;
    else
        *state = 0;
}

//2

// recursion,
// high = num-1,like index
/*int BinSearch_rec( char( *data )[22], int low, int high, char *key, int *op_num ) {
    int mid, i=0;
    while ( low <= high ) {
        mid = ( high + low ) / 2;
        i++;
        if ( strcmp( key, data[mid] ) < 0 ) {
            high = mid - 1;
        }
        else if ( strcmp( key, data[mid] ) > 0 ) {
            low = mid + 1;
        }
        else {
            *op_num = i;
            return mid;
        }
    }
    *op_num = i;
    return -1;//查找失败
}*/
int BinSearch_rec( char( *data )[22], int low, int high, char *key, int *op_num ) {
    static int i; //比较数
    int mid = ( low + high ) / 2;
    if ( strcmp( key, data[mid] ) == 0 ) {
        *op_num = ++i;
        i = 0;
        return mid;
    }
    else if ( low > high ) {
        *op_num = i;
        i = 0;
        return -1;//!
    }
    //递归
    i++;
    if ( strcmp( key, data[mid] ) < 0 )
        return BinSearch_rec( data, low, mid - 1, key, op_num );
    else
        return BinSearch_rec( data, mid + 1, high, key, op_num );
}
//拆半查找
void BinSearch( int *state, int *op_num, int end ) {
    int result = BinSearch_rec( dict, 0, end, target, op_num );
    if ( result == -1 )
        *state = 0;
    else
        *state = 1;
}

//3

/*在单词表中通过索引表来获取单词查找范围，并在该查找范围中以折半方式查找*/
void IndexSearch( int *state, int *op_num ) {
    int begin, end, result;
    if ( !sign[target[0] - 'a'] ) {
        *state = 0;
        *op_num = 0;
        return;
    }
    begin = indx[target[0] - 'a'];
    end = indx[target[0] - 'a' + 1] - 1;
    result = BinSearch_rec( dict, begin, end, target, op_num );
    if ( result == -1 )
        *state = 0;
    else
        *state = 1;
}

//4

/* compute hash value for string */
#define NHASH 3001
#define MULT 37
unsigned int Hash( char *str ) {
    unsigned int h = 0;
    char *p;

    for ( p = str; *p != '\0'; p++ )
        h = MULT * h + *p;
    return h % NHASH;
}

void HashSearch( int *state, int *op_num ) {
    unsigned int flag = Hash( target );
    int i;
    struct HASH_ELEMENT *p = hashTable[( int )flag].next;
    if ( p == NULL ) {
        *state = 0;
        *op_num = 0;
        return;
    }
    for ( i = 1;
        strcmp( p->pos, target ) < 0 && p->next != NULL;
        p = p->next, i++ );
    if ( strcmp( p->pos, target ) == 0 )
        *state = 1;
    else
        *state = 0;
    *op_num = i;//?这个存疑
}

