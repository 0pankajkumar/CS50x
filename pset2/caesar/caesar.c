#include<stdio.h> //Importing input output library
#include<cs50.h> //Importing cs50 library
#include<string.h> //for getting string library for strlen
#include<ctype.h> //for getting islower isupper fuctions

int main(int argc, string argv[])
{
    char temp; //temporary variable
    if (argc < 2 || argc > 2) //throws back if less or more arguments are passed
    {
        return 1;
    }
    else
    {

        int a = atoi(argv[1]);
        //int = lum;
        string s = get_string("plaintext: ");
        //printf("\n%s\t %lu\n", s, strlen(s));
        for (int i = 0, lum = strlen(s); i < lum; i++)
        {
            if (isupper(s[i])) //loop for uppercase
            {
                temp = s[i];
                s[i] = s[i] + a;
                if (isupper(s[i])) {}
                else
                {
                    int x, y;
                    x = s[i];
                    y = temp;
                    int z = x - 'Z';
                    s[i] = '@' + z;
                }
            }
            if (islower(s[i])) //loop for lowercase
            {
                temp = s[i];
                s[i] = s[i] + a;
                //printf("\n%c\n",s[i]);
                if (islower(s[i])) {}
                else
                {
                    while (1) //running to kill cases where numbers reach graeater than ASCII values
                    {
                        int x, y;
                        x = s[i];
                        y = temp;
                        int z = x - 'z';
                        //printf("x=%d y=%d z=%d",x,y,z);
                        s[i] = '`' + z;
                        if (islower(s[i]))
                        {
                            break;
                        }
                    }
                }
            }
        }




        printf("ciphertext: %s\n", s); //printing ciphertext
    }
    return 0;
}