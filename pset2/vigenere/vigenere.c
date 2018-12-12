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
        string h = argv[1];
        int le = strlen(argv[1]);
        char f = 'A';
        char e = 'a';
        int pos[le], flag = 1, flag2 = 1;
        for (int g=0; g <= le; g++)
        {
            while (flag < 27)
            {
                if (isupper(h[g]))
                {
                    if(h[g] == f)
                    {
                        pos[g] = flag;
                    }
                    flag++;
                    f++;

                }
                if (islower(h[g]))
                {
                    if(h[g] == e)
                    {
                        pos[g] = flag;
                    }
                    flag++;
                    e++;
                }
            }
        }

        string s = get_string("plaintext: ");

        for (int i = 0, lum = strlen(s); i < lum; i++)
        {
            if (isupper(s[i])) //loop for uppercase
            {
                temp = s[i];
                s[i] = s[i] + pos[flag2];
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
                s[i] = s[i] + pos[flag2];
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
                if (flag2 < le)
                {
                    flag2++;
                }



            }
        }




        printf("ciphertext: %s\n", s); //printing ciphertext
    }
    return 0;
}