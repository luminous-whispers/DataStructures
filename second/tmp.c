#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

struct BookInfo{
    char name[60];
    char author[30];
    char press[40];
    char date[20];
    int rank;//0代表尚未开辟, 其他代表真实排序, -1代表删除
} book[2];

int cmp(const void *str1, const void *str2)//升序
{
    struct BookInfo A = *(struct BookInfo *)str1, B = *(struct BookInfo *)str2;
    int i, len = (strlen(A.name)<strlen(B.name)?strlen(A.name):strlen(B.name));

    for (i = 0; i < len; i++)
    {
        if (A.name[i] > B.name[i])
            return 1;
        else if (A.name[i] < B.name[i])
            return -1;
    }
    return 0;//完全相同, 或者还有只有前一段相同??
}

int main()
{
    int i;
    strcpy(book[0].name, "hello");
    strcpy(book[1].name, "azhe");
    printf("%d", cmp(&book[0], &book[0]));
    return 0;
}

