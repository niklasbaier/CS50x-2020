#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command line input
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open memory card
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    // Check that file pointer does not point to NULL
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    char *outfile = malloc(8);
    int filecount = 0;

    // Repeat until end of card
    while (true)
    {
        // buffer of 512 byte size
        BYTE buffer[BLOCK];
        if (fread(buffer, sizeof(BYTE), BLOCK, inptr) < BLOCK)
        {
            break;
        }

        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // create .jpg file
            sprintf(outfile, "%03i.jpg", filecount);
            FILE *img = fopen(outfile, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK, img);
            fclose(img);
            filecount++;
        }
        else
        {
            if (filecount > 0)
            {
                FILE *img = fopen(outfile, "a");
                fwrite(buffer, sizeof(BYTE), BLOCK, img);
                fclose(img);
            }
        }
    }

    // close any remaining files
    free(outfile);
    fclose(inptr);

    return 0;
}
