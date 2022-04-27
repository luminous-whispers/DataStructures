/*第四次作业第二题 检查文本中的括号
较难, 但仍考察栈的基本知识
*/
//!人为规定, 对栈顶的操作都放在显层(main函数)中, 方便可读性
#include<stdio.h>
#define TRUE 1
#define FALSE 0

struct NODE{
    char bracket;
    int line;
};

struct NODE showStack[205];
int topS = -1;
struct NODE judgeStack[205];
int topJ = -1;

int PopOut(int top, struct NODE[]);//index指要popout的元素个数
void PushIn(int top, struct NODE[], struct NODE tmp);
int BackwardQuery(char target, char * start);//返回步长, 没有返回0
void print(struct NODE);//输出单个(错误时)


int main()
{
    int lineTmp = 1, i, len;
    char str[300];
    struct NODE tmp;
    FILE *fp;
    fp = fopen("example.c", "r");
    while (fgets(str, 300, fp) != NULL)
    {
        // if (str[0] == '\n')
        //     continue;  这里被坑了, 网站上实例中的换行需要忽略, 不应该作为单独情况
        for (i=0; str[i]!='\0'; i+=len)
        {
            len = 1;//设定初始步长

            if (str[i] == '/')
            {
                if (str[i+1] == '*')
                {
                    //comment like /* */
                    if (len = BackwardQuery('*', &str[i+1]) )
                        if (str[i+2+len]=='/')
                            len +=3;
                        else
                            len = 2;
                    else
                        len = 2;
                }
                else if (str[i+1] == '/')
                    break;//end in comment;
            }
            else if (str[i] == '\'')
            {
                if ( !(len = BackwardQuery('\'', &str[i])) )
                    len = 1;
            }
            else if (str[i] == '\"')
            {
                if ( !(len = BackwardQuery('\"', &str[i])) )
                    len = 1;
            }
            else if (str[i] == '{'||str[i] == '}'||str[i] == '('||str[i] == ')')
            {
                switch (str[i])
                {
                    case '{':
                        tmp.bracket = '{';
                        tmp.line = lineTmp;
                        PushIn(++topS, showStack, tmp);
                        if (topJ == -1)
                            PushIn(++topJ, judgeStack, tmp);
                        else
                        {
                            if (judgeStack[topJ].bracket == '(')
                            {
                                print(judgeStack[topJ]);
                                return 0;
                            }
                            else
                                PushIn(++topJ, judgeStack, tmp);
                        }
                        break;
                    case '}':
                        tmp.bracket = '}';
                        tmp.line = lineTmp;
                        PushIn(++topS, showStack, tmp);
                        if (topJ == -1)
                        {
                            print(tmp);
                            return 0;
                        }
                        else if (judgeStack[topJ].bracket == '{')
                            PopOut(topJ--, judgeStack);//其实没什么用, 仅用来表示意义
                        else 
                        {
                            print(tmp);
                            return 0;
                        }
                        break;
                    case '(':
                        tmp.bracket = '(';
                        tmp.line = lineTmp;
                        PushIn(++topS, showStack, tmp);
                        PushIn(++topJ, judgeStack, tmp);
                        break;
                    case ')':
                        tmp.bracket = ')';
                        tmp.line = lineTmp;
                        PushIn(++topS, showStack, tmp);
                        if (topJ == -1)
                        {
                            print(tmp);
                            return 0;
                        }
                        else if (judgeStack[topJ].bracket == '(')
                            PopOut(topJ--, judgeStack);
                        else
                        {
                            print(tmp);
                            return 0;
                        }
                }
            }

        }
        lineTmp++;
    }
    //check if empty
    if (topJ != -1)
        print(judgeStack[topJ]);
    else
    {
        //brackets is correctly matched
        i = 0;
        while (topS != -1)
        {
            printf("%c", showStack[i++]);
            topS--;
        }
    }
    return 0;
}

int PopOut(int top, struct NODE brackets[])
{
    return brackets[top].bracket;
}

void PushIn(int top, struct NODE brackets[], struct NODE tmp)
{
    brackets[top].bracket = tmp.bracket;
    brackets[top].line = tmp.line;
    return;
}

int BackwardQuery(char target, char *start)
{
    int len;
    for (len=1; *(start+len)!='\0'; len++)
    {
        if (*(start+len)==target)
        {
            return len;
        }
    }
    return 0;
}

void print(struct NODE tmp)
{
    printf("without maching \'%c\' at line %d", tmp.bracket, tmp.line);
    return; 
}