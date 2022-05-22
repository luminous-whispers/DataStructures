/*第四次作业第一题
栈的基本操作, 简单*/
#include<stdio.h>
#define TRUE 1;
int stack[100];
int top = -1;

int main()
{
    int mode, end = 0;
    int input, output;
    while (scanf("%d", &mode) != EOF && !end)
    {
        switch (mode)
        {
            case 1:
                scanf("%d", &input);
                if (top == 99)
                {
                    printf("error ");
                    break;
                }
                else
                    stack[++top] = input;
                break;
            case 0:
                if (top == -1)
                {
                    printf("error ");
                    break;
                }
                else
                    output = stack[top--];
                printf("%d ", output);
                break;
            case -1:
                end = TRUE;
        }
    }
    return 0;
}