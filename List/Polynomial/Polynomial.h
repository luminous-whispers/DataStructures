#include<stdio.h>
#include<stdlib.h>

#ifndef _Polynomial_List_H
#define _Polynomail_List_H

struct Node;
typedef struct Node * PtrToNode;//说实话，隐藏指针多少有点愚蠢
typedef PtrToNode Polynomial;//指向一个表头，但本身并不是一个表头，易混淆
typedef PtrToNode Position;//最好typedef全大写， 否则自定类型和自定变量含义相似时很难区分，这里懒

//void zeroPolynomial( Polynomial Poly );
void addPolynomial( const Polynomial Poly1, 
    const Polynomial Poly2, Polynomial PolySum );//const是保证该指针不在局部被改动
void multPolynomial( const Polynomial Poly1, 
    const Polynomial Poly2, Polynomial PolyProd );
void deletePolynomial( Polynomial L);//叫clear也许更好
Polynomial createPolynomial( );

int isEmpty( Polynomial L );
int isLast( Position P, Polynomial L );
Position findExponent( int ToFindExponent , Polynomial L );//拿系数在多项式中寻找项
Position findPrevious( int ToFindExponent, Polynomial L );
void insertAfter( int Coefficient , int Exponent, Position P, Polynomial L);
void delete( int Exponent ,Polynomial L);
void output( Polynomial L);
void input( Polynomial L);//先入系数,再入指数

#endif