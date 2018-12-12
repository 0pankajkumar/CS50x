#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef uint8_t  BYTE;


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    int flag = 1;
    int still_writing = 0;
    int track_of_jpegs = 0; //tracking variable for jpeg files created
    char str[10]; //Making str with 000.jpg type naming first
    FILE *outptr; //For handling jpeg output file

    //Repeat untill EOF is reached
    do
    {

        BYTE buffer[512];

        int EndOfFile = fread(&buffer, 1, 512, inptr);

        //EOF check & exit
        if(EndOfFile < 512)
        {
            flag = 0;
            break;
        }




        //Finding the beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(still_writing == 1)
                fclose(outptr);     //Closing old written jpeg files

            //Create new .jpg file and write content
            if (track_of_jpegs < 10)
            {
                sprintf(str, "00%i.jpg", track_of_jpegs);
            }
            else if (track_of_jpegs > 10)
            {
                sprintf(str, "0%i.jpg", track_of_jpegs);
            }
            else if (track_of_jpegs > 99)
            {
                sprintf(str, "%i.jpg", track_of_jpegs);
            }

            //Opening stream for writing jpeg files
            outptr = fopen(str, "w");
            if (inptr == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", argv[1]);
                return 2;
            }
            fwrite(&buffer, 1, 512, outptr);

            still_writing = 1;  //A flag for file pointer closing
            
            ++track_of_jpegs;
        }
        else
        {
            //Write stuff out to .jpg file currently in use
            fwrite(&buffer, 1, 512, outptr);
        }
    } while (flag == 1);










    fclose(inptr);

    printf("%d", track_of_jpegs);

    return 0;
}

