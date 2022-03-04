#include<stdio.h>
#include<string.h>


char str[100];

void reverse(char s[]) 
{ 
    int temp,i,j; 
    for(i=0,j=strlen(s)-1;i<j;i++,j--) 
    { 
        temp=s[i]; 
        s[i]=s[j]; 
        s[j]=temp; 
    } 
} 


void itoh(unsigned n,char s[]) 
{ 
    int h,i=0; 
    do
    { 
        h=n%16;
        s[i++]=(h<=9)?h+'0':h+'A'-10; 
    }
    while((n/=16)!=0); 
    s[i++]='x';s[i]='0';
    reverse(s); 
}

main()
{
    itoh(272,str);
    printf("%s", str);

}
