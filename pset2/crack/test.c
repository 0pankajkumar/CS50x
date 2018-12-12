#define _XOPEN_SOURCE
#include <unistd.h>
#include<stdio.h> //Importing input output library
#include<cs50.h> //Importing cs50 library
#include<string.h> //for getting string library for strlen
#include<ctype.h> //for getting islower isupper fuctions

int main(void)
{
    string s1 = "pankaj", s2;
    s2 = crypt(s1,"az");
    printf("%s",s2);
    printf("\n\n%c",s2[2]);
    //char a = 'a';
    //char b = 'b';strcat(a,b);
    //printf("\n%s",);h

}