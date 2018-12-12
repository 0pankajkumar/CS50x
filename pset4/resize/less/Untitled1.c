                temp = (sizeof(RGBTRIPLE) * (n-1));
                fseek(inptr, temp, SEEK_CUR);

                int temp = 0; // A temporary variable

                FILE *outptr2 = fopen("temp.txt", "w");
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr2);
                fclose(outptr2);


                FILE *inptr2 = fopen("temp.txt", "r");
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                //To determine the last position
                fseek(inptr, 0L, SEEK_END);
                int sz = ftell(inptr);
                

