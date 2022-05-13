#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

/*place in the argument, need for complete type.*/
/*single parameter, instable.*/
/*if you want a stable version, decide want to do while similarity occurs*/
/*remember to use "strcmp" and other self-compare func*/
/*always turn pointer compulsorily is complex, just `B=*(struct*)b`*/

/*warning: instable, only available for continuous memory*/
int RiseCmp(const void *a, const void *b)
{
    return ((*(struct NODE *)a).value<(*(struct NODE *)a).value)?-1:1;
}


struct NODE *p;
int n;//数据块量
p = (struct NODE *)malloc(sizeof(struct NODE) * n);
//input
qsort(p, n, sizeof(struct NODE), Cmp);

