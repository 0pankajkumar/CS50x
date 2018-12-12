#define _XOPEN_SOURCE
#include <unistd.h>
#include<stdio.h> //Importing input output library
#include<cs50.h> //Importing cs50 library
#include<string.h> //for getting string library for strlen
#include<ctype.h> //for getting islower isupper fuctions

int main(int argc, string argv[])
{
    //char temp; //temporary variable
    if (argc < 2 || argc > 2) //throws back if less or more arguments are passed
    {
        return 1;
    }
    else
    {
        printf("%s", argv[2]);
    }
    return 0;
}