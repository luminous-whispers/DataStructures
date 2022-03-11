#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 


main()
{
    char *P = "hello", str[] = {"agzllo"};
    char *Ptr = &str[1];
    strncpy(Ptr, P, 2);
    printf("%s", str);
}