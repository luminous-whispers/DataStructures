#include<stdio.h>
typedef struct 
{
    int X;//x表示纵列
    int Y;//y表示横行
    int piece;
} PIECES;

PIECES Chess[19][19];//棋,1白,2黑 
int Mode[4][4] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}};

void inputInfo(PIECES Chess[19][19]);
PIECES * searchAll(PIECES goal);//这样返回值就能直接包含位置信息, 返回NULL如果失败. 同时查找四个方向,返回符合规范的位置
PIECES * searchOne(PIECES goal, int mode);

int main()
{
    int x, y;
    PIECES * Result;
    inputInfo(Chess);
    for (y = 0; y < 19; y++)
    {
        for (x = 0; x < 19; x++)
        {
            if(Chess[x][y].piece != 0)
            {
                Result = searchAll(Chess[x][y]);
                if (Result != NULL)
                {
                    printf("%d:%d,%d\n", Result->piece, Result->Y + 1, Result->X + 1);
                    return 0;
                }
            }
        }
    }
    printf("No\n");
    return 0;
}

void inputInfo(PIECES Chess[19][19])
{
    int x, y;
    for (y = 0; y < 19; y++)
    {
        for (x = 0; x < 19; x++)
        {
            scanf("%d", &Chess[x][y].piece);
            Chess[x][y].X = x;
            Chess[x][y].Y = y;
        }
    }
}

PIECES * searchAll(PIECES goal)
{
    int i;
    PIECES * P;
    for (i = 0; i < 4; i++)
    {
        P = searchOne(goal, i);
        if( NULL == P)
            continue;
        else
            return P;
    }
    return NULL;
}

PIECES * searchOne(PIECES goal, int mode)//没有检验前后有没有封堵
{
    int i;
    int x = goal.X, y = goal.Y, flag = goal.piece;
    for (i = 0; i < 4; i++)
    {
        if (Chess[x+Mode[mode][0]*i][y+Mode[mode][1]*i].piece != flag)
            return NULL;
    }
    if (flag == 1)
    {
        if (Chess[x+Mode[mode][0]*i][y+Mode[mode][1]*i].piece != 2
                || Chess[x-Mode[mode][0]][y-Mode[mode][1]].piece != 2)//检测两端
            return &Chess[x][y];
    }
    else
    {
        if (Chess[x+Mode[mode][0]*i][y+Mode[mode][1]*i].piece != 1
                || Chess[x-Mode[mode][0]][y-Mode[mode][1]].piece != 1)//检测两端
            return &Chess[x][y];
    }
    return NULL;
}