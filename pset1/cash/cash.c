#include<stdio.h> //Importing input output library
#include<cs50.h> //Importing cs50 library

int main(void)
{
    float f1;
    do //Gets user input > 0
    {
        f1 = get_float("O hai! How much change is owed?");
    }
    while (f1 < 0);
    f1 = f1 * 100; //for converting in cents
    int f = (int)f1; //converting in integer
    if ((f1 - f) > 0.5) //Rounding off
    {
        f = f + 1;
    }


    int count = 0; //Counter for number of coins

    while (f >= 25) //Evaluating particular coins
    {
        f = f - 25;
        count++;
    }


    while (f >= 10)
    {
        f = f - 10;
        count++;
    }

    while (f >= 5)
    {
        f = f - 5;
        count++;
    }

    while (f >= 1)
    {
        f = f - 1;
        count++;
    }

    printf("%d", count);
}