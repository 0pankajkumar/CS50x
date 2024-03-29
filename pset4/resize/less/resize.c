// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    //Checks that the multiplication factor is a natural number below 101
    if (!(n <= 100 && n > 0))
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int old_biWidth = abs(bi.biWidth);
    int old_biHeight = abs(bi.biHeight);

    //To preset the pixel width & height by n times longer
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_padding = (4 - (old_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = (abs(bi.biWidth) * 3 + new_padding) * abs(bi.biHeight);

    // change dimensions in BITMAPFILEHEADER
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines (each row)
    for (int i = 0; i < old_biHeight; i++)
    {

        for (int l = 0; l < n; l++)
        {
            fseek(inptr, bf.bfOffBits + i * (old_padding + (old_biWidth * 3)), SEEK_SET);

            // iterate over pixels in scanline (each pixel)
            for (int j = 0; j < old_biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            fseek(inptr, new_padding, SEEK_CUR);

            for (int m = 0; m < new_padding; m++)
            {
                fputc(0x00, outptr);
            }
        }

    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
