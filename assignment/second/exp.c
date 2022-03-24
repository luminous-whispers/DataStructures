#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * textFileInput(char * filename)
{
    //remember to free buffer
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen( filename , "rb" );
    if ( !fp ) perror(filename),exit(1);

    fseek(fp , 0 , SEEK_END);//0L
    lSize = ftell(fp);
    rewind(fp);

    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );//用calloc就不用末尾加\0了,自动初始化好了
    if ( !buffer ) fclose(fp), fputs("memory alloc fails",stderr), exit(1);

    /* copy the file into the buffer and meantime check it */
    if ( 1!=fread( buffer , lSize, 1 , fp) )
    fclose(fp), free(buffer), fputs("entire read fails",stderr), exit(1);

    fclose(fp);
    // free(buffer);
    return buffer;
}
