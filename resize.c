// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames

    float f = atof(argv[1]);
    // float f = atof(x);
    char *infile = argv[2];
    char *outfile = argv[3];

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
    BITMAPFILEHEADER bfo;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfo = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bo;
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

    // new image width and height
    bo = bi;
    bo.biWidth = round(bi.biWidth * f);
    bo.biHeight = round(bi.biHeight * f);

    // determine padding for scanlines
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out = (4 - (bo.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // new image size and file size
    bo.biSizeImage = ((sizeof(RGBTRIPLE) * bo.biWidth) + padding_out) * abs(bo.biHeight);
    bfo.bfSize = bo.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bo, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE *row_array = (RGBTRIPLE *)malloc(bi.biWidth * sizeof(RGBTRIPLE));

    int curr_out_column;
    int num_column_repeat;
    int num_row_repeat;
    int curr_out_row = 1;
    // iterate over infile's scanlines
    for (int i = 0; i < abs(bi.biHeight); i++)
    {

        // iterate over pixels in scanline
        for (int j = 0; j < abs(bi.biWidth); j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store RBG triple to temporary storage row_array
            row_array[j] = triple;

        }

        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);

        num_row_repeat = round((i + 1) * f) - curr_out_row;
        // copy the rows f times
        for (int p = 0; p <= num_row_repeat; p++)
        {
            curr_out_column = 1;
            for (int j = 0; j < abs(bi.biWidth); j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                triple = row_array[j];

                num_column_repeat = round((j + 1) * f) - curr_out_column;
                // write f times RGB triple to outfile
                for (int k = 0; k <= num_column_repeat; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    curr_out_column++;
                }

            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding_out; k++)
            {
                fputc(0x00, outptr);
            }

            curr_out_row++;
        }


    }

    free(row_array);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
