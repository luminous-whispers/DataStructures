#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * textFileInput(char *);
int visited[200];
char str[200], tmp[30];

int main()
{
    char buffer[100], *P, c, index = 'a';
    FILE * fp_out, * fp_in;
    int i = 0;

    fp_in = fopen("encrypt.txt", "r");
    if (fp_in == NULL) perror("failed to write"), exit(1);
    //buffer = textFileInput("encrypt.txt");
    fgets(buffer, 100, fp_in);
    fclose(fp_in);

    gets(tmp);
    while ((c = tmp[i++]) != '\0')
    {
        if (!visited[(int)c])
        {
            str[(int)index] = c;
            visited[(int)c] = 1;
            index ++;
        }
        else
            continue;
    }
    for (c = 'z'; c >= 'a'; c--)
    {
        if (!visited[(int)c])
        {
            str[(int)index] = c;//!
            visited[(int)c] = 1;
            index++;
        }
        else
            continue;
    }
    
    P = buffer;
    while (*P != '\0')
    {
        if (*P >= 'a' && *P <= 'z')
        {
            *P = str[(int)*P];  
        }
        P++;
    }

    fp_out = fopen("output.txt", "w");
    if (fp_out == NULL) perror("failed to write"), exit(1);
    //fputs(buffer, fp);
    fprintf(fp_out, "%s", buffer);
    fclose(fp_out);

    //free(buffer);
    return 0;
}


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
    buffer = calloc(1, lSize+1 );//用calloc就不用末尾加\0了,自动初始化好了
    if ( !buffer ) fclose(fp), exit(1);// fputs("memory alloc fails",stderr),

    /* copy the file into the buffer and meantime check it */
    if ( 1!=fread( buffer , lSize, 1 , fp) )//这样受限制其实较大
    fclose(fp), free(buffer), exit(1);//fputs("entire read fails",stderr)

    fclose(fp);
    // free(buffer);
    return buffer;
} 


