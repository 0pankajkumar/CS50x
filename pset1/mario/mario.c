#include<stdio.h> //Importing input output library
#include<cs50.h> //Importing cs50 library

int main(void)
{
    int n;

    //To get valid input from user
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);
    for (int i = 0; i < n; i++) //printing main loop
    {
        for (int j = n - i - 2; j >= 0; j--) //printing the spaces
        {
            printf(" ");


        }
        for (int k = 0; k < i + 2; k++) //printing the hashes
        {
            printf("#");
        }

        printf("\n");   //printing newline feed or carriage return


    }
} //End of program