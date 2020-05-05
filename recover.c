#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //Checking proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //Open file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    int count = 0;
    
    //Create and open image file with proper names
    char *output = malloc(8);
    sprintf(output, "%03i.jpg", count);
    FILE *img = fopen(output, "w");

    //Memory allocation for buffer
    BYTE *block = malloc(512);
    if (block == NULL)
    {
        printf("Memory allocating error\n");
        return 1;
    }

    //Read loop until end of file
    while (fread(block, 1, 512, f) == 512)
    {

        //Start of jpg
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            //First jpg
            if (count == 0)
            {
                count++;
                fwrite(block, 1, 512, img);
            }
            //New jpg
            else
            {
                fclose(img);
                sprintf(output, "%03i.jpg", count);
                img = fopen(output, "w");
                fwrite(block, 1, 512, img);
                count++;
            }

        }
        //Write over existing jpg
        else if (count != 0)
        {
            fwrite(block, sizeof(BYTE), 512, img);
        }
    }

    //Close last image and free allocated memory
    fclose(img);
    free(block);
    free(output);


}
