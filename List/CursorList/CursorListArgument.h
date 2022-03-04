#include<stdio.h>
#include<stdlib.h>

#define _ELEMENT_TYPE_  int
#define _SPACE_SIZE_ 10

#ifndef _Cursor_H
#define _cursor_H

    typedef int PTR_TO_NODE;
    typedef PTR_TO_NODE LIST;
    typedef PTR_TO_NODE POSITION;   

    void initializeCursorSpace( void );

    LIST makeEmpty( LIST L );
    int isEmpty( const LIST L );
    int isLast( const POSITION P, const LIST L );
    POSITION find( _ELEMENT_TYPE_ X, const LIST L );
    void deleteElement( _ELEMENT_TYPE_ X, LIST L );
    POSITION findPrevious( _ELEMENT_TYPE_ X, const LIST L );
    void insert( _ELEMENT_TYPE_ X, LIST L, POSITION P );
    void deleteList( LIST L );
    POSITION header( const LIST L );
    POSITION first( const LIST L );
    POSITION advance( const POSITION P );
    _ELEMENT_TYPE_ retrieve( const POSITION P );//这是检索，注意和find的区别

#endif

