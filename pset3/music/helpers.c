// Helper functions for music

#include <cs50.h> //standard cs50 lib
#include<string.h> //for getting string library for strlen
#include<ctype.h> //for getting islower isupper fuctions
#include<math.h> //for pow() & round() functions
#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int a = atoi(&fraction[0]);
    int b = atoi(&fraction[2]);
    if (b == 8)
    {
        return a;
    }
    else
    {
        while (b < 8)
        {
            b *= 2;
            a *= 2;
        }
        return a;
    }//Returns correct conversion by transforming into eights
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //int i = 0;
    //char a = note[0];
    char b = note[1];
    char c = note[2], ch = b;
    float freq = 440.00000; //Variable for frequency storing & calucation declared as float to retain decimals
    float e = 2.00000, g = (1.00000 / 12.00000); //Helps fr anf fr_
    float fr = pow(e, g); //for positive powers
    float fr_ = pow(e, -g); //for negative powers
    //All variables declared above
    switch (ch) //Switching the eights
    {
        case '0':
            freq /= 16;
            break;
        case '1':
            freq /= 8;
            break;
        case '2':
            freq /= 4;
            break;
        case '3':
            freq /= 2;
            break;
        case '4':
            freq *= 1;
            break;
        case '5':
            freq *= 2;
            break;
        case '6':
            freq *= 4;
            break;
        case '7':
            freq *= 8;
            break;
        case '8':
            freq *= 0;
            break;
        case '#': //Switching the occurance of #
            switch (c)
            {
                case '0':
                    freq /= 16;
                    freq *= fr;
                    break;
                case '1':
                    freq /= 8;
                    freq *= fr;
                    break;
                case '2':
                    freq /= 4;
                    freq *= fr;
                    break;
                case '3':
                    freq /= 2;
                    freq *= fr;
                    break;
                case '4':
                    freq *= 1;
                    freq *= fr;
                    break;
                case '5':
                    freq *= 2;
                    freq *= fr;
                    break;
                case '6':
                    freq *= 3;
                    freq *= fr;
                    break;
                case '7':
                    freq *= 4;
                    freq *= fr;
                    break;
                case '8':
                    freq *= 5;
                    freq *= fr;
                    break;
            }
            break;

        case 'b': ////Switching the occurance of b
            switch (c)
            {
                case '0':
                    freq /= 16;
                    freq *= fr_;
                    break;
                case '1':
                    freq /= 8;
                    freq *= fr_;
                    break;
                case '2':
                    freq /= 4;
                    freq *= fr_;
                    break;
                case '3':
                    freq /= 2;
                    freq *= fr_;
                    break;
                case '4':
                    freq *= 1;
                    freq *= fr_;
                    break;
                case '5':
                    freq *= 2;
                    freq *= fr_;
                    break;
                case '6':
                    freq *= 3;
                    freq *= fr_;
                    break;
                case '7':
                    freq *= 4;
                    freq *= fr_;
                    break;
                case '8':
                    freq *= 5;
                    freq *= fr_;
                    break;
            }
            break;
    } //First switch ends here. This is only for A notes

    switch (note[0]) //Switch for other alphabets namely B,A,G,F,E,D,C
    {
        case 'B':
            fr = pow(e, 2 * g);
            freq *= fr;
            break;
        case 'A':
            break;
        case 'G':
            fr_ = pow(e, -2 * g);
            freq *= fr_;
            break;
        case 'F':
            fr_ = pow(e, -4 * g);
            freq *= fr_;
            break;
        case 'E':
            fr_ = pow(e, -5 * g);
            freq *= fr_;
            break;
        case 'D':
            fr_ = pow(e, -7 * g);
            freq *= fr_;
            break;
        case 'C':
            fr_ = pow(e, -9 * g);
            freq *= fr_;
            break;
    }

    return round(freq); //returns calculated value of frequency after rounding off
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "\n") || strcmp(s, " ")) //Encountering carriage returns and Blank spaces
    {
        return true;
    }
    else // Otherwise returns plain false
    {
        return false;
    }
}