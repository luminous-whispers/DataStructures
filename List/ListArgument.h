//本文档为链表初级笔记和结构
#include<stdio.h>
#include<stdlib.h>

#define ElementType int //事实上，elementType是一个抽象的概念， 可以代表任意数据类型
#define TRUE 1
#define FLASE 0

//链表声明
#ifndef _List_H //ifndef当文件没有该宏定义时自动定义, 在本文件中就能避免重复定义( 不用看.c文件脸色 )
//#define _List_H 这是定义一个这个，防止重复引用

struct Node;
typedef struct Node *PtrToNode;//换言之 typedef (struct Node *) PtrToNode
typedef PtrToNode List;
typedef PtrToNode Position;//Position和List都是指向struct Node类型的指针, 即指向一个表元素的指针

/* List L指的是链表本表, 也就是表头; Position指的是链表中某一个元素 */
List MakeEmpty( List L );
int IsEmpty( List L ); 
int IsLast( Position P, List L);
Position Find( ElementType X, List L );
Position FindPrevious( ElementType X, List L);
void Delete( ElementType X, List L);
void Insert( ElementType X, List L, Position P);
void DeleteList( List L );
Position Header( List L );
Position First( List L);
Position Advance(Position P);
ElementType Retrieve( Position P);

#endif



























