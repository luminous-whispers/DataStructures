#include"Polynomial.h"
#include"Polynomial.c"

int main()
{
    Polynomial Poly1, Poly2, PolyProd;
    Poly1= createPolynomial( );
    Poly2= createPolynomial( );
    PolyProd= createPolynomial( );

    input( Poly1);//这里尝试过用freopen,但是失败了,似乎freopen不能和函数内部进行互动, 作用域不一样
    input( Poly2);
    multPolynomial( Poly1, Poly2, PolyProd);
    output( PolyProd);

    return 0;
}